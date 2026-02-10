#pragma once
#include "pch.h"
#include "Date.h"

struct Request : public Object {
    int id;
    string destination;  // in-memory string
    string flightNum;
    string passenger;
    Date date;

    static Request createFactory(int id); // Создать тестовую заявку

    // Binary (fixed-size) serialization helpers
    void writeBinary(ostream& os) const; // Записать запись фиксированного размера
    static bool readBinary(istream& is, Request& out); // Прочитать запись фиксированного размера
    static size_t binarySize() { return sizeof(int) + 31 + 16 + 31 + 3 * sizeof(short); }

    int getId() const { return id; }
    string getDestination() const { return destination; }
    string getFlightNum() const { return flightNum; }
    string getPassenger() const { return passenger; }
    Date getDate() const { return date; }

    string toString() const override; // Представление заявки в виде строки
};