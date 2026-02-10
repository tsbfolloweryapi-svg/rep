#pragma once
#include "pch.h"
#include "VectorProcess.h"

class App
{
	// обработка вектора по заданию
	VectorProcess vectorProcess_;

	// имя бинарного файла для хранения вектора
	string fileName_;

	// Вывод вектора в консоль, по m элементов в строке, точность 
	// precision знаков
	void show(const string &title, int m = 5, int precision = 3);

	// Вывод вспомогательных векторов
	void showVector(const string& title, const vector<float>& temp, int m = 5, int precision = 3);

public:
	App();
	App(const VectorProcess &vectorProcess, const string &fileName);

	// Сохраненение в бинарный файл
	void saveToBin();

	// Чтение из бинарного файла
	void loadFromBin();

	// Обработка по заданию
	void doProcess();
};

