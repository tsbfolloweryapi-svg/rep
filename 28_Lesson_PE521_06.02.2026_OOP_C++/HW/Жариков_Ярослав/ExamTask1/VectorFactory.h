#pragma once
#include "pch.h"


class VectorFactory
{
public:
	VectorFactory() = default;
	VectorFactory(const VectorFactory& other) = default;
	~VectorFactory() = default;
	VectorFactory& operator=(const VectorFactory& other) = default;

	static vector<float> create(int n, float low = -50.f, float high = 50.f);
};
