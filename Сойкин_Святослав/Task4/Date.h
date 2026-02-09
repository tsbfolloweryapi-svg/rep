#// Р¤Р°Р№Р»: Task4/Date.h
#// Р”РµР№СЃС‚РІРёРµ: РѕР±СЉСЏРІР»СЏРµРј С‚РёРїС‹ Рё С„СѓРЅРєС†РёРё РґР»СЏ СЂР°Р±РѕС‚С‹ СЃ РґР°С‚РѕР№
#pragma once
#include "pch.h"
#include "Object.h"

// пїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ: пїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅ. 
class Date : public Object
{
    short day_;   // пїЅпїЅпїЅпїЅ
    short month_; // пїЅпїЅпїЅпїЅпїЅ
    short year_;  // пїЅпїЅпїЅ

    static bool  dateValid(short day, short month, short year);
    static short daysInMonth(short month, short year);
    static bool  isLeapYear(short year);

    int  toJulianDays() const;
    void toGrigorian(int julianDays);

public:
    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    Date() : day_(1), month_(1), year_(1970) {}
// выполняем действие
    Date(short day, short month, short year) {
        setDate(day, month, year);
    } // Date

    Date(const Date& date) = default;
    virtual ~Date() = default;

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
    short getDay()   const { return day_; }
// получаем
    short getMonth() const { return month_; }
// получаем
    short getYear()  const { return year_; }

    void setDate(short day, short month, short year);

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
    virtual string toString() const override;

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ <, == пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ map, multimap, set, multiset 
    bool operator <(const Date& date) const;
    bool operator==(const Date& date) const;

    friend ostream& operator<<(ostream& os, const Date& date);
    friend istream& operator>>(istream& is, Date& date);
};
