#include "pch.h"
#include "Utils.h"
#include "App.h"
#include "VectorFactory.h"

#pragma region задача 1

void App::doTask1() {
	showNavBarMessage(hintColor, "  Обработка вектора стандартными алгоритмами");

	cout << "\tОбработка вектора, закрытого типом float алгоритмами:\n\n";

	// генерация вектора фабричным методом
	int n = getRand(12, 30);
	task_.data(VectorFactory::create(n));

	string fileName = "vector.bin";
	saveVectorToBinStream(fileName);

	show("  Вектор до обработок", task_.data());
	cout << "\tВектор сохранен в бинарном потоке " << color(arrColor) << fileName
		<< color(mainColor) << "\n\n";

	// ввод интервала [a, b]
	float a, b;
	COORD curPos;

	cout << "\tВведите интервал [a, b]\n";

	cout << "\ta: " << color(infoColor) << setw(30) << " ";
	getXY(&curPos);
	cin >> pos(curPos.X - 29, curPos.Y) >> a >> color(mainColor);
	checkInputFormat(cin);

	cout << "\tb: " << color(infoColor) << setw(30) << " ";
	getXY(&curPos);
	cin >> pos(curPos.X - 29, curPos.Y) >> b >> color(mainColor);
	checkInputFormat(cin);

	if (a > b) {
		throw exception("a не должен быть больше b.");
	} // if

	// 1) количество отрицательных
	int negCount = task_.countNegative();

	// 2) количество не в [a, b]
	int outCount = task_.countNotInRange(a, b);

	// 3) сумма перед первым минимальным
	float sumBeforeMin = task_.sumBeforeFirstMin();

	// 4) сумма между первым минимальным и первым максимальным
	float sumBetween = task_.sumBetweenFirstMinAndFirstMax();

	cout << "\n"
		<< "\t1) Количество отрицательных: " << negCount << "\n"
		<< "\t2) Количество не в [" << fixed << setprecision(2) << a << "; " << b << "]: " << outCount << "\n"
		<< "\t3) Сумма перед первым минимальным: "<< sumBeforeMin << "\n"
		<< "\t4) Сумма между min и max: " << sumBetween << "\n\n";

	// 5) отрицательные
	vector<float> negatives = task_.selectNegatives();
	show("5) Отрицательные", negatives);
	cout << endlm(3);

	// 6) не в [a, b]
	vector<float> outOfRange = task_.selectNotInRange(a, b);
	show("6) Не в [a, b]", outOfRange);
	cout << endlm(3);

	// 7) сортировка по убыванию
	task_.orderDescending();
	show("7) По убыванию", task_.data());
	cout << endlm(3);

	// 8) сортировка по возрастанию модулей
	task_.orderByAbsAscending();
	show("8) По |x| возрастанию", task_.data());
	cout << endlm(3);

	// 9) элементы не в [a, b] в конец
	task_.moveNotInRangeToEnd(a, b);
	show("9) Не в [a, b] в конец", task_.data());

	// восстановление вектора после всех обработок
	loadVectorFromBinStream(fileName);
	cout << "\tВектор восстановлен из бинарного потока " << color(arrColor) << fileName
		<< color(mainColor) << "\n\n";

	show("После восстановления", task_.data());
	cout << endlm(3);
} // App::doTask1


void App::show(const string& title, const vector<float>& v) {
	cout << title;

	if (v.empty()) {
		cout << color(headerColor) << "    вектор пуст" << color(mainColor) << "\n";
		return;
	} // if

	cout << fixed << setprecision(2);

	int counter = 0;

	for_each(v.begin(), v.end(), [&title, &counter](float item) {
		cout << setw(8) << item;

		if (++counter % 10 == 0) {
			cout << "\n" << setw(title.length()) << " ";
		} // if
		});

	cout << "\n";
} // App::show

void App::loadVectorFromBinStream(const string& fileName) {
	fstream fs(fileName, ios::binary | ios::in);
	if (!fs.is_open()) {
		throw exception(("App: не могу открыть файл \"" + fileName + "\" для чтения").c_str());
	} // if

	vector<float> loaded;

	while (!fs.eof()) {
		float item;
		fs.read(reinterpret_cast<char*>(&item), sizeof(item));
		if (fs.fail()) break;
		loaded.emplace_back(item);
		fs.peek();
	} // while

	fs.close();

	if (loaded.empty()) {
		throw exception(("App: файл \"" + fileName + "\" не содержит данных").c_str());
	} // if

	task_.data(loaded);
} // App::loadVectorFromBinStream


void App::saveVectorToBinStream(const string& fileName) {
	fstream fs(fileName, ios::binary | ios::out | ios::trunc);
	if (!fs.is_open()) {
		throw exception(("App: не могу открыть файл \"" + fileName + "\" для записи").c_str());
	} // if

	for (auto item : task_.data()) {
		fs.write(reinterpret_cast<char*>(&item), sizeof(item));
	} // for item

	fs.close();
} // App::saveVectorToBinStream

#pragma endregion
