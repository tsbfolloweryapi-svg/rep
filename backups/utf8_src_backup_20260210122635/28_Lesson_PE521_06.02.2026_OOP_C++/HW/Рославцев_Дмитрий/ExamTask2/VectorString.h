#pragma once
#include "pch.h"

class VectorString
{
private:
	vector<string> data_;

	string fileName_;
public:
	VectorString();
	VectorString(const vector<string>& data, const string& fileName);

	// инициализаци€ вектора из файла
	void loadFromTxt();

	// аксессоры
	const vector<string>& getData();
	void setData(const vector<string>& value);

	// 1)	—формируйте частотный словарь слов текста
	int doWordBook(const string& word);

};

