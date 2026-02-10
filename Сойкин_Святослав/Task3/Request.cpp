#include "Request.h"
#include "Utils.h"
#include <algorithm>
#include <cstring>

// ?????????????/????? ?????
Request Request::createFactory(int id) {
    Request r;
    r.id = id;
    string dest = "????? ?????????? " + to_string(getRand(1, 15));
    string flight = "PO-" + to_string(getRand(1000, 9999)) + "K";
    string pass = "?????? " + to_string(getRand(1, 30)) + " ?.?.";
    Date d;
    d.setDate(getRand(1, 28), getRand(1, 12), getRand(2025, 2027));
    // присвоить строковые поля
    r.destination = dest;
    r.flightNum = flight;
    r.passenger = pass;
    r.date = d;
    return r;
}

// ?????????/???????
string Request::toString() const {
    ostringstream oss;
    // сформировать строковое представление
    oss << "ID: " << id << ", направление: " << destination << ", рейс: " << flightNum
        << ", пассажир: " << passenger << ", дата: " << date.toString();
    return oss.str();
}

// ?????? ? ??????
void Request::writeBinary(ostream& os) const {
    // записать идентификатор
    os.write(reinterpret_cast<const char*>(&id), sizeof(id));
    // записать destination фиксированного размера
    char bufDest[31]; memset(bufDest, 0, sizeof(bufDest));
    memcpy(bufDest, destination.c_str(), min<size_t>(destination.size(), 30));
    os.write(bufDest, sizeof(bufDest));
    // записать flightNum фиксированного размера
    char bufFlight[16]; memset(bufFlight, 0, sizeof(bufFlight));
    memcpy(bufFlight, flightNum.c_str(), min<size_t>(flightNum.size(), 15));
    os.write(bufFlight, sizeof(bufFlight));
    // записать passenger фиксированного размера
    char bufPass[31]; memset(bufPass, 0, sizeof(bufPass));
    memcpy(bufPass, passenger.c_str(), min<size_t>(passenger.size(), 30));
    os.write(bufPass, sizeof(bufPass));
    // записать дату
    short day = date.getDay();
    short month = date.getMonth();
    short year = date.getYear();
    os.write(reinterpret_cast<const char*>(&day), sizeof(day));
    os.write(reinterpret_cast<const char*>(&month), sizeof(month));
    os.write(reinterpret_cast<const char*>(&year), sizeof(year));
}

// ?????? ? ??????
bool Request::readBinary(istream& is, Request& out) {
    // прочитать идентификатор
    if (!is.read(reinterpret_cast<char*>(&out.id), sizeof(out.id))) return false;
    // прочитать destination фиксированного размера
    char bufDest[31]; if (!is.read(bufDest, sizeof(bufDest))) return false;
    bufDest[30] = '\0'; out.destination = string(bufDest);
    // прочитать flightNum фиксированного размера
    char bufFlight[16]; if (!is.read(bufFlight, sizeof(bufFlight))) return false;
    bufFlight[15] = '\0'; out.flightNum = string(bufFlight);
    // прочитать passenger фиксированного размера
    char bufPass[31]; if (!is.read(bufPass, sizeof(bufPass))) return false;
    bufPass[30] = '\0'; out.passenger = string(bufPass);
    // прочитать дату
    short day, month, year;
    if (!is.read(reinterpret_cast<char*>(&day), sizeof(day))) return false;
    if (!is.read(reinterpret_cast<char*>(&month), sizeof(month))) return false;
    if (!is.read(reinterpret_cast<char*>(&year), sizeof(year))) return false;
    out.date.setDate(day, month, year);
    return true;
}
