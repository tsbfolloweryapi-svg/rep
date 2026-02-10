#pragma once

#include "pch.h"
#include "TextTask.h"

class App
{
    string txtFileName_;

    vector<string> readLines();
    void writeLines(const string& fileName, const vector<string>& rows);

    void showTextFile(const string& fileName, const string& title);

    // вывод таблиц частот
    void showWordFreqTable(const map<string, double>& freq);
    void showLetterFreqTable(const map<char, double>& freq);

public:
    App();
    App(const string& txtFile);

    // пункты меню
    void doWordFrequency();
    void doLetterFrequency();
    void doSwapRows();
    void doCapitalize();
    void doOrderByLen();
    void doOrderliness();
};
