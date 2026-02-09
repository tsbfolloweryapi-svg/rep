#// Р¤Р°Р№Р»: Task3/Main.cpp
#// Р”РµР№СЃС‚РІРёРµ: С‚РѕС‡РєР° РІС…РѕРґР° Task3, СЃРѕР·РґР°С‘Рј Рё Р·Р°РїСѓСЃРєР°РµРј РїСЂРёР»РѕР¶РµРЅРёРµ
#include "pch.h"
#include "Utils.h"
#include "MenuItem.h"
// точка входа
#include "Menu.h"
#include "App.h"

int main() {
    init(L"Task3: пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ");

    App app;

    // Commands
    enum Commands : int {
        CMD_ADD = 1001,
        CMD_REMOVE,
        CMD_FILTER_FLIGHT,
        CMD_FILTER_DATE,
        CMD_FILTER_PASS,
        CMD_SORT_ID,
        CMD_SORT_DATE,
        CMD_SORT_DEST,
        CMD_CHANGE,
        CMD_SAVE,
        CMD_LOAD,
        CMD_SWAP_FIRST_LAST,
        CMD_SWAP_EARLY_LATEST
    };

    vector<MenuItem> items = {
        MenuItem(CMD_ADD, "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ"),
        MenuItem(CMD_REMOVE, "пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ ID"),
        MenuItem(CMD_FILTER_FLIGHT, "пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ"),
        MenuItem(CMD_FILTER_DATE, "пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅ"),
        MenuItem(CMD_FILTER_PASS, "пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ"),
        MenuItem(CMD_SORT_ID, "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ ID"),
        MenuItem(CMD_SORT_DATE, "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅ"),
        MenuItem(CMD_SORT_DEST, "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ"),
        MenuItem(CMD_CHANGE, "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ"),
        MenuItem(CMD_SAVE, "Save binary"),
        MenuItem(CMD_LOAD, "Load binary"),
        MenuItem(CMD_SWAP_FIRST_LAST, "Swap first/last in file"),
        MenuItem(CMD_SWAP_EARLY_LATEST, "Swap earliest/latest in file"),
        MenuItem(Menu::CMD_QUIT, "пїЅпїЅпїЅпїЅпїЅ")
    };

    Menu menu(COORD{ 5, 5 }, items, mainColor, infoColor);
// выполняем действие

    while (true) {
        try {
            cls();
            showNavBarMessage(hintColor, "Task3: пїЅпїЅпїЅпїЅпїЅпїЅ");

// выполняем действие
            int cmd = menu.navigate();
            if (cmd == Menu::CMD_QUIT) break;

            switch (cmd) {
            case CMD_ADD: app.doAddRequest(); break;
            case CMD_REMOVE: app.doDeleteById(); break;
            case CMD_FILTER_FLIGHT: app.doSelectByFlight(); break;
            case CMD_FILTER_DATE: app.doSelectByDate(); break;
            case CMD_FILTER_PASS: app.doSelectByPassenger(); break;
            case CMD_SORT_ID: app.doSortById(); break;
            case CMD_SORT_DATE: app.doSortByDate(); break;
            case CMD_SORT_DEST: app.doSortByDestination(); break;
            case CMD_CHANGE: app.doChangeRequest(); break;
            case CMD_SAVE: app.doSaveToBinaryFixed(); break;
            case CMD_LOAD: app.doLoadFromBinaryFixed(); break;
            case CMD_SWAP_FIRST_LAST: app.doSwapFirstLastInFile(); break;
            case CMD_SWAP_EARLY_LATEST: app.doSwapEarliestLatestInFile(); break;
            }
// получаем

            getKey("");
        }
        catch (exception& ex) {
            int x = 12, y = 8;
            cout << color(errColor)
                << pos(x, y) << setw(W) << " "
                << pos(x, y + 1) << setw(W) << " "
                << pos(x, y + 2) << setw(W) << left << "    [пїЅпїЅпїЅпїЅпїЅпїЅ]"
                << pos(x, y + 3) << setw(W) << " "
                << pos(x, y + 4) << setw(W) << ("    "s + ex.what())
                << pos(x, y + 5) << setw(W) << " "
                << pos(x, y + 6) << setw(W) << " "
                << pos(0, 20) << right << color(mainColor);
            getKey("");
        }
    }

    cls();
    return 0;
}
