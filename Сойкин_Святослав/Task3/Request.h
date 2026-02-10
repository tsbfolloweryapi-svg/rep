#pragma once
#include "pch.h"
#include "Date.h"

// Структура заявки
struct Request : public Object {
    int id;
    string destination;
    string flightNum;
    string passenger;
    Date date;

    // Создать тестовую заявку
    static Request createFactory(int id);

    // Бинарная (фиксированный размер на диске) сериализация
    void writeBinary(ostream& os) const;
    static bool readBinary(istream& is, Request& out);
    static size_t binarySize() { return sizeof(int) + 31 + 16 + 31 + 3 * sizeof(short); }

    int getId() const { return id; }
    string getDestination() const { return destination; }
    string getFlightNum() const { return flightNum; }
    string getPassenger() const { return passenger; }
    Date getDate() const { return date; }

    // Вернуть строковое представление заявки
    string toString() const override;
};