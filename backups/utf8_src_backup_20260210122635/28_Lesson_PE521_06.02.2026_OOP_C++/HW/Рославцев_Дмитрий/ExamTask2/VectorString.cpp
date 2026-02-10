#include "VectorString.h"
#include "Utils.h"

VectorString::VectorString(): VectorString(data_, "test.txt")
{
} // VectorString::VectorString

VectorString::VectorString(const vector<string>& data, const string& fileName)
{
	data_ = data;
	fileName_ = fileName;
} // VectorString::VectorString

// инициализация вектора из файла
void VectorString::loadFromTxt()
{
	ifstream ifs;

	// открыть текстовый файл для чтения
	ifs.open(fileName_);
	if (!ifs.is_open()) {
		throw exception("App: не могу открыть текстовый поток для чтения из файл ");
	} // if

	// задать кодировку потока ввода CP1251  
	ifs.imbue(locale(".1251"));

	for (int i = 1; !ifs.eof(); ++i) {
		// читаем очередную строку из файла
		string row;
		getline(ifs, row);

		data_.emplace_back(row);

		ifs.peek();
	} // for 
	ifs.close();
} // VectorString::loadFromTxt

// аксессоры
const vector<string>& VectorString::getData()
{
	return data_;
} // VectorString::getData

void VectorString::setData(const vector<string>& value)
{
	data_ = value;
} // VectorString::setData

// 1)	Сформируйте частотный словарь слов текста
int VectorString::doWordBook(const string& word)
{
	int counter = 0;

	for_each(data_.begin(), data_.end(), [word](string item) {
		
	});
	return counter;
} // VectorString::doWordBook
