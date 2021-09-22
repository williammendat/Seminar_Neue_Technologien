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

int main(int argc, char** argv)
{
	uint32_t** array2D = new uint32_t * [5];
	for (uint16_t i{}; i < 5; ++i)
		array2D[i] = new uint32_t[5];
}

