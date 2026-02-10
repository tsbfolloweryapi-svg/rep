#pragma once
#include "pch.h"
#include "VectorTask.h"


class App
{
	// объект задачи
	VectorTask task_;

	// загрузка вектора из бинарного потока
	void loadVectorFromBinStream(const string& fileName);

	// сохранение вектора в бинарный поток
	void saveVectorToBinStream(const string& fileName);

	// вывод вектора
	void show(const string& title, const vector<float>& v);

public:
	App() :App(VectorTask()) {}
	App(const VectorTask& task) { task_ = task; } // App

#pragma region задача 1
	void doTask1();
#pragma endregion
};
