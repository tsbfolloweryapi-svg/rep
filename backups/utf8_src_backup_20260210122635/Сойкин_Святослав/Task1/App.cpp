#include "App.h"
#include "Utils.h"

// helper for pretty printing vector
static void printVectorVisual(const vector<float>& v, const string& title = "", int perRow = 8) {
    if (!title.empty()) cout << title << " (size=" << v.size() << "):\n";
    const int w = 10;
    for (size_t i = 0; i < v.size(); ++i) {
        cout << setw(3) << i << ": " << fixed << setprecision(4) << setw(w) << v[i];
        if ((i + 1) % perRow == 0 || i + 1 == v.size()) cout << "\n"; else cout << " ";
    }
}

App::App() : binFile_("task1_vector.bin") {
    // VectorProcess default ctor initializes internal data
}

float App::readFloatFromCin(const string &prompt) {
    cout << prompt;
    float value;
    if (!(cin >> value)) throw std::runtime_error("Invalid input");
    return value;
}

void App::saveToBinary() const {
    vectorProcess_.saveToBinary(binFile_);
}

void App::loadFromBinary() {
    vectorProcess_.loadFromBinary(binFile_);
}

void App::run() {
    init();
    // Сохраняем исходный вектор в бинарный файл перед обработками
    saveToBinary();

    // Автоматически генерируем интервал [a,b]
    float a = getRand(-50.0f, 50.0f);
    float b = a + getRand(0.0f, 100.0f);
    if (a > b) swap(a, b);
    cout << "Автогенерированный интервал: a=" << a << " b=" << b << "\n";

    // Выполнение шагов по очереди
    step_countNegative();
    step_countOutsideInterval(a, b);
    step_sumBeforeFirstMin();
    step_sumBetweenFirstMinAndFirstMax();
    step_selectNegatives();
    step_selectOutsideInterval(a, b);
    step_sortDescending();
    // Восстанавливаем исходный вектор из файла перед следующими операциями
    loadFromBinary();
    step_sortByAbsAscending();
    loadFromBinary();
    step_moveOutsideIntervalToEnd(a, b);

    // Восстанавливаем вектор из бинарного файла после всех обработок
    loadFromBinary();
    cout << "Вектор восстановлен из бинарного файла, размер=" << vectorProcess_.data().size() << "\n";
}

void App::step_countNegative() {
    const auto negCount = vectorProcess_.numberNegatives();
    cout << "1) Количество отрицательных элементов: " << negCount << "\n";
}

void App::step_countOutsideInterval(float a, float b) {
    const auto notInInterval = vectorProcess_.numberNotInRange(a, b);
    cout << "2) Количество элементов вне [a,b]: " << notInInterval << "\n";
}

void App::step_sumBeforeFirstMin() {
    const auto sumBeforeMin = vectorProcess_.sumBeforeFirstMin();
    cout << "3) Сумма перед первым минимальным элементом: " << sumBeforeMin << "\n";
}

void App::step_sumBetweenFirstMinAndFirstMax() {
    const auto sumBetween = vectorProcess_.sumBetweenFirstMinFirstMax();
    cout << "4) Сумма между первым min и первым max: " << sumBetween << "\n";
}

void App::step_selectNegatives() {
    auto negatives = vectorProcess_.fihdNegatives();
    cout << "5) Отобранные отрицательные элементы (count=" << negatives.size() << "):\n";
    if (!negatives.empty()) printVectorVisual(negatives, string());
}

void App::step_selectOutsideInterval(float a, float b) {
    auto outside = vectorProcess_.fihdNotInRange(a, b);
    cout << "6) Элементы вне [a,b] (count=" << outside.size() << "):\n";
    if (!outside.empty()) printVectorVisual(outside, string());
}

void App::step_sortDescending() {
    vectorProcess_.orderByDesc();
    cout << "7) Вектор после сортировки по убыванию:\n";
    printVectorVisual(vectorProcess_.data(), string());
}

void App::step_sortByAbsAscending() {
    vectorProcess_.orderByAbs();
    cout << "8) Вектор после сортировки по возрастанию модулей:\n";
    printVectorVisual(vectorProcess_.data(), string());
}

void App::step_moveOutsideIntervalToEnd(float a, float b) {
    vectorProcess_.orderByNotInRangeLast(a, b);
    cout << "9) Перенос элементов вне [a,b] в конец (внутри-интервал в начале):\n";
    printVectorVisual(vectorProcess_.data(), string());
}
