#include <iostream>
#include <string>
#include "String.h"
#include "Timer.h"
#include "Hoch3.h"
#include "Expected.h"
#include "Functions.h"
#include <string_view>
#include <ranges>
#include <vector>
#include <memory>

#define ARRAYSIZE 10
#define TIMES 100000000000

static uint64_t Allocations = 0;

void* operator new(size_t size) {
	++Allocations;
	return malloc(size);
}

void PrintStringView(std::string_view string) {
	std::cout << string << " count: " << string.size() << std::endl;
	auto test = string[0];
	std::cout << test << std::endl;
}

template <uint32_t Base>
struct Faculty
{
	static const unsigned long long result = Base * Faculty<Base - 1>::result;
};

// base case
template<>
struct Faculty<1>
{
	static const unsigned long long result = 1;
};

constexpr uint32_t Sum(uint16_t value) {
	return value <= 1 ? 1 : (value * Sum(value - 1));
}

int main(int argc, char** argv)
{
	//doStingReserverBenchmark(Allocations);

	std::cout << Sum(5) << std::endl;

	std::cin.get();
}

