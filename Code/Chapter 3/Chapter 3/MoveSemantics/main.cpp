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

int main(int argc, char** argv)
{
	doStingReserverBenchmark(Allocations);

	std::cin.get();
}

