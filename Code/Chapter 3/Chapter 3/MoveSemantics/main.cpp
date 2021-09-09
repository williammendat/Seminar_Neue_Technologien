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

void* operator new(size_t size) {
	++Allocations;
	return malloc(size);
}

void PrintString(String string) {
	std::cout << string << std::endl;
}

int main(int argc, char** argv)
{
	String demo = String("Hello") + " World!";
	PrintString(demo);
	std::cout << "New called " << Allocations << " times" << std::endl;
	std::cin.get();
}

