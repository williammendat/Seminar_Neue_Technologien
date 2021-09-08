#pragma once
#include <iostream>
#include <vector>
#include <array>
#include "Timer.h"

class Hoch3 {
public:
	auto& Hoch3Normal(uint64_t n) {
		std::vector<uint64_t>* array = new std::vector<uint64_t>();
		array->reserve(n);

		Timer timer;		
		for (uint64_t i = 1; i <= n; ++i)
		{			
			array->emplace_back(i * i * i);
		}

		return array;
	}

	void PrintArray(const std::vector<uint64_t>& array) {
		uint64_t index = 0;

		for (uint64_t i = 0; i < array.size(); ++i)
		{
			index = i + 1;
			std::cout << index << " hoch 3: " << array[i] << std::endl;
		}
	}

	auto& Hoch3Custom(uint64_t n) {
		std::vector<uint64_t>* array = new std::vector<uint64_t>();
		array->reserve(n);
		
		Timer timer;
		uint64_t help = 1;
		uint64_t ergebnis = 1;

		array->emplace_back(ergebnis);

		//help = ((help - 1) + 6 * (index - 1)) 
		//ergebnis = help + ergebnis - 1 
		for (uint64_t i = 2; i <= n; ++i)
		{
			help = help + (6 * (i - 1));
			ergebnis = help + ergebnis;
			array->emplace_back(ergebnis);
		}
		return array;
	}
};