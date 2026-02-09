#// Р¤Р°Р№Р»: Task3/Request.h
#// Р”РµР№СЃС‚РІРёРµ: РѕР±СЉСЏРІР»СЏРµРј РёРЅС‚РµСЂС„РµР№СЃ Р·Р°РїСЂРѕСЃРѕРІ
#pragma once
#include "pch.h"
#include "Date.h"

struct Request : public Object {
    int id;
    char destination[31];  // fixed for binary
    char flightNum[16];
    char passenger[31];
    Date date;

    static Request createFactory(int id);  // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ/пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ

    // Binary (fixed-size) serialization helpers
    void writeBinary(ostream& os) const;
    static bool readBinary(istream& is, Request& out);
// выполняем действие
    static size_t binarySize() { return sizeof(int) + 31 + 16 + 31 + 3 * sizeof(short); }

// получаем
    int getId() const { return id; }
// получаем
    string getDestination() const { return string(destination); }
// получаем
    string getFlightNum() const { return string(flightNum); }
// получаем
    string getPassenger() const { return string(passenger); }
// получаем
    Date getDate() const { return date; }

    string toString() const override;  // const
};
