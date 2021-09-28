#pragma once
#include <iostream>
#include "Timer.h"
#include "Expected.h"
#include <string>
#include <algorithm>

extern volatile uint64_t Allocations;

template<typename S, typename T>
class LevensteinDistanceDemo {
private:
	S name;
	void (*Function)(T, T);
public:
	LevensteinDistanceDemo(S&& name, void (*Function)(T, T))
		:name(std::move(name)), Function(Function)
	{

	}

	S getName() const
	{
		return name;
	}

	auto getFunktion() const {
		return Function;
	}
};

uint32_t LevensteinDistance(std::string string1, std::string string2) 
{
	if (string1.empty() || string2.empty())
		throw std::runtime_error("string1 or string2 is empty");

	const uint32_t len1 = string1.size() + 1;
	const uint32_t len2 = string2.size() + 1;
	uint32_t result = 0;

	//Create
	uint32_t** Matrix = new uint32_t * [len1];
	for (uint32_t i = 0; i < len1; i++)
		Matrix[i] = new uint32_t[len2];

	//Init 
	Matrix[0][0] = 0;

	for (uint32_t i = 1; i < len1; ++i)
		Matrix[i][0] = i;

	for (uint32_t i = 1; i < len2; ++i)
		Matrix[0][i] = i;

	//Complete the Matrix
	for (uint32_t i = 1; i < len1; ++i)
		for (uint32_t j = 1; j < len2; ++j)
			Matrix[i][j] = std::min({ Matrix[i - 1][j] + 1, Matrix[i][j - 1] + 1, Matrix[i - 1][j - 1] + (string1[i - 1] == string2[j - 1] ? 0 : 1) });

	result = Matrix[len1 - 1][len2 - 1];

	for (uint32_t i = 0; i < len1; i++)
		delete[] Matrix[i];
	delete[] Matrix;

	return result;
}

int32_t LevensteinDistanceOptimized(const std::string_view string1, const std::string_view string2) 
{
	int32_t result = -1;
	if (string1.empty() || string2.empty())
		return result;

	const uint32_t len1 = string1.size() + 1;
	const uint32_t len2 = string2.size() + 1;

	uint32_t* Matrix = new uint32_t[len1 * len2];
	uint32_t* ptr1 = Matrix;
	uint32_t* ptr2 = Matrix;

	Matrix[0] = 0;

	for (uint32_t i = 1; i < len1; i++){
		ptr1 += len2;
		(*ptr1) = i;
	}

	for (uint32_t i = 1; i < len2; ++i) {
		++ptr2;
		(*ptr2) = i;
	}

	ptr1 = nullptr;
	ptr2 = nullptr;

	for (uint32_t i = 1; i < len1; ++i)
		for (uint32_t j = 1; j < len2; ++j) {
			Matrix[i * len2 + j] = std::min({ Matrix[(i - 1) * len2 + j] + 1, Matrix[i * len2 + (j - 1)] + 1, Matrix[(i - 1) * len2 + (j - 1)] + (string1[i - 1] == string2[j - 1] ? 0 : 1) });
		}
			
	result = static_cast<int32_t>(Matrix[(len1 - 1) * len2 + (len2 - 1)]);

	delete[] Matrix;

	return result;
}

void DoLevensteinDistance(std::string string1, std::string string2) {
	try
	{
		LevensteinDistance(string1, string2);
	}
	catch (const std::exception& e)
	{
		// handle Error
	}
}

void DoLevensteinDistanceOptimized(std::string_view string1, std::string_view string2) {
	auto result = LevensteinDistanceOptimized(string1, string2);

	if (result == -1) {
		//Handle error
	}
}

template<typename S, typename T>
void DoLevensteinDistanceBenchmark(uint32_t times, const LevensteinDistanceDemo<S,T>& levenstein) 
{
	Allocations = 0;

	std::cout << levenstein.getName() << " with " << times << " Times: ";

	{
		Timer timer;
		for (uint32_t i = 0; i < times; ++i)
			levenstein.getFunktion()((i % 100) ? "Hallo this world" : "", (i % 101) ? "Hello this worlt" : "");
	}

	std::cout << "New Called: " << Allocations << " times." << std::endl;
}

