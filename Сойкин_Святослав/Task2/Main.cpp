#include "pch.h"
#include "Utils.h"
#include "MenuItem.h"
#include "Menu.h"
#// Р¤Р°Р№Р»: Task2/Main.cpp
// точка входа
#// Р”РµР№СЃС‚РІРёРµ: С‚РѕС‡РєР° РІС…РѕРґР°, СЃРѕР·РґР°С‘Рј Рё Р·Р°РїСѓСЃРєР°РµРј РїСЂРёР»РѕР¶РµРЅРёРµ
#include "pch.h"

int main() {
    init(L"Task2: пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");

    App app;

    // Commands
    enum Commands : int {
        CMD_FREQ_WORDS = 1001,
        CMD_FREQ_LETTERS,
        CMD_SWAP_LINES,
        CMD_CAPITALIZE,
        CMD_ORDER_BY_LEN,
        CMD_ORDER_WORDS_IN_LINES
    };

    vector<MenuItem> items = {
        MenuItem(CMD_FREQ_WORDS, "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ"),
        MenuItem(CMD_FREQ_LETTERS, "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ"),
        MenuItem(CMD_SWAP_LINES, "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ"),
        MenuItem(CMD_CAPITALIZE, "Capitalize пїЅпїЅпїЅпїЅпїЅ"),
        MenuItem(CMD_ORDER_BY_LEN, "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ"),
        MenuItem(CMD_ORDER_WORDS_IN_LINES, "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ"),
        MenuItem(Menu::CMD_QUIT, "пїЅпїЅпїЅпїЅпїЅ")
    };

    Menu menu(COORD{ 5, 5 }, items, mainColor, infoColor);
// выполняем действие

    while (true) {
        try {
            cls();
            showNavBarMessage(hintColor, "Task2: пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ");

// выполняем действие
            int cmd = menu.navigate();
            if (cmd == Menu::CMD_QUIT) break;

            switch (cmd) {
            case CMD_FREQ_WORDS: app.doFreqDictWords(); break;
            case CMD_FREQ_LETTERS: app.doFreqDictLetters(); break;
            case CMD_SWAP_LINES: app.doSwapLines(); break;
            case CMD_CAPITALIZE: app.doWordsCapitalize(); break;
            case CMD_ORDER_BY_LEN: app.doOrderByLen(); break;
// выполняем действие
            case CMD_ORDER_WORDS_IN_LINES: app.doOrderWordsInLines(); break;
            }
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
