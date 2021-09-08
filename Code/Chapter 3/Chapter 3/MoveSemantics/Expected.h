#pragma once
#include <iostream>
#include <exception>

typedef std::exception Exception;

template <class T>
class Expected {
private:
	// Our union of value and error. Only one of these can exist in any `Expected` object created.
	T value;
	Exception exception;
	bool error = false;

public:
	// Instantiate the `Expected` object with the successfully created value.
	Expected(const T& value) {
		this->value = value;
	}

	~Expected() {
	}

	// Instantiate the `Expected` object with an exception.
	Expected(const Exception& ex) {
		this->exception = ex;
		this->error = true;
	}

	// Was there an error?
	bool hasError() {
		return error;
	}

	// Access the value.
	T getValue() {
		return value;
	}

	// Access the exception.
	Exception getError() {
		return exception;
	}
};