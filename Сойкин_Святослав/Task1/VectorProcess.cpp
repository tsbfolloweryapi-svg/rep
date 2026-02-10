#include "pch.h"
#include "Utils.h"
#include "VectorProcess.h"

VectorProcess::VectorProcess():VectorProcess(initialize(getRand(23, 30))) {
}

VectorProcess::VectorProcess(const vector<float> data) {
    data_ = data;
}

const vector<float>& VectorProcess::data() {
    return data_;
}

vector<float> VectorProcess::initialize(int n, float lo, float hi) {
    vector<float> data(n);
    generate(data.begin(), data.end(), [lo, hi]() { return getRand(lo, hi); });
    return data;
}

int VectorProcess::numberNegatives() {
    return count_if(data_.begin(), data_.end(), [](float item) { return item < 0; });
}

int VectorProcess::numberNotInRange(float a, float b) {
    return count_if(data_.begin(), data_.end(), [a, b](float item) { return a > item || item > b; });
}

float VectorProcess::sumBeforeFirstMin() {
    auto itFirstMin = min_element(data_.begin(), data_.end());
    return accumulate(data_.begin(), itFirstMin, 0.f);
}

float VectorProcess::sumBetweenFirstMinFirstMax() {
    auto itFirst = min_element(data_.begin(), data_.end());
    auto itSecond = max_element(data_.begin(), data_.end());
    if (itFirst > itSecond) swap(itFirst, itSecond);
    return accumulate(itFirst + 1, itSecond, 0.f);
}

vector<float> VectorProcess::fihdNegatives() {
    vector<float> selected;
    copy_if(data_.begin(), data_.end(), back_inserter(selected), [](float item) { return item < 0.f; });
    return selected;
}

vector<float> VectorProcess::fihdNotInRange(float a, float b) {
    vector<float> selected;
    copy_if(data_.begin(), data_.end(), back_inserter(selected), [a, b](float item) { return a > item || item > b; });
    return selected;
}

void VectorProcess::orderByDesc() {
    sort(data_.begin(), data_.end(), greater<float>());
}

void VectorProcess::orderByAbs() {
    sort(data_.begin(), data_.end(), [](float x, float y) { return abs(x) < abs(y); });
}

void VectorProcess::orderByNotInRangeLast(float a, float b) {
    sort(data_.begin(), data_.end(), [a, b](float x, float y) {
        return (a <= x && x <= b) && !(a <= y && y <= b);
    });
}

void VectorProcess::saveToBinary(const string &fileName) {
    fstream fs(fileName, ios::out | ios::binary);
    if (!fs.is_open()) {
        throw exception(("VectorProcess: cannot open file " + fileName).c_str());
    }
    for (auto datum : data_) fs.write((char*)&datum, sizeof(datum));
    fs.close();
}

void VectorProcess::loadFromBinary(const string& fileName) {
    fstream fs(fileName, ios::in | ios::binary);
    if (!fs.is_open()) {
        throw exception(("VectorProcess: cannot open file " + fileName).c_str());
    }
    for (data_.clear(); !fs.eof(); fs.peek()) {
        float datum;
        fs.read((char*)&datum, sizeof(datum));
        if (fs.gcount() == sizeof(datum)) data_.emplace_back(datum);
    }
    fs.close();
}
