#// Файл: Task2/TextProcessor.h
#// Действие: объявляем функции для обработки текста
#pragma once
#include "pch.h"

class TextProcessor {

public:
    static vector<string> splitBySpace(const string& line);
    static map<string, double> makeWordsFrequencyDict(const string& fileName);
    static map<string, double> makeLettersFrequencyDict(const string& fileName);
};