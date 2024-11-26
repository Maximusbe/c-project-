#include "calculator.h"

// MathException constructor that takes a message and stores it
MathException::MathException(const std::string& message) : msg(message) {}

// Override of the 'what' function which returns the error message
const char* MathException::what() const throw() { return msg.c_str(); }