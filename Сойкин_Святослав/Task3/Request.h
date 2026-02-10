#pragma once
#include "pch.h"
#include "Date.h"

struct Request : public Object {
    int id;
    string destination;  // logical field, serialized as fixed 31 bytes
    string flightNum;    // logical field, serialized as fixed 16 bytes
    string passenger;    // logical field, serialized as fixed 31 bytes
    Date date;

    static Request createFactory(int id);  // фабричный метод создания тестовой записи

    // Binary (fixed-size) serialization helpers
    void writeBinary(ostream& os) const;
    static bool readBinary(istream& is, Request& out);
    static size_t binarySize() { return sizeof(int) + 31 + 16 + 31 + 3 * sizeof(short); }

    int getId() const { return id; }
    string getDestination() const { return destination; }
    string getFlightNum() const { return flightNum; }
    string getPassenger() const { return passenger; }
    Date getDate() const { return date; }

    string toString() const override;  // представление для вывода
};