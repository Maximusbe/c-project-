#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <string>
#include <cmath>
#include <exception>

class Validate{

public:
    // Checks if there are any errors in the equations
    std::string validateEquation(std::string equation);
};

class MathException : public std::exception {

private:
    // Contains the error message
    std::string msg;
public:
    // Returns the error that was found during calculations
    MathException(const std::string& message);
    const char* what() const throw();
};

class Solver{

public:
    // Calculates the postfix equation
    double calculatePostfix(std::string equation, bool angle);
};

class Calculate{

public:
    // Uses the value given and does the appropriate calculation
    double calculations(double value, char opt);

    // Uses the value and the type of angle and does the appropriate calculation
    double calculations(double value, char opt, bool angle);
    
    // Uses the two values given and does the appropriate calculation
    double calculations(double value1, double value2, char opt);
};

class NumberStack{

private:
    // The stack that contains the values
    double stack[50];
    
    // Variable for the top of the stack
    int top = -1;

public:
    // Pushes a value into the stack
    void push(double num);

    // Pops a value from the stack
    double pop();

    // Returns the value at the top of the stack
    double topValue();

    // Returns the amount of values inside the stack
    int length();

    // Checks if the stack is empty
    bool isEmpty();

    // Prints the contents of the stack
    void print();
};

class Converter{

public:
    // Converts from infix notation to postfix notation
    std::string infixToPostfix(std::string equation);
};

class Priority{

public:
    // A switch that returns the priority of the operator
    int optCheck(char opt);
};

class CharacterStack{

private:
    // The stack that contains the operators
    char stack[50];
    
    // Variable for the top of the stack
    int top = -1;

public:
    // Pushes a value into the stack
    void push(char opr);

    // Pops a value from the stack
    char pop();

    // Returns the value at the top of the stack
    char topValue();

    // Returns the amount of values inside the stack
    int length();

    // Checks if the stack is empty
    bool isEmpty();

    // Prints the contents of the stack
    void print();
};

#endif //CALCULATOR_H