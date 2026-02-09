#include "pch.h"
#// Р¤Р°Р№Р»: Task2/TextProcessor.cpp
#// Р”РµР№СЃС‚РІРёРµ: РѕР±СЂР°Р±Р°С‚С‹РІР°РµРј С‚РµРєСЃС‚ Рё С„РѕСЂРјРёСЂСѓРµРј СЃР»РѕРІР°СЂРё/С‡Р°СЃС‚РѕС‚С‹
#include "TextProcessor.h"
#include <locale>
#include <cctype>

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
map<string, double> TextProcessor::makeWordsFrequencyDict(const string& fileName) {
// выполняем действие
    map<string, double> freqDict;

    fstream fs(fileName, ios::in);
    if (!fs.is_open()) {
        throw exception(("TextProcessor: пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ " + fileName).c_str());
    }
    fs.imbue(locale(".1251"));
// выполняем действие

    int wordsCounter = 0;
    string line;
    while (getline(fs, line)) {
// выполняем действие
        if (line.empty()) continue;

        vector<string> words = splitBySpace(line);
        for (const auto& word : words) {
            freqDict[word] += 1.0;
        }
// выполняем действие
        wordsCounter += static_cast<int>(words.size());
    }
    fs.close();
    if (wordsCounter > 0) {
// выполняем действие
        for (auto& item : freqDict) {
            item.second /= wordsCounter;
        }
    }
    return freqDict;
}

map<string, double> TextProcessor::makeLettersFrequencyDict(const string& fileName) {
// выполняем действие
    map<string, double> freqDict;

    fstream fs(fileName, ios::in);
    if (!fs.is_open()) {
        throw exception(("TextProcessor: пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ " + fileName).c_str());
    }
    fs.imbue(locale(".1251"));
// выполняем действие

    string text;
    string line;
    while (getline(fs, line)) {
        if (!text.empty()) text += ' ';
        text += line;
    }
// выполняем действие
    fs.close();

    int lettersCounter = 0;
    for (char c : text) {
// выполняем действие
        if (isalpha(static_cast<unsigned char>(c))) {
            char lowerC = tolower(static_cast<unsigned char>(c));
            freqDict[string(1, lowerC)] += 1;
            lettersCounter++;
// выполняем действие
        }
    }

    if (lettersCounter > 0) {
// выполняем действие
        for (auto& item : freqDict) {
            item.second /= lettersCounter;
        }
    }
    return freqDict;
// выполняем действие
}

// splitBySpace
vector<string> TextProcessor::splitBySpace(const string& line) {
// выполняем действие
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word) {
        if (!word.empty()) words.emplace_back(word);
    }
    return words;
}
