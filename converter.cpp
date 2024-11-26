#include "calculator.h"

// Converts from infix notation to postfix notation
std::string Converter::infixToPostfix(std::string equation){

    CharacterStack stack;
    Priority priority;
        
    std::string result;

    // Loop to go through the equation one value at a time
    for(int i = 0; i < equation.length(); ++i){
        char value = equation.at(i);

        // If the scanned character is
        // an number, add it to the result string.
         if((value >= '0' && value <= '9')){
             result += value;
         }

         // If the scanned character is an
        // dot(.), add it to the result string.
        else if(value == '.'){
            result += value;
        }

        // If the scanned character is an
        // ‘(‘, push it to the stack.
        else if(value == '('){
            stack.push('(');
            i++;
            if(equation.at(i) == '-'){
                result += "0 ";
            }
            i--;
        }

        // If the scanned character is an ‘)’,
        // pop and add to the result string from the stack
        // until an ‘(‘ is encountered.
        else if(value == ')') {
            while (stack.topValue() != '(') {
                result = result + " " + stack.pop() + " ";
            }
            stack.pop(); 
        }

        // If an operator is scanned
        else{
            while(!stack.isEmpty() && priority.optCheck(value) < priority.optCheck(stack.topValue()) ||
                !stack.isEmpty() && priority.optCheck(value) == priority.optCheck(stack.topValue())) {
                result = result + " " + stack.pop() + " ";
            }
            stack.push(value);
            result += " ";
        }
    }

    // Pop all the remaining elements from the stack
    while(!stack.isEmpty()) {
        result = result + " " + stack.pop() + " ";
    }
    return result;
}