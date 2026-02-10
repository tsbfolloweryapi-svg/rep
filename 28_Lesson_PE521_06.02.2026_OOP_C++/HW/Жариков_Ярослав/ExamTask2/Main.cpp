#include "pch.h"
#include "Utils.h"
#include "App.h"
#include "MenuItem.h"
#include "Menu.h"

#include "FileException.h"

int main()
{
	// настройка вывода в консоль
	init(L"Обработка текста (string + STL)");

	ostringstream oss;

	// ширина панели вывода сообщения об ошибке
	constexpr int width = 64;

	// коды команд
	enum Commands : short {
		CMD_WORD_FREQ = 1001,
		CMD_LETTER_FREQ,
		CMD_SWAP_ROWS,
		CMD_CAPITALIZE,
		CMD_ORDER_BY_LEN,
		CMD_ORDERLINESS
	};

	// коллекция пунктов меню
	vector<MenuItem> items = {
		MenuItem(CMD_WORD_FREQ,    "Частотный словарь слов текста (map<string,double>)"),
		MenuItem(CMD_LETTER_FREQ,  "Частотный словарь букв текста (map<char,double>, регистро-независимо)"),
		MenuItem(CMD_SWAP_ROWS,    "Поменять местами каждые две соседние строки -> swap.txt"),
		MenuItem(CMD_CAPITALIZE,   "Сделать слова: Первая Буква Заглавная -> capitalize.txt"),
		MenuItem(CMD_ORDER_BY_LEN, "Упорядочить строки по длине -> orderByLen.txt"),
		MenuItem(CMD_ORDERLINESS,  "В каждой строке слова по алфавиту, 1 пробел -> orderliness.txt"),

		MenuItem(Menu::CMD_QUIT, "Выход. Завершение приложения")
	};

	Menu mainMenu(COORD{ 5, 5 }, items, infoColor, hintColor);

	App* app = nullptr;

	while (true) {
		try {
			if (app == nullptr) {
				app = new App();
			} // if

			cout << color(mainColor) << cls;
			showNavBarMessage(hintColor, acctColor, "  Обработка файла test.txt  |  ~Esc~ ~F10~ Выход");

			int cmd = mainMenu.navigate();
			cout << color(mainColor) << cls;
			if (cmd == Menu::CMD_QUIT) break;

			switch (cmd) {
			case CMD_WORD_FREQ:
				app->doWordFrequency();
				break;

			case CMD_LETTER_FREQ:
				app->doLetterFrequency();
				break;

			case CMD_SWAP_ROWS:
				app->doSwapRows();
				break;

			case CMD_CAPITALIZE:
				app->doCapitalize();
				break;

			case CMD_ORDER_BY_LEN:
				app->doOrderByLen();
				break;

			case CMD_ORDERLINESS:
				app->doOrderliness();
				break;
			} // switch
		} // try

		catch (FileException& ex) {
			setColor(mainColor);
			cls();
			showNavBarMessage(hintColor, "  Ошибка приложения, нажмите любую клавишу для продолжения...");

			oss.str("");
			oss << endlm(4) << left
				<< "\t" << setw(width) << " " << "\n"
				<< "\t" << setw(width) << "    [Ошибка]" << "\n"
				<< "\t    " << left << setw(width - 4) << ex.what() << right << "\n"
				<< "\t    " << left << setw(width - 4) << ex.getFileName() << right << "\n"
				<< "\t" << setw(width) << " " << "\n"
				<< "\t" << setw(width) << " " << "\n"
				<< endlm(4)
				<< right;
			showMessage(oss.str(), errColor, mainColor);
		} // catch

		catch (exception& ex) {
			cout << color(mainColor) << cls;
			showNavBarMessage(hintColor, "  Ошибка в приложении, нажмите любую клавишу для продолжения");

			oss.str("");
			oss << endlm(4) << left
				<< "\t" << setw(width) << " " << "\n"
				<< "\t" << setw(width) << "    [Ошибка]" << "\n"
				<< "\t    " << left << setw(width - 4) << ex.what() << right << "\n"
				<< "\t" << setw(width) << " " << "\n"
				<< "\t" << setw(width) << " " << "\n"
				<< endlm(4)
				<< right;
			showMessage(oss.str(), errColor, mainColor);
		} // try-catch

		getKey("\tНажмите любую клавишу для продолжения...");
	} // while

	delete app;
	cls();
	return 0;
} // main
