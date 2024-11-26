#include "calculator.h"

// Pushes a value into the stack
void CharacterStack::push(char opr){
    top++;
    stack[top] = opr;
}

// Pops a value from the stack
char CharacterStack::pop(){
    int i = top;
    top--;
    return stack[i];
}

// Returns the value at the top of the stack
char CharacterStack::topValue(){
    return stack[top];
}

// Returns the amount of values inside the stack
int CharacterStack::length(){
    return top + 1;
}

// Checks if the stack is empty
bool CharacterStack::isEmpty(){
    return top == -1;
}

// Prints the contents of the stack
void CharacterStack::print(){
    for(int i = top ; i >= 0 ; i--){
        std::cout << "|  " << stack[i] << "  |" << std::endl;
    }
    std::cout << "+-----+" << std::endl;
}