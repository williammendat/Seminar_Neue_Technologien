#pragma once
#include <iostream>
#include "Timer.h"
#include "Expected.h"
#include <random>

const int randomRange = 2;  // Give me a number between 0 and 2.
const int errorInt = 0;     // Stop every time the number is 0.
int getRandom() {
	return rand() % randomRange;
}

void exitWithExceptionThrown() {
	if (getRandom() == errorInt)
		throw std::runtime_error("Exception thrown!");
}

int exitWithReturnCode() {
	if (getRandom() == errorInt)
		return -1;
	return 0;
}

void doBenchmarkException(uint64_t times) {
	Timer timer;
	for (uint64_t i = 0; i < times; ++i)
	{
		try
		{
			exitWithExceptionThrown();
		}
		catch (const std::exception&)
		{
			// handle Error
		}
	}
}

void doBenchmarkReturnCode(uint64_t times) {
	Timer timer;
	for (uint64_t i = 0; i < times; ++i)
	{
		auto err = exitWithReturnCode();
		if (err == -1) {
			//handle Error
		}
	}
}

void doBenchmarkExceptions(uint64_t times) {
	//std::cout << "Exception throwing " << times << " times:";
	//doBenchmarkException(times, true);

	std::cout << "Exception not throwing " << times << " times:";
	doBenchmarkException(times);

	std::cout << "Return Code " << times << " times:";
	doBenchmarkReturnCode(times);
}

Expected<int> returnWithExpeted() {
	if (getRandom() == errorInt) {
		return Expected<int>(std::runtime_error("Halt! If you want..."));  //  Return; don't throw!
	}
	return Expected<int>(5);
}

void doBenchmarkExpected(uint64_t times) {
	Timer timer;
	for (uint64_t i = 0; i < times; i++)
	{
		auto expected = returnWithExpeted();

		if (expected.hasError()) {
			//handle Error
		}
	}
}

void doBenchmark(uint64_t times) {
	std::cout << "Exception throwing " << times << " times:";
	doBenchmarkException(times);

	std::cout << "Expected return " << times << " times:";
	doBenchmarkExpected(times);

	std::cout << "Return Code " << times << " times:";
	doBenchmarkReturnCode(times);
}