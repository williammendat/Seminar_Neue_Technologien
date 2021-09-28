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
#include "Demo.h"
#include <sstream>


#define ARRAYSIZE 10
#define TIMES 100000000000

extern volatile uint64_t Allocations;

void* operator new(size_t size) {
	++Allocations;
	return malloc(size);
}


int main(int argc, char** argv)
{
	std::vector times = { 100000, 500000, 1000000 };
	LevensteinDistanceDemo<std::string_view, std::string> Normal("Levenstein Distance", DoLevensteinDistance);
	LevensteinDistanceDemo<std::string_view, std::string_view> Optimized("Levenstein Distance Optimized", DoLevensteinDistanceOptimized);
	Allocations = 0;

	for (uint32_t i = 0; i < times.size(); ++i) {
		DoLevensteinDistanceBenchmark(times[i], Normal);
		std::cout << std::endl;
		DoLevensteinDistanceBenchmark(times[i], Optimized);

		std::cout << "---------------------------------------" << std::endl;
	}
	std::cout << "Finished" << std::endl;

	std::cin.get();
}

