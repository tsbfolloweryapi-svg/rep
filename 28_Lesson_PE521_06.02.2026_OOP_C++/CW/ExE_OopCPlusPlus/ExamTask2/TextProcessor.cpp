#include "TextProcessor.h"

// Сформировать частотный словарь
map<string, double> TextProcessor::makeWordsFrequencyDict(const string& fileName)
{
	map<string, double> freqDict;
	
	fstream fs(fileName, ios::in);

	if (!fs.is_open()) {
		throw exception(("TextProcessor: Ошибка открытия файла " + fileName + " для чтения").c_str());
	} // if

	// задать кодировку потока вывода CP1251  
	fs.imbue(locale(".1251"));

	// Построчное чтение и обработка файла
	int wordsCounter = 0;
	for (; !fs.eof(); fs.peek()) {
		string line;
		getline(fs, line);

		// не обрабатываем пустую строку
		if (line.empty()) { 
			continue; 
		} // if

		// Построчная обработка: выделение слов, 
		// подсчет общего количества слов,
		// заполнение словаря
		vector<string> words = splitBySpace(line);
		for (auto word: words) {
			freqDict[word] += 1;
		} // for word

		wordsCounter += words.size();
	} // ehile

	fs.close();

	// нормирование словаря: поделить в каждой паре количество слов
	// на общее количество слов в тексте
	for (auto& item : freqDict) {
		item.second /= wordsCounter;
	} // for item
	
	return freqDict;
} // TextProcessor::makeWordsFrequencyDict


// возвращает вектор слов из строки, состоящей из русских букв,
// слова разделяются одним или несколкими пробелами
vector<string> TextProcessor::splitBySpace(const string& line) {
	vector<string> words;

	stringstream ss(line);

	while (!ss.fail()) {
		string word;
		ss >> word;

		// игнорируем пустые строки, которые образуются
		// из-за двух поодряд идущих пробелов
		if (word.empty()) {
			continue;
		} // if

		// cout << "DEBUG: " << word << "\n";
		words.emplace_back(word);
	} // while

	return words;
} // TextProcessor::splitBySpace
