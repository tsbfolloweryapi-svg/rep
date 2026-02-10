#include "pch.h"
#include "VectorFactory.h"
#include "Utils.h"


vector<float> VectorFactory::create(int n, float low, float high) {
	if (n < 12 || n > 30) {
		throw exception("VectorFactory: n должно быть в диапазоне [12; 30].");
	} // if

	vector<float> data(n);

	generate(data.begin(), data.end(), [low, high]() {
		return getRand(low, high);
		});

	return data;
} // VectorFactory::create
