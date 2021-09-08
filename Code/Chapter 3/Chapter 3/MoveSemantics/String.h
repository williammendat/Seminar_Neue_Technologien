#pragma once
#include <iostream>

class String {

public:
	String() = default;
	//String(const String& other) = default;

	//Normaler Konstruktor um ein Objekt zu erzeugen
	String(const char* string) {
		printf("Created\n");
		m_Size = strlen(string);
		m_Data = new char[m_Size + 1];
		memcpy(m_Data, string, m_Size);
		m_Data[m_Size] = 0;
	}

	//Copy Construktor um ein Objekt zu kopieren
	//Deep Copy muss Speicher neu erzeugen
	String(const String& other) {
		printf("Copied\n");
		m_Size = other.m_Size;
		m_Data = new char[m_Size + 1];
		memcpy(m_Data, other.m_Data, m_Size + 1);
	}

	//Move Constuktor um ein Objekt zu Moven
	//Flache Kopie kein speicher muss neu erzeugt werden
	//Ideal für temporäre objekte
	String(String&& other) noexcept {
		printf("Moved\n");
		m_Size = other.m_Size;
		m_Data = other.m_Data;

		other.m_Data = nullptr;
		other.m_Size = 0;
	}


	String& operator= (String&& other) noexcept {
		printf("Moved via =\n");
		if (this == &other)
			return *this;

		delete[] m_Data;

		m_Size = other.m_Size;
		m_Data = other.m_Data;

		other.m_Data = nullptr;
		other.m_Size = 0;
		return *this;
	}

	String& operator=(const String& other) noexcept {
		printf("Copied via =\n");
		if (this == &other)
			return *this;

		delete[] m_Data;

		m_Size = other.m_Size;
		m_Data = new char[m_Size + 1];
		memcpy(m_Data, other.m_Data, m_Size + 1);
		return *this;
	}

	String& operator+(const String& other) noexcept {
		this->operator+(other.m_Data);
	}

	String& operator+(const char* other) noexcept {
		printf("Copied via +\n");
		String temp = std::move(*this);

		delete[] m_Data;
		int other_Size = strlen(other);
		m_Size = temp.m_Size + other_Size;
		m_Data = new char[m_Size + 1];
		int i = 0;

		for (int j = 0; j < temp.m_Size; ++j, ++i)
			m_Data[i] = temp.m_Data[j];

		for (int j = 0; j < other_Size; ++j, ++i)
			m_Data[i] = other[j];

		m_Data[m_Size] = 0;
		return *this;
	}

	char& operator[] (int index) noexcept {
		return m_Data[index];
	}

	friend std::ostream& operator<<(std::ostream& os, const String& string);

	~String() {
		printf("Deleted\n");
		delete m_Data;
	}

	const void const PrintLine() const {
		Print();
		printf("\n");
	}

	inline void const Print() const {
		for (int i = 0; i < m_Size; ++i)
			printf("%c", m_Data[i]);
	}

	virtual void PrintString() { std::cout << *this << " printed with String" << std::endl; }

	uint64_t Size() { return m_Size; }

protected:

	uint64_t m_Size;
	char* m_Data;
};

class Stringbuilder : public String {
public:

	Stringbuilder(const char* string)
		:String(string)
	{

	}

	void PrintString() override { std::cout << *this << " printed with Stringbuilder" << std::endl; }
};


std::ostream& operator<<(std::ostream& os, const String& string) {
	os << string.m_Data;
	return os;
}
