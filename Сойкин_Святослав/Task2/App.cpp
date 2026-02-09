#// Р¤Р°Р№Р»: Task2/App.cpp
#// Р”РµР№СЃС‚РІРёРµ: СЂРµР°Р»РёР·СѓРµРј РјРµС‚РѕРґС‹ РїСЂРёР»РѕР¶РµРЅРёСЏ, РІС‹РІРѕРґРёРј Рё РѕР±СЂР°Р±Р°С‚С‹РІР°РµРј С‚РµРєСЃС‚
#include "App.h"
#include "Utils.h"
#include <locale>
#include <cctype>
#include <algorithm>

App::App() : App("test.txt") {}
App::App(const string& fileName) : fileName_(fileName) {}
// выводим

// viewText
void App::viewText(const string& title, const string& fname) {
    cout << "     " << title << "\n"
        << "     +" << setfill('-') << setw(112) << "-" << "+"  // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ 8
// устанавливаем
        << setfill(' ') << "\n";

    fstream fs(fname, ios::in);
    if (!fs.is_open()) {
        throw exception(("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ " + fname + " пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ").c_str());
    }
    fs.imbue(locale(".1251"));
// выполняем действие

    int row = 1;
    string line;
    while (getline(fs, line)) {
        cout << " " << setfill('0') << setw(3) << row++ << setfill(' ')
            << " | " << left << setw(110) << line << right << " |\n";  // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ 8
    }
    fs.close();
    cout << "     +" << setfill('-') << setw(112) << "-" << "+"
        << setfill(' ') << "\n";
// выводим
}

// show
void App::show(const string& title, const map<string, double>& freqDict) {
// устанавливаем
    cout << "    " << title << "\n" << setprecision(3);

    int counter = 1;
    for (const auto& item : freqDict) {
// устанавливаем
        cout << "    " << left << setw(20) << item.first << right
            << setw(5) << item.second << " || ";
        if (counter++ % 3 == 0) {
            cout << "\n";
        }
    }
    cout << "\n";
// выполняем действие
}

// doFreqDictWords
void App::doFreqDictWords() {
    cls();
    viewText("пїЅпїЅпїЅпїЅ " + fileName_ + ", пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ:", fileName_);
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ");

    try {
// выполняем действие
        map<string, double> freqDict = TextProcessor::makeWordsFrequencyDict(fileName_);
        show("\n\n    пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅ " + fileName_ + ":", freqDict);
    }
    catch (const exception& ex) {
        cout << color(errColor) << "пїЅпїЅпїЅпїЅпїЅпїЅ: " << ex.what() << color(mainColor) << "\n";
    }

    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ...");
// выполняем действие
}

// doFreqDictLetters
void App::doFreqDictLetters() {
    cls();
    viewText("пїЅпїЅпїЅпїЅ " + fileName_ + ", пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ:", fileName_);
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ");

    try {
// выполняем действие
        map<string, double> freqDict = TextProcessor::makeLettersFrequencyDict(fileName_);
        show("\n\n    пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅ " + fileName_ + ":", freqDict);
    }
    catch (const exception& ex) {
        cout << color(errColor) << "пїЅпїЅпїЅпїЅпїЅпїЅ: " << ex.what() << color(mainColor) << "\n";
    }

    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ...");
// перемещаем элементы
}

// doSwapLines
void App::doSwapLines() {
    cls();
    viewText("пїЅпїЅпїЅпїЅ " + fileName_ + ", пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ:", fileName_);
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ");

    try {
        fstream in(fileName_, ios::in);
        if (!in.is_open()) throw runtime_error(("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ " + fileName_).c_str());
        in.imbue(locale(".1251"));
// выполняем действие

        vector<string> lines;
        string line;
        while (getline(in, line)) {
            lines.push_back(line);
        }
        in.close();

        for (size_t i = 0; i + 1 < lines.size(); i += 2) {
            swap(lines[i], lines[i + 1]);
        }

        string outFile = "swap.txt";
// выполняем действие
        ofstream out(outFile);
        if (!out.is_open()) throw runtime_error(("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ " + outFile).c_str());
        out.imbue(locale(".1251"));
        for (const auto& l : lines) {
            out << l << "\n";
        }
        out.close();

        cout << "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ " << outFile << "\n";
// очищаем экран
        cls();
        viewText("пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ " + outFile + ":", outFile);
    }
    catch (const exception& ex) {
        cout << color(errColor) << "пїЅпїЅпїЅпїЅпїЅпїЅ: " << ex.what() << color(mainColor) << "\n";
    }

    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ...");
// выполняем действие
}

