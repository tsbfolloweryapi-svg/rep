#// Р¤Р°Р№Р»: Task3/Utils.h
#// Р”РµР№СЃС‚РІРёРµ: РѕР±СЉСЏРІР»СЏРµРј РІСЃРїРѕРјРѕРіР°С‚РµР»СЊРЅС‹Рµ СѓС‚РёР»РёС‚С‹
#pragma once
#include "Palette.h"

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ

// пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
const int W = 84;

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅ., пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ)
// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ: https://www.asutpp.ru/skorost-sveta.html
const double C = 1'080'000'000;


// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ)
void init(const wstring &title = L"пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ");

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ (пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ)
int getKey(const string &message = "\t    пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ...");

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
int    getRand(int    low, int    high);
double getRand(double low, double high);
float  getRand(float  low, float  high);
char   getRand(char   low, char   high);

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
void setColor(short color);

// пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
int getInt();

// пїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
void showNavBarMessage(short hintColor, const string &message);
void showNavBarMessage(short hintColor, short acctColor, const string &message);

// пїЅпїЅпїЅпїЅпїЅ "пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ"
void showUnderConstruction(short width, short mainColor, short infoColor);

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
void showMessage(const string &msg, short msgColor, short mainColor);

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
void showInputLine(const string &prompt = "пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ:", short n = 19, short color = infoColor);

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
void checkInputFormat(istream& is);

// ---------------------------------------------------------------------------------
#pragma region WinAPI_helpers
// пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ WinAPI пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ

COORD getConsoleSize();

void showCursor(bool mode);
bool isCursor();

void gotoXY(short x, short y);
void getXY(COORD* position);


void cls();
#include <Windows.h>

// пїЅпїЅпїЅпїЅпїЅпїЅ UTF-8 пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ CP1251-пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
void printCp1251(const string& utf8);
#pragma endregion


#pragma region stream_manipulators
// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅ-пїЅпїЅпїЅпїЅпїЅпїЅпїЅ

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ: cout << cls;
ostream& cls(ostream& os);
// cin >> cls;
istream& cls(istream& is);

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ: cout << tab;
ostream& tab(ostream& os);

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ: cout << cursor
ostream& cursor(ostream& os);
istream& cursor(istream& is);

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ: cout << nocursor
ostream& nocursor(ostream& os);
istream& nocursor(istream& is);

// пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ: cout << endlm(n)
class endlm
{
	int n_;

public:
	endlm(int n) : n_(n) {}

	friend ostream& operator<<(ostream& os, const endlm& obj);
};

// пїЅпїЅпїЅпїЅпїЅ-пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
class color
{
	short color_;

public:
	color(short color) : color_(color) {}

	friend ostream& operator<<(ostream& os, const color& obj);
	friend istream& operator>>(istream& is, const color& obj);
};

// пїЅпїЅпїЅпїЅпїЅ-пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
class pos
{
	short x_;
	short y_;

public:
	pos(short x, short y) : x_(x), y_(y) {}

	friend ostream& operator<<(ostream& os, const pos& obj);
	friend istream& operator>>(istream& is, const pos& obj);
};

#pragma endregion


// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
inline bool eq(double d1, double d2) { return abs(d1 - d2) <= 1e-6; }
// выполняем действие
inline bool eq(float d1, float d2) { return abs(d1 - d2) <= 1e-6; }

int getCurrentYear();
