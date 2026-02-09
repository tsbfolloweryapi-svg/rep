#// Р¤Р°Р№Р»: Task4/Payers.cpp
#// Р”РµР№СЃС‚РІРёРµ: СЂРµР°Р»РёР·СѓРµРј СЂР°Р±РѕС‚Сѓ СЃ РєРѕР»Р»РµРєС†РёРµР№ РїР»Р°С‚РёР»СЊС‰РёРєРѕРІ
#include "Payers.h"
#include "Utils.h"
#include <algorithm>
#include <fstream>
// выполняем действие
#include <sstream>
#include <stdexcept>  // for runtime_error

void checkInputFormat(istringstream& iss) {
    if (iss.fail()) throw runtime_error("CSV: пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ");
}

Payers::Payers() {
    for (int i = 0; i < 15; ++i) {
        list_.push_back(Payer::createFactory(nextId_++));
// выполняем действие
    }
}

void Payers::addPayer() {
// выполняем действие
    list_.push_back(Payer::createFactory(nextId_++));
}

void Payers::deleteById(int id) {
    list_.remove_if([id](const Payer& p) { return p.getId() == id; });
// фильтруем
}

list<Payer> Payers::selectByTariff(double tariff) const {
// фильтруем
    list<Payer> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [tariff](const Payer& p) {
        return eq(p.getTariff(), tariff);
        });
// фильтруем
    return result;
}

list<Payer> Payers::selectByDiscount(int discount) const {
// фильтруем
    list<Payer> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [discount](const Payer& p) {
        return p.getDiscount() == discount;
        });
// фильтруем
    return result;
}

list<Payer> Payers::selectBySumRange(double low, double high) const {
// фильтруем
    list<Payer> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [low, high](const Payer& p) {
        double sum = p.calculateSum();
        return sum >= low && sum <= high;
        });
    result.sort([](const Payer& a, const Payer& b) { return a.getPhone() < b.getPhone(); });
// фильтруем
    return result;
}

list<Payer> Payers::selectByPhone(const string& phone) const {
// фильтруем
    list<Payer> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [&phone](const Payer& p) {
        return p.getPhone() == phone;
    });
// фильтруем
    return result;
}

list<Payer> Payers::selectByName(const string& name) const {
// фильтруем
    list<Payer> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [&name](const Payer& p) {
        return p.getName() == name;
    });
// фильтруем
    return result;
}

list<Payer> Payers::selectByDate(const Date& date) const {
// фильтруем
    list<Payer> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [&date](const Payer& p) {
        return p.getDate() == date;
    });
// выполняем действие
    return result;
}

double Payers::totalPayments() const {
    double sum = 0.0;
    for (const auto& p : list_) sum += p.calculateSum();
// сортируем
    return sum;
}

void Payers::sortByPhone() {
    list_.sort([](const Payer& a, const Payer& b) { return a.getPhone() < b.getPhone(); });
// сортируем
}

void Payers::sortByTimeDescending() {
    list_.sort([](const Payer& a, const Payer& b) { return a.getTimeMin() > b.getTimeMin(); });
// сортируем
}

void Payers::sortById() {
    list_.sort([](const Payer& a, const Payer& b) { return a.getId() < b.getId(); });
// сортируем
}

void Payers::sortByName() {
    list_.sort([](const Payer& a, const Payer& b) { return a.getName() < b.getName(); });
// сортируем
}

void Payers::sortBySumDescending() {
    list_.sort([](const Payer& a, const Payer& b) { return a.calculateSum() > b.calculateSum(); });
// выполняем действие
}

void Payers::changePayer(int id) {
// выполняем действие
    for (auto& p : list_) {
// выполняем действие
        if (p.getId() == id) {
            p = Payer::createFactory(id);
            return;
        }
    }
// выполняем действие
    throw runtime_error("пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
}

void Payers::saveToCSV(const string& fname) const {
    ofstream out(fname);
// выполняем действие
    if (!out.is_open()) throw runtime_error(("пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ: " + fname).c_str());

    out << "ID,пїЅпїЅпїЅ,пїЅпїЅпїЅпїЅпїЅпїЅпїЅ,пїЅпїЅпїЅпїЅпїЅ,пїЅпїЅпїЅпїЅпїЅпїЅ,пїЅпїЅпїЅпїЅпїЅпїЅ,пїЅпїЅпїЅпїЅ,пїЅпїЅпїЅпїЅпїЅ,пїЅпїЅпїЅ\n";
    for (const auto& p : list_) {
        out << p.getId() << "," << p.getName() << "," << p.getPhone() << "," << p.getTariff() << "," << p.getDiscount()
            << "," << p.getTimeMin() << "," << p.getDate().getDay() << "," << p.getDate().getMonth() << "," << p.getDate().getYear() << "\n";
// загружаем из файла
    }
}

void Payers::loadFromCSV(const string& fname) {
    if (fname.empty()) throw runtime_error("CSV: пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ.");

    ifstream in(fname);
    if (!in.is_open()) throw runtime_error(("CSV: пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ " + fname).c_str());

    string line;
    if (!getline(in, line)) throw runtime_error("CSV: пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ.");

    {
        istringstream iss(line);
        string token;
        if (!getline(iss, token, ',')) throw runtime_error("CSV: пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ.");
        if (token != "ID") throw runtime_error("CSV: пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ ID).");
        // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ: пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
// очищаем экран
    }

    list_.clear();
    while (getline(in, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        Payer p;
        int id, discount, timeMin, d, m, y;
        double tariff;
        string name, phone;

        iss >> id;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ ID).");
        getline(iss, name, ',');
        getline(iss, phone, ',');
        iss >> tariff;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ).");
        iss >> discount;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ).");
        iss >> timeMin;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ).");
        iss >> d;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ).");
        iss >> m;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ).");
        iss >> y;
        checkInputFormat(iss);

        p.setId(id);
        p.setName(name);
        p.setPhone(phone);
        p.setTariff(tariff);
        p.setDiscount(discount);
        p.setTimeMin(timeMin);
        p.setDate(d, m, y);

        list_.push_back(p);
        nextId_ = max(nextId_, p.getId() + 1);
    }

    if (list_.empty()) throw runtime_error("CSV: пїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ.");
}
