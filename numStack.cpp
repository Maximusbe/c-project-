#include "calculator.h"

// Pushes an integer value into the stack
void NumberStack::push(double num){
    top++;
    stack[top] = num;
}

// Pops a value from the stack
double NumberStack::pop(){
    if(top == -1){
        return 0;
    }
    else{
        int i = top;
        top--;
        return stack[i];
    }
}

// Returns the value at the top of the stack
double NumberStack::topValue(){
    return stack[top];
}

// Returns the amount of values inside the stack
int NumberStack::length(){
    return top + 1;
}

// Checks if the stack is empty
bool NumberStack::isEmpty(){
    return top == -1;
}

// Prints the contents of the stack
void NumberStack::print(){
    for(int i = top ; i >= 0 ; i--){
        std::cout << stack[i] << std::endl;
    }
    std::cout << "\\__________/" << std::endl;
}