#include "calculator.h"

// Calculates the postfix equation
double Solver::calculatePostfix(std::string equation, bool angle){

    NumberStack stack;
    Calculate calculate;
    
    for(int i = 0; i < equation.length(); ++i){

        // Skips to the next iteration if 
        // the scanned character is a space
        if(equation.at(i) == ' '){
            continue;
        }
            
        // If the scanned character is an operand 
        // (number here), push it to the stack.
        if(isdigit(equation.at(i))){
            double num = 0;

            int numberOfDecimals = 0;
            bool decimalExists = false;
            
            while(isdigit(equation.at(i)) || equation.at(i) == '.'){

                if(equation.at(i) == '.'){
                    i++;
                    decimalExists = true;
                    continue;
                }

                num = ((num * 10) + equation.at(i) - '0');
                i++;

                if(decimalExists){
                    numberOfDecimals++;
                }
            }
            i--;

            int j = 0;
            while(j < numberOfDecimals){
                num /= 10;
                j++;
                }
            stack.push(num);
        }
    
        // If the scanned character is an operator, 
        // pop the necessary elements from the stack 
        // and apply the operator
        else{

            double val1, val2, value;

            switch (equation.at(i)) {
            case 'R':
                val1 = stack.pop();
                value = calculate.calculations(val1, equation.at(i));
                stack.push(value);
                break;
            case 'L':
                val1 = stack.pop();
                value = calculate.calculations(val1, equation.at(i));
                stack.push(value);
                break;
            case 'N':
                val1 = stack.pop();
                value = calculate.calculations(val1, equation.at(i));
                stack.push(value);
                break;
            case 'S':
                val1 = stack.pop();
                value = calculate.calculations(val1, equation.at(i), angle);
                stack.push(value);
                break;
            case 'C':
                val1 = stack.pop();
                value = calculate.calculations(val1, equation.at(i), angle);
                stack.push(value);
                break;
            case 'T':
                val1 = stack.pop();
                value = calculate.calculations(val1, equation.at(i), angle);
                stack.push(value);
                break;
            case 's':
                val1 = stack.pop();
                value = calculate.calculations(val1, equation.at(i), angle);
                stack.push(value);
                break;
            case 'c':
                val1 = stack.pop();
                value = calculate.calculations(val1, equation.at(i), angle);
                stack.push(value);
                break;
            case 't':
                val1 = stack.pop();
                value = calculate.calculations(val1, equation.at(i), angle);
                stack.push(value);
                break;
            default:
                val2 = stack.pop();
                val1 = stack.pop();
                value = calculate.calculations(val1, val2, equation.at(i));
                stack.push(value);
                break;
            }
        }
    }
    return stack.pop();
}