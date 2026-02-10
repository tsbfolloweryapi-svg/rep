#pragma once
#include "pch.h"

class FileException : public exception
{
	// имя файла, на котором возникла ошибка
	string fileName_;

public:
	// ансамбль конструкторов и деструктор
	FileException() :FileException("FileException: ошибка"s, ""s) {}

	FileException(const char* msg, const char* fileName) : exception(msg) {
		fileName_ = fileName;
	} // FileException

	FileException(const string& msg, const string& fileName) : exception(msg.c_str()) {
		fileName_ = fileName;
	} // FileException

	FileException(const FileException& obj) = default;

	~FileException() override = default;

	// перегрузка операции присваивавния
	FileException& operator=(const FileException& obj) = default;

	// геттеры для удобства работы, сеттеры не нужны по логике работы
	const string& getFileName() const { return fileName_; }
};
