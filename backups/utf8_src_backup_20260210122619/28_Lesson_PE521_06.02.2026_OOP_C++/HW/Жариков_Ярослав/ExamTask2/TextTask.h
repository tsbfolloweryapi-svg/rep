#pragma once
#include "pch.h"
// TextTask Ч контейнер/модель дл€ обработки текста
// ƒанные: vector<string> (строки)

class TextTask
{
    vector<string> rows_;

    // ѕроверки и преобразование регистра русских букв
    bool isLetterCp1251(char ch);
    char toLowerCp1251(char ch);
    char toUpperCp1251(char ch);

    // сравнение строк без учета регистра (дл€ сортировки слов)
    bool   lessNoCaseCp1251(const string& s1, const string& s2);
    string capitalizeWord(const string& word);

    // разбор строки на слова и сборка обратно с 1 пробелом
    vector<string> splitWords(const string& row);
    string joinWordsOneSpace(const vector<string>& words);

    // собрать все слова/буквы из rows_
    vector<string> getWordsFromLines();
    vector<char>   getLettersFromLines();

public:
    //  онструкторы
    TextTask();
    TextTask(const vector<string>& rows);

    // аксессоры
    const vector<string>& rows() const;
    void rows(const vector<string>& value);

    void clear();
    // ќбработки по заданию

    // 1) „астотный словарь слов (map<string,double>)
    map<string, double> wordFrequency(int& totalWords);

    // 2) „астотный словарь букв (map<char,double>, регистро-независимо)
    map<char, double> letterFrequency(int& totalLetters);

    // 3) swap соседних строк (0<->1, 2<->3, ...)
    void swapNeighborRows();

    // 4) Capitalize (ѕерва€ «аглавна€)
    void capitalizeRows();

    // 5) сортировка строк по длине
    void orderByLen();

    // 6) сортировка слов в каждой строке по алфавиту, 1 пробел
    void orderliness();
};