// doWordsCapitalize
void App::doWordsCapitalize() {
    cls();
    viewText("пїЅпїЅпїЅпїЅ " + fileName_ + ", пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ:", fileName_);
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ capitalize");

    try {
        fstream in(fileName_, ios::in);
        if (!in.is_open()) throw runtime_error(("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ " + fileName_).c_str());
        in.imbue(locale(".1251"));
// выполняем действие

        vector<string> lines;
        string line;
        while (getline(in, line)) {
            lines.push_back(line);
        }
// выполняем действие
        in.close();

        vector<string> newLines;
        for (auto l : lines) {
// выполняем действие
            stringstream ss(l);
            string newL, word;
            while (ss >> word) {
// выполняем действие
                if (!word.empty()) {
                    word[0] = toupper(static_cast<unsigned char>(word[0]));
// выполняем действие
                    transform(word.begin() + 1, word.end(), word.begin() + 1, [](unsigned char c) { return tolower(c); });
                }
                newL += word + " ";
            }
            if (!newL.empty()) newL.pop_back();
            newLines.push_back(newL);
        }

        string outFile = "capitalize.txt";
// выполняем действие
        ofstream out(outFile);
        if (!out.is_open()) throw runtime_error(("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ " + outFile).c_str());
        out.imbue(locale(".1251"));
        for (const auto& l : newLines) {
            out << l << "\n";
        }
        out.close();

        cout << "пїЅпїЅпїЅпїЅпїЅ пїЅ capitalize пїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ " << outFile << "\n";
// очищаем экран
        cls();
        viewText("пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ " + outFile + ":", outFile);
    }
    catch (const exception& ex) {
        cout << color(errColor) << "пїЅпїЅпїЅпїЅпїЅпїЅ: " << ex.what() << color(mainColor) << "\n";
    }

    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ...");
// выполняем действие
}

// doOrderByLen
void App::doOrderByLen() {
    cls();
    viewText("пїЅпїЅпїЅпїЅ " + fileName_ + ", пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ:", fileName_);
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ");

    try {
        fstream in(fileName_, ios::in);
        if (!in.is_open()) throw runtime_error(("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ " + fileName_).c_str());
        in.imbue(locale(".1251"));
// выполняем действие

        vector<string> lines;
        string line;
        while (getline(in, line)) {
            lines.push_back(line);
        }
        in.close();

// сортируем
        sort(lines.begin(), lines.end(), [](const string& a, const string& b) { return a.length() < b.length(); });

        string outFile = "orderByLen.txt";
// выполняем действие
        ofstream out(outFile);
        if (!out.is_open()) throw runtime_error(("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ " + outFile).c_str());
        out.imbue(locale(".1251"));
        for (const auto& l : lines) {
            out << l << "\n";
        }
        out.close();

        cout << "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ " << outFile << "\n";
// очищаем экран
        cls();
        viewText("пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ " + outFile + ":", outFile);
    }
    catch (const exception& ex) {
        cout << color(errColor) << "пїЅпїЅпїЅпїЅпїЅпїЅ: " << ex.what() << color(mainColor) << "\n";
    }

    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ...");
// выполняем действие
}

// doOrderWordsInLines
void App::doOrderWordsInLines() {
    cls();
    viewText("пїЅпїЅпїЅпїЅ " + fileName_ + ", пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ:", fileName_);
    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ");

    try {
        fstream in(fileName_, ios::in);
        if (!in.is_open()) throw runtime_error(("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ " + fileName_).c_str());
        in.imbue(locale(".1251"));
// выполняем действие

        vector<string> lines;
        string line;
        while (getline(in, line)) {
            lines.push_back(line);
        }
// выполняем действие
        in.close();

        vector<string> newLines;
        for (const auto& l : lines) {
// выполняем действие
            vector<string> words = TextProcessor::splitBySpace(l);
            sort(words.begin(), words.end(), [](const string& a, const string& b) {
                string la = a, lb = b;
// выполняем действие
                transform(la.begin(), la.end(), la.begin(), [](unsigned char c) { return tolower(c); });
// выполняем действие
                transform(lb.begin(), lb.end(), lb.begin(), [](unsigned char c) { return tolower(c); });
// выполняем действие
                return la < lb;
                });
            string newL;
            for (const auto& w : words) {
                newL += w + " ";
            }
            if (!newL.empty()) newL.pop_back();
            newLines.push_back(newL);
        }

        string outFile = "orderliness.txt";
// выполняем действие
        ofstream out(outFile);
        if (!out.is_open()) throw runtime_error(("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ " + outFile).c_str());
        out.imbue(locale(".1251"));
        for (const auto& l : newLines) {
            out << l << "\n";
        }
        out.close();

        cout << "пїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ " << outFile << "\n";
// очищаем экран
        cls();
        viewText("пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ " + outFile + ":", outFile);
    }
    catch (const exception& ex) {
        cout << color(errColor) << "пїЅпїЅпїЅпїЅпїЅпїЅ: " << ex.what() << color(mainColor) << "\n";
    }

    getKey("\nпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ...");
}
