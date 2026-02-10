#include "App.h"
#include "App.h"
#include "pch.h"
#include "Utils.h"
#include "App.h"

App::App() :App(VectorProcess(), "vector.bin") {} // App::App

App::App(const VectorProcess& vectorProcess, const string& fileName) {
	vectorProcess_ = vectorProcess;
	fileName_ = fileName;
} // App::App

// Сохраненение в бинарный файл
void App::saveToBin()
{
	// открыть бинарный поток вывода
	// ios::trunc очищает файл, усекая его длину до нуля
	fstream fs(fileName_, ios::binary | ios::out | ios::trunc);
	if (!fs.is_open()) {
		throw exception(("App: не могу открыть файл \"" + fileName_ + "\" для записи").c_str());
	} // if

	auto temp = vectorProcess_.getData();

	for (auto& item : temp) {
		fs << item;
	} // for

	// закрыть бинарный поток вывода
	fs.close();
} // App::saveToBin

// Чтение из бинарного файла
void App::loadFromBin()
{ 
	// открыть бинарный поток ввода
	fstream fs(fileName_, ios::binary | ios::in);
	if (!fs.is_open()) {
		throw exception(("App: не могу открыть файл \"" + fileName_ + "\" для чтения").c_str());
	} // if

	vectorProcess_.clearVector();

	auto temp = vectorProcess_.getData();

	// чтение из бинарного потока ввода
	while (!fs.eof()) {
		float vec;
		
		fs >> vec;

		temp.emplace_back(vec);
	} // while

	vectorProcess_.setData(temp);

	// закрыть бинарный поток вывода
	fs.close();
} // App::loadFromBin


// Обработка по заданию
void App::doProcess() {
	showNavBarMessage(hintColor, "    Применение алгоритмов для обработки вектора float");
	
	show("    Вектор для обработки: ");

	saveToBin();

	cout << "\n\nВектор сохранен в файл ( " + fileName_ + " ) \n";

	// Ввод диапазона значений [a, b]
	float a, b;
	cout << "\n\n"
		<< "    Границы интервала [a, b]: " << color(infoColor) << setw(30) << " ";
	COORD coord;
	getXY(&coord);
	cin >> pos(coord.X - 29, coord.Y) >> a >> b >> color(mainColor);
	checkInputFormat(cin);

	int negatives = vectorProcess_.numberNegatives();
	int notInRanges = vectorProcess_.numberNotInRange(a, b);
	cout<< pos(0, coord.Y) << setw(80) << " " << "\r"
		<< "    Отрицательных элементов в векторе: " << setw(8) << negatives << "\n\n"
		<< "    Элементов, не попадающих в интервал [" << a << ", " << b << "]: " << notInRanges << "\n\n";

	float minSum = vectorProcess_.sumToMin();
	float sumMinMax = vectorProcess_.sumInDiaposone();

	cout << "    Сумма элементов до первого минимального: " << setw(8) << minSum << "\n\n"
		 << "    Сумма элементов между первым минимальным и первым максимальным: " << sumMinMax;

	vector<float> temp = vectorProcess_.findByNegative();
	showVector("\n\nВектор с отрицательными элементами: ", temp);

	temp = vectorProcess_.findByDiaposone(a, b);
	showVector("\n\nВектор с диапозоном чисел [ " + to_string(a) + ", " + to_string(b) + " ]: ", temp);

	vectorProcess_.sortItem();
	show("\n\nBектор по убыванию:      ");

	vectorProcess_.sortByModel();
	show("\n\nBектор по возростанию модулей:  ");

	vectorProcess_.sortByDiaposone(a, b);
	show("\n\nBектор по диапозону:  ");

	loadFromBin();

	show("\n\nВектор восстановлен из файла ( " + fileName_ + " )");
} // App::doProcess


// Вывод вектора в консоль, по m элементов в строке, точность 
// precision знаков
void App::show(const string& title, int m, int precision) {
	cout << fixed << setprecision(precision) << title;
	int counter = 0;
	auto data = vectorProcess_.getData();
	for_each(data.begin(), data.end(), [m, &counter, title](float item) {
		cout << setw(10) << item;
		if (++counter % m == 0) {
			cout << "\n" << setw(title.length()) << " ";
		} // if
	});

	// Переход при незаполненной последнй строке вывода
	if (counter % m != 0) {
		cout << "\n";
	} // if
} // App::show

// Вывод вспомогательных векторов
void App::showVector(const string& title, const vector<float>& temp, int m, int precision)
{
	cout << fixed << setprecision(precision) << title;
	int counter = 0;
	for_each(temp.begin(), temp.end(), [m, &counter, title](float item) {
		cout << setw(10) << item;
		if (++counter % m == 0) {
			cout << "\n" << setw(title.length()) << " ";
		} // if
		});

	// Переход при незаполненной последнй строке вывода
	if (counter % m != 0) {
		cout << "\n";
	} // if
} // App::showVector
