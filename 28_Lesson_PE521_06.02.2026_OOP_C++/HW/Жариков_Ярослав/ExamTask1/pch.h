#ifndef PCH_H
#define PCH_H

// дл€ использовани€ старых, небезопасных функций, например sprintf()
#define _CRT_SECURE_NO_WARNINGS

// использование математических констант, современный стиль
#include <corecrt_math_defines.h>

#include <iostream>  // этот файл делает доступными инженерные функции  
#include <iomanip>   // дл€ манипул€торов вывода setw(), setprecision()
#include <Windows.h> // дл€ использовани€ функций WinAPI
#include <conio.h>
#include <sstream>   // дл€ классов ostringstream, istringstream
#include <fstream>   // дл€ файловых потоков ввода/вывода

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <algorithm>
#include <numeric>
#include <iterator>

using namespace std;

// объ€вление символической константы - кодовой страницы
#define CODE_PAGE 1251

#endif //PCH_H
