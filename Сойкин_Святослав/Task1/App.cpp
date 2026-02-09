// Р¤Р°Р№Р»: Task1/App.cpp
// РћРїРёСЃР°РЅРёРµ: Р РµР°Р»РёР·Р°С†РёСЏ РєР»Р°СЃСЃР° `App` вЂ” РѕСЃРЅРѕРІРЅР°СЏ Р»РѕРіРёРєР° Р·Р°РґР°РЅРёСЏ РїРѕ СЂР°Р±РѕС‚Рµ СЃ РІРµРєС‚РѕСЂР°РјРё.
// РџСЂРёРјРµС‡Р°РЅРёРµ: Р”РѕР±Р°РІР»РµРЅС‹ РїРѕСЏСЃРЅСЏСЋС‰РёРµ РєРѕРјРјРµРЅС‚Р°СЂРёРё Рё СѓР»СѓС‡С€РµРЅР° С‡РёС‚Р°РµРјРѕСЃС‚СЊ.
#include "App.h"
// выводим
#include "Utils.h"

// Р’СЃРїРѕРјРѕРіР°С‚РµР»СЊРЅР°СЏ С„СѓРЅРєС†РёСЏ: РІС‹РІРѕРґ РІРµРєС‚РѕСЂР° РІ РІРёР·СѓР°Р»СЊРЅРѕРј РІРёРґРµ
static void printVectorVisual(const vector<float>& v, const string& title = "", int perRow = 8) {
    if (!title.empty()) cout << title << " (size=" << v.size() << "):\n";
    const int w = 10;
    for (size_t i = 0; i < v.size(); ++i) {
        cout << setw(3) << i << ": " << fixed << setprecision(4) << setw(w) << v[i];
        if ((i + 1) % perRow == 0 || i + 1 == v.size()) cout << "\n"; else cout << " ";
    }
}

// РљРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ: РёРЅРёС†РёР°Р»РёР·РёСЂСѓРµС‚ РІРµРєС‚РѕСЂ СЃР»СѓС‡Р°Р№РЅС‹С… Р·РЅР°С‡РµРЅРёР№ Рё РёРјСЏ Р±РёРЅР°СЂРЅРѕРіРѕ С„Р°Р№Р»Р°
App::App() : binFile_("task1_vector.bin") {
    // РЎР»СѓС‡Р°Р№РЅС‹Р№ СЂР°Р·РјРµСЂ РІРµРєС‚РѕСЂР° РІ РґРёР°РїР°Р·РѕРЅРµ [12, 30]
    int n = getRand(12, 30);
    v_.assign(n, 0.0f);
    for (auto &x : v_) x = getRand(-100.0f, 100.0f);
// выполняем действие
}

// пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ)
float App::readFloatFromCin(const string &prompt) {
    // РџСЂРѕСЃС‚РѕР№ РІРІРѕРґ float СЃ РїСЂРѕРІРµСЂРєРѕР№ С„РѕСЂРјР°С‚Р°
    cout << prompt;
    float value;
    if (!(cin >> value)) throw std::runtime_error("Invalid input");
// сохраняем в файл
    return value;
}

void App::saveToBinary() const {
    ofstream out(binFile_, ios::binary | ios::out | ios::trunc);
    if (!out.is_open()) throw std::runtime_error("РќРµ СѓРґР°Р»РѕСЃСЊ РѕС‚РєСЂС‹С‚СЊ С„Р°Р№Р» РґР»СЏ Р·Р°РїРёСЃРё");

    size_t n = v_.size();
    out.write(reinterpret_cast<const char*>(&n), sizeof(n));
    if (n) out.write(reinterpret_cast<const char*>(v_.data()), n * sizeof(float));
// выполняем действие
    if (out.fail()) throw std::runtime_error("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ");
}

void App::loadFromBinary() {
    ifstream in(binFile_, ios::binary | ios::in);
    if (!in.is_open()) throw std::runtime_error("РќРµ СѓРґР°Р»РѕСЃСЊ РѕС‚РєСЂС‹С‚СЊ С„Р°Р№Р» РґР»СЏ С‡С‚РµРЅРёСЏ");

    size_t n = 0;
    in.read(reinterpret_cast<char*>(&n), sizeof(n));
// выполняем действие
    if (in.fail()) throw std::runtime_error("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ");

    vector<float> tmp;
    if (n) {
        tmp.resize(n);
        in.read(reinterpret_cast<char*>(tmp.data()), n * sizeof(float));
        if (in.fail()) throw std::runtime_error("пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ");
    }

// перемещаем элементы
    v_.swap(tmp);
}

