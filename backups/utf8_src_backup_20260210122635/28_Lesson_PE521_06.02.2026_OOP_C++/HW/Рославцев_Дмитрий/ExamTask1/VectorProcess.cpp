#include "pch.h"
#include "Utils.h"
#include "VectorProcess.h"

VectorProcess::VectorProcess():VectorProcess(initialize(getRand(23, 30))) {

} // VectorProcess::VectorProcess


VectorProcess::VectorProcess(const vector<float> data) {
	data_ = data;
} // VectorProcess::VectorProcess


// геттер для вывода вектора
const vector<float>& VectorProcess::getData() {
	return data_;
} // VectorProcess::data

// сеттер для вывода вектора
void VectorProcess::setData(vector<float>& value)
{
	data_ = value;
} // VectorProcess::setData


// Генерация вектора заданного размера
vector<float> VectorProcess::initialize(int n, float lo, float hi) {
	vector<float> data(n);

	generate(data.begin(), data.end(), [lo, hi]() { return getRand(lo, hi); });
	return data;
} // VectorProcess::initialize

// очистка вектора
void VectorProcess::clearVector()
{
	data_.clear();
} // VectorProcess::clearVector


// Количество отрицательных элементов вектора
int VectorProcess::numberNegatives() {
	return count_if(data_.begin(), data_.end(), 
		[](float item) { return item < 0; });
} // VectorProcess::numberNegatives


// Количество элементов вектора, не попадающих в интервал [a, b], введенный с клавиатуры
int VectorProcess::numberNotInRange(float a, float b) {
	return count_if(data_.begin(), data_.end(), 
		[a, b](float item) { return a > item or item > b; });
} // VectorProcess::numberNotInRange

// Сумма элементов вектора, расположенных перед первым минимальным элементом
float VectorProcess::sumToMin()
{
	float sum = 0.f;

	sum = accumulate(data_.begin(), min_element(data_.begin(), data_.end()), 0.f);

	return sum;
} // VectorProcess::sumToMin

// Сумма элементов вектора, расположенных между первым минимальным и первым максимальным элементами
float VectorProcess::sumInDiaposone()
{
	float sum = 0.f;

	if(min_element(data_.begin(), data_.end()) < max_element(data_.begin(), data_.end())) {
		sum = accumulate(min_element(data_.begin(), data_.end()), max_element(data_.begin(), data_.end()), 0.f);
	} // if
	else {
		sum = accumulate(max_element(data_.begin(), data_.end()), min_element(data_.begin(), data_.end()), 0.f);
	}
	return sum;
} // VectorProcess::sumInDiaposone

// Bыборка в другой вектор отрицательных элементов
vector<float> VectorProcess::findByNegative()
{
	vector<float> temp;

	copy_if(data_.begin(), data_.end(), back_inserter(temp), [](float item) { return item < 0; });

	return temp;
} // VectorProcess::findByNegative

// Выбрка в другой вектор элементов, не попадающих в интервал [a, b]
vector<float> VectorProcess::findByDiaposone(float first, float second)
{
	vector<float> temp;

	copy_if(data_.begin(), data_.end(), back_inserter(temp), [first, second](float item) { return first <= item and item <= second; });

	return temp;
} // VectorProcess::findByDiaposone

// Упорядочить элементы вектора по убыванию
void VectorProcess::sortItem()
{
	sort(data_.begin(), data_.end(), [](float item1, float item2) { return item1 < item2; });
} // VectorProcess::sortItem

// Упорядочить вектор по возрастанию модулей элементов
void VectorProcess::sortByModel()
{
	sort(data_.begin(), data_.end(), [](float& item1, float& item2) {
		return (item1 < 0 ? item1 * -1.f : item1) < (item2 < 0 ? item2 * -1.f : item2);
	});
} // VectorProcess::sortByModel

// Упорядочить вектор по правилу – элементы, не попадающие в интервал значений [a, b] в конец вектора
void VectorProcess::sortByDiaposone(float first, float second)
{
	sort(data_.begin(), data_.end(), [first, second](float item, float item2) { 
		return (first <= item2 and item2 <= second) < (first <= item and item <= second);
	});
} // VectorProcess::sortByDiaposone

