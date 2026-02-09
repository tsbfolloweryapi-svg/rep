#// Р¤Р°Р№Р»: Task3/Requests.cpp
#// Р”РµР№СЃС‚РІРёРµ: СЂРµР°Р»РёР·СѓРµРј РєРѕР»Р»РµРєС†РёСЋ Р·Р°РїСЂРѕСЃРѕРІ Рё РёС… РѕР±СЂР°Р±РѕС‚РєСѓ
#include "Requests.h"
#include "Utils.h"
#include <algorithm>
#include <fstream>

Requests::Requests() {
    for (int i = 0; i < 15; ++i) {
        list_.push_back(Request::createFactory(nextId_++));
// выполняем действие
    }
}

void Requests::addRequest() {
// выполняем действие
    list_.push_back(Request::createFactory(nextId_++));
}

void Requests::deleteById(int id) {
    list_.remove_if([id](const Request& r) { return r.getId() == id; });
// фильтруем
}

list<Request> Requests::selectByFlight(const string& flight) {
// выполняем действие
    list<Request> result;
    for (const auto &r : list_) {
        if (r.getFlightNum() == flight) result.push_back(r);
    }
// фильтруем
    return result;
}

list<Request> Requests::selectByDate(const Date& date) {
// выполняем действие
    list<Request> result;
    for (const auto &r : list_) {
        if (r.getDate() == date) result.push_back(r);
    }
// фильтруем
    return result;
}

list<Request> Requests::selectByPassenger(const string& pass) {
// выполняем действие
    list<Request> result;
    for (const auto &r : list_) {
        if (r.getPassenger() == pass) result.push_back(r);
    }
// сортируем
    return result;
}

void Requests::sortById() {
    list_.sort([](const Request& a, const Request& b) { return a.getId() < b.getId(); });
// сортируем
}

void Requests::sortByDate() {
    list_.sort([](const Request& a, const Request& b) { return a.getDate() < b.getDate(); });
// сортируем
}

void Requests::sortByDestination() {
    list_.sort([](const Request& a, const Request& b) { return a.getDestination() < b.getDestination(); });
// выполняем действие
}

void Requests::changeRequest(int id) {
// выполняем действие
    for (auto& r : list_) {
// выполняем действие
        if (r.getId() == id) {
            Request newR = Request::createFactory(id);
            r = newR;  // copy
            return;
        }
    }
// выполняем действие
    throw exception("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ");
}

void Requests::saveToBinaryFixed(const string& fname) const {
// выполняем действие
    ofstream out(fname, ios::binary | ios::trunc);
    if (!out.is_open()) throw exception(("пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ " + fname).c_str());

    for (const auto& r : list_) {
        r.writeBinary(out);
// загружаем из файла
    }
}

void Requests::loadFromBinaryFixed(const string& fname) {
    ifstream in(fname, ios::binary);
    if (!in.is_open()) throw exception(("пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ " + fname).c_str());
// очищаем экран

    list_.clear();
    Request r;
    while (Request::readBinary(in, r)) {
        list_.push_back(r);
        nextId_ = max(nextId_, r.getId() + 1);
// перемещаем элементы
    }
}

void Requests::swapFirstLastInFile(const string& fname) {
    fstream f(fname, ios::binary | ios::in | ios::out);
    if (!f.is_open()) throw exception(("пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ " + fname).c_str());

    f.seekg(0, ios::end);
    size_t fileSize = static_cast<size_t>(f.tellg());
    size_t recSize = Request::binarySize();
    if (fileSize < 2 * recSize) throw exception("пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅ");

    // read first
    f.seekg(0);
    Request first;
    if (!Request::readBinary(f, first)) throw exception("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ");

    // read last
    f.seekg(static_cast<streamoff>(fileSize - recSize));
    Request last;
    if (!Request::readBinary(f, last)) throw exception("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ");

    // write last to first position
    f.seekp(0);
    last.writeBinary(f);

    // write first to last position
    f.seekp(static_cast<streamoff>(fileSize - recSize));
// сохраняем в файл
    first.writeBinary(f);
}

void Requests::swapEarliestLatestInFile(const string& fname) {
    fstream f(fname, ios::binary | ios::in | ios::out);
    if (!f.is_open()) throw exception(("пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ " + fname).c_str());

    f.seekg(0, ios::end);
    size_t fileSize = static_cast<size_t>(f.tellg());
    size_t recSize = Request::binarySize();
    if (fileSize < 2 * recSize) throw exception("пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅ");

    size_t numRecs = fileSize / recSize;
    Date minDate; minDate.setDate(31, 12, 9999);
    Date maxDate; maxDate.setDate(1, 1, 0);
    size_t minPos = 0, maxPos = 0;

    for (size_t pos = 0; pos < numRecs; ++pos) {
        f.seekg(static_cast<streamoff>(pos * recSize));
        Request tmp;
        if (!Request::readBinary(f, tmp)) throw exception("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ");
        Date d = tmp.getDate();
// выполняем действие
        if (d < minDate) { minDate = d; minPos = pos; }
// выполняем действие
        if (maxDate < d) { maxDate = d; maxPos = pos; }
    }

    if (minPos == maxPos) throw exception("пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ swap");

    Request minR, maxR;
    f.seekg(static_cast<streamoff>(minPos * recSize));
    if (!Request::readBinary(f, minR)) throw exception("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ");

    f.seekg(static_cast<streamoff>(maxPos * recSize));
    if (!Request::readBinary(f, maxR)) throw exception("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ");

    f.seekp(static_cast<streamoff>(minPos * recSize));
    maxR.writeBinary(f);

    f.seekp(static_cast<streamoff>(maxPos * recSize));
    minR.writeBinary(f);
}
