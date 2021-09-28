#pragma once

#include <iostream>
#include <chrono>
#include <sstream>

static volatile uint64_t Allocations = 0;

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
		double ms = round2(duration * 0.001);
		double sec = round2(ms * 0.001);

		std::cout << duration << " microseconds : " << ms << " millisecounds : " << sec << " sekunden" << std::endl;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepont;

	double round2(double zahl) {
		return  (double)((int)(zahl * 100)) / 100;
	}
};
