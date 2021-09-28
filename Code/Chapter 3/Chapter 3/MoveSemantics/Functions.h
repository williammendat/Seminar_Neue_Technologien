#pragma once
#include <iostream>
#include "Timer.h"
#include "Expected.h"
#include <random>
#include <string>

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

void doStingReserverBenchmark(uint64_t& Allocations)
{
	std::vector<uint64_t> times = { 100000, 200000, 300000, 400000, 500000, 600000, 700000 };

	for (uint32_t i = 0; i < times.size(); ++i)
	{
		//init von Strings
		std::vector<std::string> strings;

		Allocations = 0;

		for (uint64_t j = 0; j < times[i]; j++)
			strings.push_back("String");

		{
			std::cout << "String without reserver with " << times[i] << " times: ";
			std::string* string = new std::string();
			Timer timer;

			for (uint64_t j = 0; j < times[i]; j++)
				string->append(strings.at(j));
			delete string;
		}

		std::cout << "New called: " << Allocations << " times" << std::endl;
		Allocations = 0;
		{
			std::cout << "String with reserve with " << times[i] << " times: ";
			std::string* string = new std::string();
			uint64_t bytes = 0;
			Timer timer;

			for (uint64_t j = 0; j < times[i]; j++)
				bytes += strings.at(j).size();

			string->reserve(bytes + 1);

			for (uint64_t j = 0; j < times[i]; j++)
				string->append(strings.at(j));

			delete string;
		}

		std::cout << "New called: " << Allocations << " times" << std::endl;

		std::cout << "--------------------------------------------------------" << std::endl;

	}
}

void PrintStringView(std::string_view string) {
	std::cout << string << std::endl;
}

void PrintStdString(const std::string& string) {
	std::cout << string << std::endl;
}

template <uint32_t Base>
struct Sum
{
	static const uint64_t result = Base + Sum<Base - 1>::result;
};

// base case
template<>
struct Sum<1>
{
	static const uint64_t result = 1;
};

constexpr uint64_t SumConstExpr(const uint32_t value) {
	return value <= 1 ? 1 : (value + SumConstExpr(value - 1));
}

