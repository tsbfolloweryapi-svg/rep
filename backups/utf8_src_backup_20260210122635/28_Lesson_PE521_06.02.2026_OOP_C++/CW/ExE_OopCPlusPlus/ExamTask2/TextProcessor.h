#pragma once
#include "pch.h"


class TextProcessor
{
	// возвращает вектор слов из строки, состоящей из русских букв,
	// слова разделяются одним или несколкими пробелами
	static vector<string> splitBySpace(const string &line);

public:

	// Сформировать частотный словарь
	static map<string, double> makeWordsFrequencyDict(const string &fileName);
};

