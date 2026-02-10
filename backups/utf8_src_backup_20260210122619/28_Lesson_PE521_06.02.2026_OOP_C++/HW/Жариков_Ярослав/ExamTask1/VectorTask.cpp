#include "pch.h"
#include "VectorTask.h"


VectorTask::VectorTask() : VectorTask(vector<float>())
{
} // VectorTask::VectorTask


VectorTask::VectorTask(const vector<float>& data) {
	this->data(data);
} // VectorTask::VectorTask


const vector<float>& VectorTask::data() const { return data_; } // VectorTask::data
void VectorTask::data(const vector<float>& value) { data_ = value; } // VectorTask::data


void VectorTask::clear() { data_.clear(); } // VectorTask::clear


#pragma region Обработки по заданию

int VectorTask::countNegative() const {
	return (int)count_if(data_.begin(), data_.end(), [](float x) { return x < 0.f; });
} // VectorTask::countNegative


int VectorTask::countNotInRange(float a, float b) const {
	return (int)count_if(data_.begin(), data_.end(), [a, b](float x) {
		return x < a || x > b;
		});
} // VectorTask::countNotInRange


float VectorTask::sumBeforeFirstMin() const {
	if (data_.empty()) return 0.f;

	auto itMin = min_element(data_.begin(), data_.end());
	return accumulate(data_.begin(), itMin, 0.f);
} // VectorTask::sumBeforeFirstMin


float VectorTask::sumBetweenFirstMinAndFirstMax() const {
	if (data_.empty()) return 0.f;

	auto itMin = min_element(data_.begin(), data_.end());
	auto itMax = max_element(data_.begin(), data_.end());

	if (itMin == itMax) return 0.f;

	if ((itMin < itMax && itMin + 1 == itMax) || (itMax < itMin && itMax + 1 == itMin)) return 0.f;

	return itMin < itMax
		? accumulate(itMin + 1, itMax, 0.f)
		: accumulate(itMax + 1, itMin, 0.f);
} // VectorTask::sumBetweenFirstMinAndFirstMax


vector<float> VectorTask::selectNegatives() const {
	vector<float> result;

	copy_if(data_.begin(), data_.end(), back_inserter(result),
		[](float x) { return x < 0.f; }
	);

	return result;
} // VectorTask::selectNegatives


vector<float> VectorTask::selectNotInRange(float a, float b) const {
	vector<float> result;

	copy_if(data_.begin(), data_.end(), back_inserter(result),
		[a, b](float x) { return x < a || x > b; }
	);

	return result;
} // VectorTask::selectNotInRange


void VectorTask::orderDescending() {
	sort(data_.begin(), data_.end(), [](float x, float y) { return y < x; });
} // VectorTask::orderDescending

void VectorTask::orderByAbsAscending() {
	sort(data_.begin(), data_.end(),
		[](float x, float y) {
			return fabs(x) < fabs(y);
		}
	);
} // VectorTask::orderByAbsAscending

void VectorTask::moveNotInRangeToEnd(float a, float b) {
	// Правило сортировки: сначала элементы из [a, b], затем остальные
	sort(data_.begin(), data_.end(), [a, b](float x, float y) {
		return (x >= a && x <= b) && !(y >= a && y <= b);
		});
} // VectorTask::moveNotInRangeToEnd

#pragma endregion
