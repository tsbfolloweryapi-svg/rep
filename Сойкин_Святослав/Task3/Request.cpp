#include "Request.h"
#include "Utils.h"

// ?????????????/????? ?????
Request Request::createFactory(int id) {
    Request r;
    r.id = id;
    // Создать случайные текстовые поля заявки
    string dest = "Пункт назначения " + to_string(getRand(1, 15));
    string flight = "PO-" + to_string(getRand(1000, 9999)) + "K";
    string pass = "Пассажир " + to_string(getRand(1, 30)) + " П.О.";
    Date d;
    d.setDate(getRand(1, 28), getRand(1, 12), getRand(2025, 2027));
    // Присвоить поля std::string
    r.destination = dest;
    r.flightNum = flight;
    r.passenger = pass;
    r.date = d;
    return r;
}

// ?????????/???????
string Request::toString() const {
    ostringstream oss;
    // Собрать строковое представление заявки
    oss << "ID: " << id << ", Пункт: " << destination << ", Рейс: " << flightNum
        << ", Пассажир: " << passenger << ", Дата: " << date.toString();
    return oss.str();
}

// ?????? ? ??????
void Request::writeBinary(ostream& os) const {
    os.write(reinterpret_cast<const char*>(&id), sizeof(id));
    // Записать поля фиксированной длины: destination(31), flightNum(16), passenger(31)
    char buf31[31];
    memset(buf31, 0, sizeof(buf31));
    strncpy(buf31, destination.c_str(), 30);
    os.write(buf31, 31);

    char buf16[16];
    memset(buf16, 0, sizeof(buf16));
    strncpy(buf16, flightNum.c_str(), 15);
    os.write(buf16, 16);

    char buf31b[31];
    memset(buf31b, 0, sizeof(buf31b));
    strncpy(buf31b, passenger.c_str(), 30);
    os.write(buf31b, 31);
    short day = date.getDay();
    short month = date.getMonth();
    short year = date.getYear();
    os.write(reinterpret_cast<const char*>(&day), sizeof(day));
    os.write(reinterpret_cast<const char*>(&month), sizeof(month));
    os.write(reinterpret_cast<const char*>(&year), sizeof(year));
}

// ?????? ? ??????
bool Request::readBinary(istream& is, Request& out) {
    if (!is.read(reinterpret_cast<char*>(&out.id), sizeof(out.id))) return false;
    // Прочитать фиксированные поля в временные буферы и присвоить std::string
    char td[31];
    if (!is.read(td, 31)) return false;
    td[30] = '\0';
    out.destination = string(td);

    char tf[16];
    if (!is.read(tf, 16)) return false;
    tf[15] = '\0';
    out.flightNum = string(tf);

    char tp[31];
    if (!is.read(tp, 31)) return false;
    tp[30] = '\0';
    out.passenger = string(tp);
    short day, month, year;
    if (!is.read(reinterpret_cast<char*>(&day), sizeof(day))) return false;
    if (!is.read(reinterpret_cast<char*>(&month), sizeof(month))) return false;
    if (!is.read(reinterpret_cast<char*>(&year), sizeof(year))) return false;

    // Ensure null-termination (in case source used full-length strings)
    out.destination[30] = '\0';
    out.flightNum[15] = '\0';
    out.passenger[30] = '\0';

    out.date.setDate(day, month, year);
    return true;
}
