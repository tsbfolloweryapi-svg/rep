#include "pch.h"
#include "Utils.h"
#include "App.h"

#include "FileException.h"
// Конструкторы

App::App() : App("test.txt") {}

App::App(const string& txtFile) : txtFileName_(txtFile) {
} // App::App

// Чтение строк файла в vector<string>
vector<string> App::readLines() {
    ifstream ifs(txtFileName_);
    if (!ifs.is_open()) {
        throw FileException(
            "App: не могу открыть текстовый поток для чтения из файл "s,
            txtFileName_
        );
    } // if

    ifs.imbue(locale(".1251"));

    vector<string> rows;
    while (!ifs.eof()) {
        string row;
        getline(ifs, row);
        rows.emplace_back(row);
        ifs.peek();
    } // while

    ifs.close();
    return rows;
} // App::readLines

// Запись строк в файл
void App::writeLines(const string& fileName, const vector<string>& rows) {
    ofstream ofs(fileName);
    if (!ofs.is_open()) {
        throw FileException(
            "App: не могу открыть текстовый поток для записи в файл "s,
            fileName
        );
    } // if

    ofs.imbue(locale(".1251"));

    for_each(rows.begin(), rows.end(), [&](const string& row) {
        ofs << row << "\n";
        });

    ofs.close();
} // App::writeLines

// Вывод текстового файла в консоль (нумерация строк)
void App::showTextFile(const string& fileName, const string& title) {
    ifstream ifs;

    ifs.open(fileName);
    if (!ifs.is_open()) {
        throw FileException(
            "App: не могу открыть текстовый поток для чтения из файл "s,
            fileName
        );
    } // if

    ifs.imbue(locale(".1251"));

    vector<string> rows;
    while (!ifs.eof()) {
        string row;
        getline(ifs, row);
        rows.emplace_back(row);
        ifs.peek();
    } // while

    ifs.close();

    cout << "\n\n"
        << color(sumColor) << "    Файл " << fileName
        << title
        << "    " << string(80, '-')
        << color(mainColor) << "\n";

    int i = 1;
    for_each(rows.begin(), rows.end(), [&](const string& row) {
        cout << "    " << setfill('0') << setw(2)
            << color(sumColor) << i++ << color(mainColor) << ": "
            << setfill(' ')
            << row << "\n";
        });
} // App::showTextFile

// Вывод таблицы слов
void App::showWordFreqTable(const map<string, double>& freq) {
    cout << left
        << "    " << setw(5) << "№"
        << setw(50) << "Слово"
        << setw(12) << "Частота"
        << "\n"
        << "    " << string(80, '-') << "\n";

    int n = 1;
    for_each(freq.begin(), freq.end(), [&](const pair<const string, double>& p) {
        cout << "    " << setw(5) << n++
            << setw(50) << p.first
            << setw(12) << p.second
            << "\n";
        });
} // App::showWordFreqTable

// Вывод таблицы букв
void App::showLetterFreqTable(const map<char, double>& freq) {
    cout << left
        << "    " << setw(5) << "№"
        << setw(8) << "Буква"
        << setw(12) << "Частота"
        << "\n"
        << "    " << string(80, '-') << "\n";

    int n = 1;
    for_each(freq.begin(), freq.end(), [&](const pair<const char, double>& p) {
        cout << "    " << setw(5) << n++
            << setw(8) << p.first
            << setw(12) << p.second
            << "\n";
        });
} // App::showLetterFreqTable

// 1) Частотный словарь слов (map<string,double>)
void App::doWordFrequency() {
    showNavBarMessage(hintColor, "  Частотный словарь слов текста (map<string,double>)");

    vector<string> rows = readLines();
    TextTask task(rows);

    int totalWords = 0;
    map<string, double> freq = task.wordFrequency(totalWords);

    cout << fixed << setprecision(5)
        << endlm(4)
        << color(sumColor) << "    Файл " << txtFileName_
        << ", всего слов: " << totalWords << "\n"
        << "    " << string(80, '-') << color(mainColor) << "\n";

    if (totalWords == 0) {
        cout << "    (нет слов)\n";
        return;
    } // if

    showWordFreqTable(freq);

    cout << right
        << color(sumColor) << "    " << string(80, '-') << color(mainColor) << "\n";
} // App::doWordFrequency

// 2) Частотный словарь букв (map<char,double>)
void App::doLetterFrequency() {
    showNavBarMessage(hintColor, "  Частотный словарь букв текста (map<char,double>, регистро-независимо)");

    vector<string> rows = readLines();
    TextTask task(rows);

    int totalLetters = 0;
    map<char, double> freq = task.letterFrequency(totalLetters);

    cout << fixed << setprecision(5)
        << endlm(4)
        << color(sumColor) << "    Файл " << txtFileName_
        << ", всего букв: " << totalLetters << "\n"
        << "    " << string(80, '-') << color(mainColor) << "\n";

    if (totalLetters == 0) {
        cout << "    (нет букв)\n";
        return;
    } // if

    showLetterFreqTable(freq);

    cout << right
        << color(sumColor) << "    " << string(80, '-') << color(mainColor) << "\n";
} // App::doLetterFrequency

// 3) Swap соседних строк -> swap.txt
void App::doSwapRows() {
    showNavBarMessage(hintColor, "  Поменять местами каждые две соседние строки -> swap.txt");

    TextTask task(readLines());
    task.swapNeighborRows();

    const string outFileName = "swap.txt";
    writeLines(outFileName, task.rows());

    showTextFile(outFileName, " после обмена пар строк:\n");
    cout << color(sumColor) << "    " << string(80, '-') << color(mainColor) << "\n";
} // App::doSwapRows

// 4) Capitalize -> capitalize.txt
void App::doCapitalize() {
    showNavBarMessage(hintColor, "  Перевести слова в формат: Первая Заглавная -> capitalize.txt");

    TextTask task(readLines());
    task.capitalizeRows();

    const string outFileName = "capitalize.txt";
    writeLines(outFileName, task.rows());

    showTextFile(outFileName, " после приведения слов к виду 'Первая Заглавная':\n");
    cout << color(sumColor) << "    " << string(80, '-') << color(mainColor) << "\n";
} // App::doCapitalize

// 5) Упорядочить строки по длине -> orderByLen.txt
void App::doOrderByLen() {
    showNavBarMessage(hintColor, "  Упорядочить строки по длине -> orderByLen.txt");

    TextTask task(readLines());
    task.orderByLen();

    const string outFileName = "orderByLen.txt";
    writeLines(outFileName, task.rows());

    showTextFile(outFileName, " после сортировки строк по длине:\n");
    cout << color(sumColor) << "    " << string(80, '-') << color(mainColor) << "\n";
} // App::doOrderByLen

// 6) В каждой строке слова по алфавиту -> orderliness.txt
void App::doOrderliness() {
    showNavBarMessage(hintColor, "  В каждой строке слова по алфавиту, 1 пробел -> orderliness.txt");

    TextTask task(readLines());
    task.orderliness();

    const string outFileName = "orderliness.txt";
    writeLines(outFileName, task.rows());

    showTextFile(outFileName, " после сортировки слов в каждой строке:\n");
    cout << color(sumColor) << "    " << string(80, '-') << color(mainColor) << "\n";
} // App::doOrderliness
