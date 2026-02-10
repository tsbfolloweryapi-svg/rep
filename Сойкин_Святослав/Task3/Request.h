#pragma once
#include "pch.h"
#include "Date.h"

// Definition of Request record and helpers
struct Request : public Object {
    // identifier field
    int id;

    // destination string (variable-length in-memory)
    string destination;

    // flight number string (variable-length in-memory)
    string flightNum;

    // passenger name string (variable-length in-memory)
    string passenger;

    // desired date
    Date date;

    // factory method: create a sample Request
    static Request createFactory(int id);

    // Binary (fixed-size) serialization helpers: write/read fixed-size records
    void writeBinary(ostream& os) const;
    static bool readBinary(istream& is, Request& out);
    static size_t binarySize() { return sizeof(int) + 31 + 16 + 31 + 3 * sizeof(short); }

    // accessors
    int getId() const { return id; }
    string getDestination() const { return destination; }
    string getFlightNum() const { return flightNum; }
    string getPassenger() const { return passenger; }
    Date getDate() const { return date; }

    // textual representation
    string toString() const override;
};