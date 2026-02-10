#pragma once
#include "pch.h"
#include "TextProcessor.h"

class App
{
	string fileName_;

	void viewText(const string &title);

	// Вывод частотного словаря слов
	void show(const string &title, const map<string, double> &freqDict);

public:
	App();
	App(const string& fileName);

	// Сформируйте частотный словарь слов текста. Ключом является слово, 
    // значением – количество таких слов в тексте, деленное на общее 
    // количество слов в тексте.
	void doFreqDictWords();

	void doFreqDictLetters();
	
	void doSwapLines();
	
	void doWordsCapitalize();
	
	void doOrderByLen();
	
	void doOrderWordsInLines();
};

