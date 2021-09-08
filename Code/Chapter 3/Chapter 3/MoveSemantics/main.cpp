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

#define ARRAYSIZE 10
#define TIMES 100000000000

static uint64_t Allocations = 0;

//void* operator new(size_t size) {
//	++Allocations;
//	printf("Allocated %d Bytes\n", size);
//	return malloc(size);
//}

void f(auto& vector, auto& function) {
	function(vector);
}

int main(int argc, char** argv)
{
	//doBenchmark(TIMES);
	//Hoch3 test; 

	std::vector<uint64_t> times = { 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 1000000 };

	//for (uint64_t i = 0; i < times.size(); i++)
	//{
	//	//Normal
	//	std::cout << "Normal with " << times[i] << " times: ";
	//	const auto* array = test.Hoch3Normal(times[i]);
	//	delete array;

	//	//Custom 
	//	std::cout << "Custom with " << times[i] << " times: ";
	//	const auto* arrayCustom = test.Hoch3Custom(times[i]);
	//	delete arrayCustom;

	//	std::cout << "-----------------------------------------------" << std::endl;
	//}
	for (uint64_t i = 0; i < times.size(); i++)
	{
		doBenchmark(times[i]);
		std::cout << "-----------------------------------------------" << std::endl;
	}

	/*uint64_t test = 0;

	for (uint64_t i = 0; i < 10000000; i++)
	{
		test += i;
	}*/

	std::cout << "Finished" << std::endl;
	std::cin.get();

}