void App::run() {
    init();
    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    saveToBinary();

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ [a,b]
    float a = getRand(-50.0f, 50.0f);
    float b = a + getRand(0.0f, 100.0f);
    if (a > b) swap(a, b);
    cout << "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ: a=" << a << " b=" << b << "\n";

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    step_countNegative();
    step_countOutsideInterval(a, b);
    step_sumBeforeFirstMin();
    step_sumBetweenFirstMinAndFirstMax();
    step_selectNegatives();
    step_selectOutsideInterval(a, b);
    step_sortDescending();
    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    loadFromBinary();
    step_sortByAbsAscending();
    loadFromBinary();
    step_moveOutsideIntervalToEnd(a, b);

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    loadFromBinary();
    cout << "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅ=" << v_.size() << "\n";
// считаем
}

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
void App::step_countNegative() {
    const auto negCount = count_if(v_.begin(), v_.end(), [](float x){ return x < 0.0f; });
// считаем
    cout << "1) пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ: " << negCount << "\n";
}

void App::step_countOutsideInterval(float a, float b) {
    const auto notInInterval = count_if(v_.begin(), v_.end(), [a,b](float x){ return x < a || x > b; });
// суммируем
    cout << "2) пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ [a,b]: " << notInInterval << "\n";
}

void App::step_sumBeforeFirstMin() {
    const auto itMin = min_element(v_.begin(), v_.end());
    const float sumBeforeMin = (itMin == v_.begin() || itMin == v_.end()) ? 0.0f : accumulate(v_.begin(), itMin, 0.0f);
// суммируем
    cout << "3) пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ: " << sumBeforeMin << "\n";
}

void App::step_sumBetweenFirstMinAndFirstMax() {
// выполняем действие
    const auto itMin = min_element(v_.begin(), v_.end());
    const auto itMax = max_element(v_.begin(), v_.end());
    float sumBetween = 0.0f;
    if (itMin != v_.end() && itMax != v_.end() && itMin != itMax) {
        auto first = min(itMin, itMax);
        auto last = max(itMin, itMax);
        if (distance(first, last) > 1) sumBetween = accumulate(next(first), last, 0.0f);
    }
// фильтруем
    cout << "4) пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ min пїЅ пїЅпїЅпїЅпїЅпїЅпїЅ max: " << sumBetween << "\n";
}

void App::step_selectNegatives() {
    vector<float> negatives;
// фильтруем
    copy_if(v_.begin(), v_.end(), back_inserter(negatives), [](float x){ return x < 0.0f; });
    cout << "5) пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ (count=" << negatives.size() << ":\n";
// выполняем действие
    if (!negatives.empty()) printVectorVisual(negatives, string());
}

void App::step_selectOutsideInterval(float a, float b) {
    vector<float> outside;
// фильтруем
    copy_if(v_.begin(), v_.end(), back_inserter(outside), [a,b](float x){ return x < a || x > b; });
    cout << "6) пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ [a,b] (count=" << outside.size() << ":\n";
// выполняем действие
    if (!outside.empty()) printVectorVisual(outside, string());
}

void App::step_sortDescending() {
    sort(v_.begin(), v_.end(), greater<float>());
    cout << "7) пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ:\n";
// выводим
    printVectorVisual(v_, string());
}

void App::step_sortByAbsAscending() {
// сортируем
    sort(v_.begin(), v_.end(), [](float lhs, float rhs){ return fabs(lhs) < fabs(rhs); });
    cout << "8) пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ:\n";
// выводим
    printVectorVisual(v_, string());
}

void App::step_moveOutsideIntervalToEnd(float a, float b) {
// перемещаем элементы
    stable_partition(v_.begin(), v_.end(), [a,b](float x){ return x >= a && x <= b; });
    cout << "9) пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ [a,b] пїЅ пїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅпїЅпїЅ-пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅ):\n";
    printVectorVisual(v_, string());
}
