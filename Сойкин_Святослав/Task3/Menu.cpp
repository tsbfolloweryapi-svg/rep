#include "pch.h"
#include "Utils.h"
#// Р¤Р°Р№Р»: Task3/Menu.cpp
#// Р”РµР№СЃС‚РІРёРµ: СЂРµР°Р»РёР·СѓРµРј РјРµРЅСЋ Рё РЅР°РІРёРіР°С†РёСЋ
#include "Menu.h"

#include "FKeys.h"

Menu::Menu() :startPosition_(), itemColor_(mainColor), currentColor_(infoColor), menuItems_() {}

Menu::Menu(const COORD startPosition, const vector<MenuItem>& menuItems, Palette itemColor, Palette currentColor):
	startPosition_(startPosition),
	itemColor_(itemColor),
	currentColor_(currentColor),
    menuItems_(menuItems)  // пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
{
	// пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
	menuItems_[0].selected(true);
} // Menu::Menu


// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
short Menu::itemColor() const { return itemColor_; }
// формируем меню
void Menu::itemColor(short value) { itemColor_ = value; }

// формируем меню
short Menu::currentColor() const { return currentColor_; }
// формируем меню
void Menu::currentColor(short value) { currentColor_ = value; }

// пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
// получаем


// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
int Menu::getMaxLen() {
	auto toConsole = [](const string &s)->string{
#if CODE_PAGE == 1251
		if (s.empty()) return s;
		int wlen = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, nullptr, 0);
		if (wlen == 0) return s;
		vector<wchar_t> wbuf(wlen);
		MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, wbuf.data(), wlen);
		int len = WideCharToMultiByte(1251, 0, wbuf.data(), -1, nullptr, 0, nullptr, nullptr);
		if (len == 0) return s;
		vector<char> buf(len);
		WideCharToMultiByte(1251, 0, wbuf.data(), -1, buf.data(), len, nullptr, nullptr);
		return string(buf.data(), len - 1);
#else
		return s;
#endif
	};

	return (int)max_element(menuItems_.begin(), menuItems_.end(),
		[&toConsole](MenuItem& mi1, MenuItem& mi2) { return toConsole(mi1.text()).length() < toConsole(mi2.text()).length(); })->text().length();
} // Menu::getMaxLen
// выводим


// пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
void Menu::show() {
	// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
	int maxLen = getMaxLen();
	cout << left;

	// пїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ,
	// пїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ 4пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
	auto toConsole = [](const string &s)->string{
#if CODE_PAGE == 1251
		if (s.empty()) return s;
		int wlen = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, nullptr, 0);
		if (wlen == 0) return s;
		vector<wchar_t> wbuf(wlen);
		MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, wbuf.data(), wlen);
		int len = WideCharToMultiByte(1251, 0, wbuf.data(), -1, nullptr, 0, nullptr, nullptr);
		if (len == 0) return s;
		vector<char> buf(len);
		WideCharToMultiByte(1251, 0, wbuf.data(), -1, buf.data(), len, nullptr, nullptr);
		return string(buf.data(), len - 1);
#else
		return s;
#endif
	};

	int rowOffset = 0;
	for (auto mi:menuItems_) {
		string text = toConsole(mi.text());
		cout<< pos(startPosition_.X, startPosition_.Y + rowOffset++)
			<< color(mi.isSelected()?currentColor_:itemColor_)
			<< "    " << setw(maxLen)<< text << "    ";
	} // for mi
	cout << right;
} // Menu::show
// формируем меню


// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ - пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
int Menu::navigate() {
	int cmd = -1;

	// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
	cout << nocursor;

	// пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅ - пїЅпїЅ ENTER/RETURN пїЅпїЅпїЅ ESCAPE
	auto it = find_if(menuItems_.begin(), menuItems_.end(), 
		[](const MenuItem& mi) { return mi.isSelected(); });

	while (true) {
		// пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
		show();
		
		// пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
		short key = _getch();
// выполняем действие
		if (key == 0 || key == 224) key = _getch();

		// пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
		if (key == VK_RETURN) {
			cmd = it->command();
			break;
// выполняем действие
		} // if

		// пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ - пїЅпїЅпїЅпїЅпїЅ
		if (key == VK_ESCAPE || key == K_F10) {
			cmd = CMD_QUIT;
			break;
// выполняем действие
		} // if

		// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
		switch (key) {
		// пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
		case K_DOWN:
			// пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
// фильтруем
			it->selected(false);

			// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
			if (it == menuItems_.end() - 1) {
				it = menuItems_.begin();
			}
			else {
				it++;
			} // if
			break;

		// пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
		case K_UP:
			// пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
// фильтруем
			it->selected(false);

			// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
			if (it == menuItems_.begin()) {
				it = menuItems_.end() - 1;
			}
			else {
				it--;
			} // if
// выполняем действие
			break;

		case K_HOME:
			if (it != menuItems_.begin()) {
				// пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
				it->selected(false);

				it = menuItems_.begin();
			} // if
// выполняем действие
			break;

			case K_END:
			if (it != menuItems_.end() - 1) {
				// пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
				it->selected(false);

				it = menuItems_.end() - 1;
			} // if
			break;
		} // switch

		// i-пїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
		it->selected(true);
	} // while

	// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
	cout << cursor << color(mainColor);
	return cmd;
} // Menu::navigate
