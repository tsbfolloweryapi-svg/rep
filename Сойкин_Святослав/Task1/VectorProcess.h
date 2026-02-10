#pragma once
#include "pch.h"
#include <vector>
using std::vector;

class VectorProcess
{
    vector<float> data_;

public:
    VectorProcess();
    VectorProcess(const vector<float> data);

    const vector<float>& data();

    static vector<float> initialize(int n, float lo = -50.f, float hi = 50.f);

    int numberNegatives();
    int numberNotInRange(float a, float b);
    float sumBeforeFirstMin();
    float sumBetweenFirstMinFirstMax();
    vector<float> fihdNegatives();
    vector<float> fihdNotInRange(float a, float b);
    void orderByDesc();
    void orderByAbs();
    void orderByNotInRangeLast(float a, float b);

    void saveToBinary(const string& fileName);
    void loadFromBinary(const string& fileName);
};
