#include "pch.h"
#include "TextTask.h"

// Конструкторы
TextTask::TextTask() : TextTask(vector<string>()) {}

TextTask::TextTask(const vector<string>& rows) {
    this->rows(rows);
} // TextTask::TextTask

// Аксессоры
const vector<string>& TextTask::rows() const { return rows_; } // TextTask::rows
void TextTask::rows(const vector<string>& value) { rows_ = value; } // TextTask::rows

void TextTask::clear() { rows_.clear(); } // TextTask::clear

bool TextTask::isLetterCp1251(char ch)  {
    return (ch >= 'А' && ch <= 'Я')
        || (ch >= 'а' && ch <= 'я')
        || ch == 'Ё'
        || ch == 'ё';
} // TextTask::isLetterCp1251


char TextTask::toLowerCp1251(char ch)  {
    if (ch == 'Ё') return 'ё';

    if (ch >= 'А' && ch <= 'Я') {
        ch = ch + 32;
    } // if

    return ch;
} // TextTask::toLowerCp1251


char TextTask::toUpperCp1251(char ch) {
    if (ch == 'ё') return 'Ё';

    if (ch >= 'а' && ch <= 'я') {
        ch = ch - 32;
    } // if

    return ch;
} // TextTask::toUpperCp1251


bool TextTask::lessNoCaseCp1251(const string& s1, const string& s2)  {
    string a = s1;
    string b = s2;

    transform(a.begin(), a.end(), a.begin(), [&](char ch) { return toLowerCp1251(ch); });
    transform(b.begin(), b.end(), b.begin(), [&](char ch) { return toLowerCp1251(ch); });

    return a < b;
} // TextTask::lessNoCaseCp1251


string TextTask::capitalizeWord(const string& word) {
    string res = word;

    // всё -> нижний регистр
    transform(res.begin(), res.end(), res.begin(), [&](char ch) { return toLowerCp1251(ch); });

    // первая буква (именно буква) -> верхний регистр
    auto it = find_if(res.begin(), res.end(), [&](char ch) { return isLetterCp1251(ch); });
    if (it != res.end()) {
        *it = toUpperCp1251(*it);
    } // if

    return res;
} // TextTask::capitalizeWord

// Разбор/сборка строки
vector<string> TextTask::splitWords(const string& row)  {
    istringstream iss(row);
    vector<string> words;

    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
    return words;
} // TextTask::splitWords


string TextTask::joinWordsOneSpace(const vector<string>& words)  {
    if (words.empty()) return ""s;

    ostringstream oss;
    oss << words[0];

    for_each(words.begin() + 1, words.end(), [&](const string& w) {
        oss << " " << w;
        });

    return oss.str();
} // TextTask::joinWordsOneSpace

// Сбор всех слов/букв из rows_
vector<string> TextTask::getWordsFromLines()  {
    vector<string> words;

    for_each(rows_.begin(), rows_.end(), [&](const string& row) {
        istringstream iss(row);
        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(words));
        });

    return words;
} // TextTask::getWordsFromLines


vector<char> TextTask::getLettersFromLines()  {
    vector<char> letters;

    for_each(rows_.begin(), rows_.end(), [&](const string& row) {
        for_each(row.begin(), row.end(), [&](char ch) {
            if (isLetterCp1251(ch)) {
                letters.emplace_back(toLowerCp1251(ch));
            } // if
            });
        });

    return letters;
} // TextTask::getLettersFromLines

// 1) Частотный словарь слов
map<string, double> TextTask::wordFrequency(int& totalWords)  {
    vector<string> words = getWordsFromLines();
    totalWords = (int)words.size();

    map<string, double> freq;

    if (totalWords == 0) return freq;

    // сначала считаем количество (в double), потом делим на totalWords
    for_each(words.begin(), words.end(), [&](const string& w) {
        ++freq[w];
        });

    for_each(freq.begin(), freq.end(), [&](pair<const string, double>& p) {
        p.second /= totalWords;
        });

    return freq;
} // TextTask::wordFrequency

// 2) Частотный словарь букв (регистро-независимо)
map<char, double> TextTask::letterFrequency(int& totalLetters)  {
    vector<char> letters = getLettersFromLines();
    totalLetters = (int)letters.size();

    map<char, double> freq;

    if (totalLetters == 0) return freq;

    for_each(letters.begin(), letters.end(), [&](char ch) {
        ++freq[ch];
        });

    for_each(freq.begin(), freq.end(), [&](pair<const char, double>& p) {
        p.second /= totalLetters;
        });

    return freq;
} // TextTask::letterFrequency

// 3) Поменять местами каждые две соседние строки
void TextTask::swapNeighborRows() {
    size_t i = 0;

    for_each(rows_.begin(), rows_.end(), [&](string& row) {
        if ((i & 1) == 0 && i + 1 < rows_.size()) {
            swap(row, rows_[i + 1]);
        } // if
        ++i;
        });
} // TextTask::swapNeighborRows

// 4) Capitalize
void TextTask::capitalizeRows() {
    for_each(rows_.begin(), rows_.end(), [&](string& row) {
        if (row.empty()) return;

        vector<string> words = splitWords(row);

        transform(words.begin(), words.end(), words.begin(),
            [&](const string& w) { return capitalizeWord(w); });

        row = joinWordsOneSpace(words);
        });
} // TextTask::capitalizeRows

// 5) Сортировка строк по длине
void TextTask::orderByLen() {
    sort(rows_.begin(), rows_.end(),
        [](const string& a, const string& b) { return a.length() < b.length(); });
} // TextTask::orderByLen

// 6) В каждой строке слова по алфавиту, 1 пробел
void TextTask::orderliness() {
    for_each(rows_.begin(), rows_.end(), [&](string& row) {
        if (row.empty()) return;

        vector<string> words = splitWords(row);

        sort(words.begin(), words.end(),
            [&](const string& a, const string& b) { return lessNoCaseCp1251(a, b); });

        row = joinWordsOneSpace(words);
        });
} // TextTask::orderliness
