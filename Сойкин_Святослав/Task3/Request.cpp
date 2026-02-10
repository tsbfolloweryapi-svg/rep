#include "Request.h"
#include "Utils.h"
// Создание тестовой записи (factory)
Request Request::createFactory(int id) {
    // Инициализация структуры результата
    Request r;
    r.id = id;

    // Формирование строки пункта назначения
    string dest = "Пункт " + to_string(getRand(1, 15));

    // Формирование строки номера рейса
    string flight = "PO-" + to_string(getRand(1000, 9999)) + "K";

    // Формирование строки пассажира
    string pass = "Пассажир " + to_string(getRand(1, 30)) + " П.О.";

    // Формирование даты вылета
    Date d;
    d.setDate(getRand(1, 28), getRand(1, 12), getRand(2025, 2027));

    // Присвоение логических полей (строк) с обрезкой по максимально допустимой длине
    r.destination = dest.substr(0, 30);
    r.flightNum = flight.substr(0, 15);
    r.passenger = pass.substr(0, 30);
    r.date = d;

    // Возврат заполненной записи
    return r;
}

// Преобразование записи в строку для вывода
string Request::toString() const {
    // Формирование человекочитаемой строки
    ostringstream oss;
    oss << "ID: " << id << ", пункт: " << destination << ", рейс: " << flightNum
        << ", пассажир: " << passenger << ", дата: " << date.toString();
    return oss.str();
}

// Запись в бинарный поток с фиксированными полями
void Request::writeBinary(ostream& os) const {
    // Запись идентификатора
    os.write(reinterpret_cast<const char*>(&id), sizeof(id));

    // Подготовка и запись поля destination (31 байт, включая терминатор)
    char bufDest[31] = {0};
    strncpy(bufDest, destination.c_str(), 30);
    os.write(bufDest, 31);

    // Подготовка и запись поля flightNum (16 байт)
    char bufFlight[16] = {0};
    strncpy(bufFlight, flightNum.c_str(), 15);
    os.write(bufFlight, 16);

    // Подготовка и запись поля passenger (31 байт)
    char bufPass[31] = {0};
    strncpy(bufPass, passenger.c_str(), 30);
    os.write(bufPass, 31);

    // Запись даты (день, месяц, год как short)
    short day = date.getDay();
    short month = date.getMonth();
    short year = date.getYear();
    os.write(reinterpret_cast<const char*>(&day), sizeof(day));
    os.write(reinterpret_cast<const char*>(&month), sizeof(month));
    os.write(reinterpret_cast<const char*>(&year), sizeof(year));
}

// Чтение из бинарного потока с фиксированными полями
bool Request::readBinary(istream& is, Request& out) {
    // Чтение идентификатора
    if (!is.read(reinterpret_cast<char*>(&out.id), sizeof(out.id))) return false;

    // Чтение и конвертация поля destination
    char bufDest[31];
    if (!is.read(bufDest, 31)) return false;
    bufDest[30] = '\0';
    out.destination = string(bufDest);

    // Чтение и конвертация поля flightNum
    char bufFlight[16];
    if (!is.read(bufFlight, 16)) return false;
    bufFlight[15] = '\0';
    out.flightNum = string(bufFlight);

    // Чтение и конвертация поля passenger
    char bufPass[31];
    if (!is.read(bufPass, 31)) return false;
    bufPass[30] = '\0';
    out.passenger = string(bufPass);

    // Чтение даты и установка в объект
    short day, month, year;
    if (!is.read(reinterpret_cast<char*>(&day), sizeof(day))) return false;
    if (!is.read(reinterpret_cast<char*>(&month), sizeof(month))) return false;
    if (!is.read(reinterpret_cast<char*>(&year), sizeof(year))) return false;
    out.date.setDate(day, month, year);

    // Успешное чтение
    return true;
}
