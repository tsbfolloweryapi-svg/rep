#pragma once
#include "pch.h"


class VectorTask
{
	vector<float> data_;

public:
	VectorTask();
	VectorTask(const vector<float>& data);

	// аксессоры
	const vector<float>& data() const;
	void data(const vector<float>& value);

	void clear();

#pragma region Обработки по заданию

	int countNegative() const;

	int countNotInRange(float a, float b) const;

	float sumBeforeFirstMin() const;

	float sumBetweenFirstMinAndFirstMax() const;

	vector<float> selectNegatives() const;

	vector<float> selectNotInRange(float a, float b) const;

	void orderDescending();

	void orderByAbsAscending();

	void moveNotInRangeToEnd(float a, float b);

#pragma endregion
};
