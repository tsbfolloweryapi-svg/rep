#include "Request.h"
#include "Utils.h"

// ?????????????/????? ?????
// Factory: create a sample Request
Request Request::createFactory(int id) {
    // allocate and fill a Request object
    Request r;
    r.id = id;

    // build destination text
    string dest = "Пункт назначения " + to_string(getRand(1, 15));

    // build flight number text
    string flight = "PO-" + to_string(getRand(1000, 9999)) + "K";

    // build passenger name text
    string pass = "Пассажир " + to_string(getRand(1, 30)) + " П.";

    // build date
    Date d;
    d.setDate(getRand(1, 28), getRand(1, 12), getRand(2025, 2027));

    // assign string fields
    r.destination = dest;
    r.flightNum = flight;
    r.passenger = pass;
    r.date = d;

    // return filled record
    return r;
}

// Convert Request to human-readable string
string Request::toString() const {
    // compose textual representation
    ostringstream oss;
    oss << "ID: " << id << ", Пункт назначения: " << destination << ", Рейс: " << flightNum
        << ", Пассажир: " << passenger << ", Дата: " << date.toString();
    return oss.str();
}

// Serialize Request to fixed-size binary record
void Request::writeBinary(ostream& os) const {
    // write id
    os.write(reinterpret_cast<const char*>(&id), sizeof(id));

    // prepare and write fixed-size destination (31 bytes)
    char destBuf[31] = {0};
    strncpy(destBuf, destination.c_str(), 30);
    os.write(destBuf, 31);

    // prepare and write fixed-size flight number (16 bytes)
    char flightBuf[16] = {0};
    strncpy(flightBuf, flightNum.c_str(), 15);
    os.write(flightBuf, 16);

    // prepare and write fixed-size passenger (31 bytes)
    char passBuf[31] = {0};
    strncpy(passBuf, passenger.c_str(), 30);
    os.write(passBuf, 31);

    // write date components
    short day = date.getDay();
    short month = date.getMonth();
    short year = date.getYear();
    os.write(reinterpret_cast<const char*>(&day), sizeof(day));
    os.write(reinterpret_cast<const char*>(&month), sizeof(month));
    os.write(reinterpret_cast<const char*>(&year), sizeof(year));
}

// Deserialize Request from fixed-size binary record
bool Request::readBinary(istream& is, Request& out) {
    // read id
    if (!is.read(reinterpret_cast<char*>(&out.id), sizeof(out.id))) return false;

    // read fixed-size destination
    char destBuf[31];
    if (!is.read(destBuf, 31)) return false;
    destBuf[30] = '\0';
    out.destination = string(destBuf);

    // read fixed-size flight number
    char flightBuf[16];
    if (!is.read(flightBuf, 16)) return false;
    flightBuf[15] = '\0';
    out.flightNum = string(flightBuf);

    // read fixed-size passenger
    char passBuf[31];
    if (!is.read(passBuf, 31)) return false;
    passBuf[30] = '\0';
    out.passenger = string(passBuf);

    // read date components
    short day, month, year;
    if (!is.read(reinterpret_cast<char*>(&day), sizeof(day))) return false;
    if (!is.read(reinterpret_cast<char*>(&month), sizeof(month))) return false;
    if (!is.read(reinterpret_cast<char*>(&year), sizeof(year))) return false;

    // set date and return success
    out.date.setDate(day, month, year);
    return true;
}
