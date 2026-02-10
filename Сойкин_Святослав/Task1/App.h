#pragma once
#include "pch.h"
#include "VectorProcess.h"

class App {
    VectorProcess vectorProcess_;
    string binFile_;

    // steps of Task 1 implemented as separate functions
    void step_countNegative();
    void step_countOutsideInterval(float a, float b);
    void step_sumBeforeFirstMin();
    void step_sumBetweenFirstMinAndFirstMax();
    void step_selectNegatives();
    void step_selectOutsideInterval(float a, float b);
    void step_sortDescending();
    void step_sortByAbsAscending();
    void step_moveOutsideIntervalToEnd(float a, float b);

    float readFloatFromCin(const string &prompt);

    // Binary save/load are handled by VectorProcess; App delegates to it in run().

public:
    App();
    void run();
};
