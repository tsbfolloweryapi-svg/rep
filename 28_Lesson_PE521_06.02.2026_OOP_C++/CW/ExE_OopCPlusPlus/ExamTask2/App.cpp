#include "App.h"
#include "Utils.h"

App::App() :App("test.txt") {}
App::App(const string& fileName) {
	fileName_ = fileName;
} // App::App

// Сформируйте частотный словарь слов текста. Ключом является слово, 
// значением – количество таких слов в тексте, деленное на общее 
// количество слов в тексте.
void App::doFreqDictWords() {
	showNavBarMessage(hintColor, "    Ыормирование частотного словаря слов текста");

	// Показать файл для обработки
	viewText("Файл " + fileName_ + ", текст для обработки:");

	// Сформировать частотный словарь
	map<string, double> freqDict = TextProcessor::makeWordsFrequencyDict(fileName_);

	// Вывести словарь
	show("\n\n    Частотный словарь слов текста, файл " + fileName_ + ":", freqDict);
} // App::doFreqDictWords


void App::doFreqDictLetters() {}

void App::doSwapLines() {}

void App::doWordsCapitalize() {}

void App::doOrderByLen() {}

void App::doOrderWordsInLines() {}


// -------------------------------------------------------

void App::viewText(const string & title) {
	cout<< "     " << title << "\n"
		<< "     +" << setfill('-') << setw(92) << "-" << "+" 
		<< setfill(' ') << "\n";

	fstream fs(fileName_, ios::in);

	if (!fs.is_open()) {
		throw exception(("App: Ошибка открытия файла " + fileName_ + " для чтения").c_str());
	} // if

	// задать кодировку потока вывода CP1251  
	fs.imbue(locale(".1251"));

	int row = 1;
	while (!fs.eof()) {
		string line;
		getline(fs, line);

		cout << " " << setfill('0') << setw(3) << row++ << setfill(' ')
			<< " | " << left << setw(90) << line << right << " |\n";

		fs.peek();
	} // ehile

	fs.close();
	cout<< "     +" << setfill('-') << setw(92) << "-" << "+"
		<< setfill(' ') << "\n";
} // App::viewText


// Вывод частотного словаря слов
void App::show(const string& title, const map<string, double>& freqDict) {
	cout << "    " << title << "\n" << setprecision(3);
	
	int counter = 1;
	for (auto &item: freqDict) {
		cout<< "    " << left << setw(20) << item.first << right
			<< setw(5) << item.second << " || ";

		if (counter++ % 3
			== 0) {
			cout << "\n";
		} // if
	} // for item 
} // App::show 
