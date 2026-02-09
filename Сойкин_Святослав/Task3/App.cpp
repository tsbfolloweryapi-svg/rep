#// Р¤Р°Р№Р»: Task3/App.cpp
#// Р”РµР№СЃС‚РІРёРµ: СЂРµР°Р»РёР·СѓРµРј Р»РѕРіРёРєСѓ РїСЂРёР»РѕР¶РµРЅРёСЏ Task3
#include "App.h"
#include "Utils.h"

App::App() {}
// выводим

void App::printList(const list<Request>& lst, const string& title) const {
    cout << "     " << title << "\n"
        << "     +" << setfill('-') << setw(112) << "-" << "+"
// устанавливаем
        << setfill(' ') << "\n";

    int row = 1;
    for (const auto& r : lst) {
        cout << " " << setfill('0') << setw(3) << row++ << setfill(' ')
            << " | ID: " << setw(2) << r.id
            << " | пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ: " << setw(19) << r.destination
            << " | пїЅпїЅпїЅпїЅ: " << setw(8) << r.flightNum
            << " | пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ: " << setw(15) << r.passenger
            << " | пїЅпїЅпїЅпїЅ: " << r.date.toString() << " |\n";
    }
    cout << "     +" << setfill('-') << setw(112) << "-" << "+"
// устанавливаем
        << setfill(' ') << "\n";
}

void App::doAddRequest() {
    cls();
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ... \n\n");

    requests_.addRequest();
    cout << "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ\n";

    cls();
// выводим
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
}

void App::doDeleteById() {
    cls();
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ... \n\n");

    if (getRequests().empty()) throw exception("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ");

    const auto& all = requests_.getList();
    auto it = all.begin();
    advance(it, getRand(0, static_cast<int>(all.size()) - 1));
    int id = it->getId();
    requests_.deleteById(id);
    cout << color(errColor) << "пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ ID: " << id << color(mainColor) << "\n";

    cls();
// выводим
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
}

void App::doSelectByFlight() {
    cls();
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ... \n\n");

    if (getRequests().empty()) throw exception("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ");

    const auto& all = requests_.getList();
    auto it = all.begin();
    advance(it, getRand(0, static_cast<int>(all.size()) - 1));
    string flight = it->getFlightNum();
    cout << "пїЅпїЅпїЅпїЅ: " << flight << "\n";
    auto res = requests_.selectByFlight(flight);
// выводим
    printList(res, "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ");
}

void App::doSelectByDate() {
    cls();
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ... \n\n");

    if (getRequests().empty()) throw exception("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ");

    const auto& all = requests_.getList();
    auto it = all.begin();
    advance(it, getRand(0, static_cast<int>(all.size()) - 1));
    Date date = it->getDate();
    cout << "пїЅпїЅпїЅпїЅ: " << date.toString() << "\n";
    auto res = requests_.selectByDate(date);
// выводим
    printList(res, "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅ");
}

void App::doSelectByPassenger() {
    cls();
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ... \n\n");

    if (getRequests().empty()) throw exception("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ");

    const auto& all = requests_.getList();
    auto it = all.begin();
    advance(it, getRand(0, static_cast<int>(all.size()) - 1));
    string pass = it->getPassenger();
    cout << "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ: " << pass << "\n";
    auto res = requests_.selectByPassenger(pass);
// выводим
    printList(res, "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ");
}

void App::doSortById() {
    cls();
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ... \n\n");

    requests_.sortById();
    cout << "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ ID\n";

    cls();
// выводим
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
}

void App::doSortByDate() {
    cls();
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ... \n\n");

    requests_.sortByDate();
    cout << "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅ\n";

    cls();
// выводим
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
}

void App::doSortByDestination() {
    cls();
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ... \n\n");

    requests_.sortByDestination();
    cout << "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ\n";

    cls();
// выводим
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
}

void App::doChangeRequest() {
    cls();
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ... \n\n");

    if (getRequests().empty()) throw exception("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ");

    auto it = getRequests().begin();
    advance(it, getRand(0, getRequests().size() - 1));
    int id = it->id;
    requests_.changeRequest(id);
    cout << "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ ID: " << id << "\n";

    cls();
// выводим
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
}

void App::doSaveToBinaryFixed() {
    cls();
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ... \n\n");

    requests_.saveToBinaryFixed(binFile_);
    cout << "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ\n";

    cls();
// выводим
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
}

void App::doLoadFromBinaryFixed() {
    cls();
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ... \n\n");

    requests_.loadFromBinaryFixed(binFile_);
    cout << "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ\n";

    cls();
// выводим
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
}

void App::doSwapFirstLastInFile() {
    cls();
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ... \n\n");

    requests_.swapFirstLastInFile(binFile_);
    cout << "пїЅпїЅпїЅпїЅпїЅпїЅ/пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ\n";

    cls();
// выводим
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
}

void App::doSwapEarliestLatestInFile() {
    cls();
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ... \n\n");

    requests_.swapEarliestLatestInFile(binFile_);
    cout << "пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ/пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ\n";

    cls();
    printList(getRequests(), "пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");
}
