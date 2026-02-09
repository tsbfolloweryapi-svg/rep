#include "pch.h"
#include "Utils.h"
#include "MenuItem.h"
#include "Menu.h"
#include "App.h"

int main() try {
    init(L"Task4: пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ");

#// Р¤Р°Р№Р»: Task4/Main.cpp
#// Р”РµР№СЃС‚РІРёРµ: С‚РѕС‡РєР° РІС…РѕРґР° Task4, СЃРѕР·РґР°С‘Рј Рё Р·Р°РїСѓСЃРєР°РµРј РїСЂРёР»РѕР¶РµРЅРёРµ
    App app;

    // Commands
    enum Commands : int {
        CMD_ADD = 1001,
        CMD_REMOVE,
        CMD_FILTER_TARIFF,
        CMD_FILTER_DISCOUNT,
        CMD_FILTER_SUM_RANGE,
        CMD_SORT_ID,
        CMD_SORT_NAME,
        CMD_SORT_SUM_DESC,
        CMD_CHANGE,
        CMD_SAVE,
        CMD_LOAD
    };

    vector<MenuItem> items = {
        MenuItem(CMD_ADD, "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ"),
        MenuItem(CMD_REMOVE, "пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ ID"),
        MenuItem(CMD_FILTER_TARIFF, "пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ"),
        MenuItem(CMD_FILTER_DISCOUNT, "пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ"),
        MenuItem(CMD_FILTER_SUM_RANGE, "пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ"),
        MenuItem(CMD_SORT_ID, "пїЅпїЅпїЅпїЅ пїЅпїЅ ID"),
        MenuItem(CMD_SORT_NAME, "пїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅ"),
        MenuItem(CMD_SORT_SUM_DESC, "пїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ."),
        MenuItem(CMD_CHANGE, "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ"),
        MenuItem(CMD_SAVE, "Save CSV"),
        MenuItem(CMD_LOAD, "Load CSV"),
        MenuItem(Menu::CMD_QUIT, "пїЅпїЅпїЅпїЅпїЅ")
    };

    Menu menu(COORD{ 5, 5 }, items, mainColor, infoColor);
// выполняем действие

    while (true) {
        cls();
        showNavBarMessage(hintColor, "Task4: пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ");

// выполняем действие
        int cmd = menu.navigate();
        if (cmd == Menu::CMD_QUIT) break;

        switch (cmd) {
        case CMD_ADD: app.doAddPayer(); break;
        case CMD_REMOVE: app.doDeleteById(); break;
        case CMD_FILTER_TARIFF: app.doSelectByTariff(); break;
        case CMD_FILTER_DISCOUNT: app.doSelectByDiscount(); break;
        case CMD_FILTER_SUM_RANGE: app.doSelectBySumRange(); break;
        case CMD_SORT_ID: app.doSortById(); break;
        case CMD_SORT_NAME: app.doSortByName(); break;
        case CMD_SORT_SUM_DESC: app.doSortBySumDescending(); break;
        case CMD_CHANGE: app.doChangePayer(); break;
        case CMD_SAVE: app.doSaveToCSV(); break;
        case CMD_LOAD: app.doLoadFromCSV(); break;
        }

        getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ...");
    }

    cls();
    return 0;
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
