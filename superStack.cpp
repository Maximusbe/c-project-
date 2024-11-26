#include <iostream>
#include <string>
#include <sstream>

union value{
    int i;
    float f;
    double d;
    char c;
};

class Stack{

private:
    // The stack that contains the operators
    std::string stack[50];
    
    // Variable for the top of the stack
    int length = -1;

public:

    // Pushes a integer value into the stack
    void push(int value){
        std::string newValue = std::to_string(value);
        length++;
        stack[length] = newValue;
    }

    // Pushes a float value into the stack
    void push(float value){
        std::string newValue = std::to_string(value);
        length++;
        stack[length] = newValue;
    }

    // Pushes a double value into the stack
    void push(double value){
        std::string newValue = std::to_string(value);
        length++;
        stack[length] = newValue;
    }

    // Pushes a char value into the stack
    void push(char value){
        length++;
        stack[length] = value;
    }

    // Pops a value from the stack
    value pop(){
        // Checks if the stack is empty
        if (length < 0) {
            throw std::out_of_range("Stack is empty");
        }
        
        std::string topValue = stack[length];
        length--;

        value returnValue;

        // Attempt to deduce the type from the string value
        std::istringstream ss(topValue);

        // Checks if it's an integer
        int intVal;
        if (ss >> intVal && ss.eof()) {
            returnValue.i = intVal;
            return returnValue;
        }

        // Checks if it's a float
        std::istringstream ssFloat(topValue);
        float floatVal;
        if (ssFloat >> floatVal && ssFloat.eof()) {
            returnValue.f = floatVal;
            return returnValue;
        }

        // Checks if it's a double
        std::istringstream ssDouble(topValue);
        double doubleVal;
        if (ssDouble >> doubleVal && ssDouble.eof()) {
            returnValue.d = doubleVal;
            return returnValue;
        }

        // Checks if it's a char (single character string)
        if (topValue.length() == 1) {
            returnValue.c = topValue[0];
            return returnValue;
        }

        // If it's none of the above, assume it's a string
        return returnValue;
    }

    // Returns the value at the top of the stack
    std::string top(){
        return stack[length];
    }

    // Checks if the stack is empty
    bool isEmpty(){
        if(length == -1){
            return true;
        }
        else{
            return false;
        }
    }

    // Prints the contents of the stack
    void print(){
        for(int i = length ; i >= 0 ; i--){

            std::cout << stack[i] << std::endl;
        }
        std::cout << "\\__________/" << std::endl;
    }

};