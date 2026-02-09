#// пїЅпїЅпїЅпїЅ: Task4/Payer.h
#// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ: пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
#pragma once
#include "pch.h"
#include "Object.h"
#include "Date.h"

class Payer : public Object {
private:
    int id_;
    string name_;
    string phone_;
    double tariff_;
    int discount_;
    int timeMin_;
    Date date_;

public:
    static Payer createFactory(int id);

// получаем
    int getId() const { return id_; }
// получаем
    string getName() const { return name_; }
// получаем
    string getPhone() const { return phone_; }
// получаем
    double getTariff() const { return tariff_; }
// получаем
    int getDiscount() const { return discount_; }
// получаем
    int getTimeMin() const { return timeMin_; }
// получаем
    Date getDate() const { return date_; }

// суммируем
    double calculateSum() const { return timeMin_ * tariff_ * (1 - discount_ / 100.0); }

// устанавливаем
    void setId(int id) { id_ = id; }
// устанавливаем
    void setName(const string& name) { name_ = name; }
// устанавливаем
    void setPhone(const string& phone) { phone_ = phone; }
// устанавливаем
    void setTariff(double tariff) { tariff_ = tariff; }
// устанавливаем
    void setDiscount(int discount) { discount_ = discount; }
// устанавливаем
    void setTimeMin(int timeMin) { timeMin_ = timeMin; }
// устанавливаем
    void setDate(short d, short m, short y) { date_.setDate(d, m, y); }

    string toString() const override;
};
