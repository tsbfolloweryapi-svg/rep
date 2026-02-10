#include "Request.h"
#include "Utils.h"
// --- Request factory -----------------------------------------------------
// Build a synthetic `Request` with randomized fields used for initial
// population of the collection. The function intentionally constructs
// human-readable strings and returns a `Request` with `std::string`
// members populated.
Request Request::createFactory(int id) {
    Request r;
    // Set numeric identifier
    r.id = id;

    // Destination, flight code and passenger name are created as strings
    // (in-memory we use std::string; binary serialization will handle
    // marshaling to fixed-length fields when writing to disk).
    r.destination = "Город " + to_string(getRand(1, 15));
    r.flightNum = "PO-" + to_string(getRand(1000, 9999)) + "K";
    r.passenger = "Пассажир " + to_string(getRand(1, 30)) + " П.О.";

    // Random date within a reasonable range
    Date d;
    d.setDate(getRand(1, 28), getRand(1, 12), getRand(2025, 2027));
    r.date = d;

    return r;
}


// --- Textual representation ---------------------------------------------
// Return human-readable description of the request. Useful for console
// output and debugging.
string Request::toString() const {
    ostringstream oss;
    oss << "ID: " << id
        << ", destination: " << destination
        << ", flight: " << flightNum
        << ", passenger: " << passenger
        << ", date: " << date.toString();
    return oss.str();
}


// --- Binary serialization (fixed-size record) ---------------------------
// We maintain the same on-disk fixed-size layout as before for
// compatibility with other code that expects constant record sizes.
// Layout (bytes): int id; char destination[31]; char flightNum[16];
// char passenger[31]; short day; short month; short year;
//
// `writeBinary` marshals `std::string` fields into temporary
// fixed-size buffers (truncating or padding as necessary) and writes
// them into the stream. `readBinary` reads fixed-sized blocks and
// constructs std::string values from them.
void Request::writeBinary(ostream& os) const {
    // Write id (binary)
    os.write(reinterpret_cast<const char*>(&id), sizeof(id));

    // Destination: fixed 31 bytes on disk. Copy up to 30 characters
    // and ensure a terminating zero in the buffer written.
    char destBuf[31] = {0};
    strncpy(destBuf, destination.c_str(), 30);
    destBuf[30] = '\0';
    os.write(destBuf, 31);

    // Flight number: fixed 16 bytes
    char flightBuf[16] = {0};
    strncpy(flightBuf, flightNum.c_str(), 15);
    flightBuf[15] = '\0';
    os.write(flightBuf, 16);

    // Passenger: fixed 31 bytes
    char passBuf[31] = {0};
    strncpy(passBuf, passenger.c_str(), 30);
    passBuf[30] = '\0';
    os.write(passBuf, 31);

    // Date components as shorts
    short day = date.getDay();
    short month = date.getMonth();
    short year = date.getYear();
    os.write(reinterpret_cast<const char*>(&day), sizeof(day));
    os.write(reinterpret_cast<const char*>(&month), sizeof(month));
    os.write(reinterpret_cast<const char*>(&year), sizeof(year));
}


// Read a fixed-size record from stream and populate `out`.
// Returns false on read failure (EOF, truncated record, etc.).
bool Request::readBinary(istream& is, Request& out) {
    if (!is.read(reinterpret_cast<char*>(&out.id), sizeof(out.id))) return false;

    char destBuf[31];
    if (!is.read(destBuf, 31)) return false;
    char flightBuf[16];
    if (!is.read(flightBuf, 16)) return false;
    char passBuf[31];
    if (!is.read(passBuf, 31)) return false;

    short day, month, year;
    if (!is.read(reinterpret_cast<char*>(&day), sizeof(day))) return false;
    if (!is.read(reinterpret_cast<char*>(&month), sizeof(month))) return false;
    if (!is.read(reinterpret_cast<char*>(&year), sizeof(year))) return false;

    // Ensure buffers are null-terminated then assign to std::string fields.
    destBuf[30] = '\0';
    flightBuf[15] = '\0';
    passBuf[30] = '\0';

    out.destination = string(destBuf);
    out.flightNum = string(flightBuf);
    out.passenger = string(passBuf);

    out.date.setDate(day, month, year);
    return true;
}
