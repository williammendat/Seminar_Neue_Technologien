#pragma once
#include <iostream>
#include "String.h"

class Entity {
public:
	Entity(const String& name)
		:m_Name(name)
	{
	}

	Entity(String&& name)
		:m_Name(std::move(name))
	{
	}

	void PrintName() {
		m_Name.PrintLine();
	}

	void Test(const String& string) {
		string.PrintLine();
	}

	void Test(String&& string) {
		printf("TestMoved\n");
		string.PrintLine();
	}

	constexpr long long factorial(int n) {
		if (n <= 1)
			return 1;

		long long result = 1;
		for (int i = 1; i <= n; ++i)
			result *= i;
		return result;
	}

private:
	String m_Name;
};