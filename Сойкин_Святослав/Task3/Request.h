#pragma once
#include "pch.h"
#include "Date.h"

// Request: represents a single ticket request record.
//
// NOTE: originally this struct used fixed-size C-style char arrays
// (destination[31], flightNum[16], passenger[31]) to store text so the
// on-disk binary format had fixed-length records. To avoid issues with
// teacher's preference for non-char arrays and to make in-memory usage
// safer, we now use `std::string` members for textual fields while
// preserving the on-disk fixed-size binary layout when serializing.
//
// The in-memory layout is strings (dynamic) but `writeBinary`/`readBinary`
// will marshal/unmarshal these strings into fixed-size buffers so existing
// file-handling code (which expects constant-size records) continues to work.
// This keeps file operations compatible while eliminating C-style buffers
// from the public API of `Request`.
struct Request : public Object {
    int id;                 // numeric identifier
    std::string destination; // destination name (variable-length in memory)
    std::string flightNum;   // flight code (variable-length in memory)
    std::string passenger;   // passenger name (variable-length in memory)
    Date date;               // desired flight date

    // Create a synthetic request (factory used by app initialization).
    static Request createFactory(int id);

    // Binary (fixed-size) serialization helpers.
    // These functions will write/read fixed-size fields to preserve
    // compatibility with the on-disk record format used elsewhere.
    void writeBinary(ostream& os) const;
    static bool readBinary(istream& is, Request& out);

    // Size of a record on disk (fixed): int + 31 + 16 + 31 + 3*short
    // Keep this constant so existing file-based logic can compute offsets.
    static size_t binarySize() { return sizeof(int) + 31 + 16 + 31 + 3 * sizeof(short); }

    // Simple accessors (return `std::string`).
    int getId() const { return id; }
    std::string getDestination() const { return destination; }
    std::string getFlightNum() const { return flightNum; }
    std::string getPassenger() const { return passenger; }
    Date getDate() const { return date; }

    // Textual representation for display/debug.
    string toString() const override;
};