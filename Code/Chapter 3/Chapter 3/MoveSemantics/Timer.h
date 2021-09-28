#pragma once

#include <iostream>
#include <chrono>
#include <sstream>

static volatile uint64_t Allocations = 0;

constexpr uint32_t GetMultiply(const uint16_t digits) {
	if (digits == 0)
		return 1;

	uint32_t result = 10;

	for (uint16_t i = 1; i < digits; ++i)
		result *= 10;

	return result;
}

double round(double zahl, const uint16_t digits) {
	return  (double)((int)(zahl * GetMultiply(digits))) / GetMultiply(digits);
}

class Timer {
public:
	Timer()
	{
		m_StartTimepont = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		Stop();
	}

	void Stop() 
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepont).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
		
		auto duration = end - start;
		double ms = round(duration * 0.001, 2);
		double sec = round(ms * 0.001, 2);

		std::cout << duration << " microseconds : " << ms << " millisecounds : " << sec << " secounds" << std::endl;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepont;


};
