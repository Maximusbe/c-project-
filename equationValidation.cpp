#include "calculator.h"

// Validates the equation
std::string Validate::validateEquation(std::string equation) {

    // Erases all the spaces inside the equation
    for(int i = 0; i < equation.length(); i++){
        if(equation.at(i) == ' ') {
            equation.erase(i, 1);
            i--;
        }
    }

    // Variables that keep track of the number
    // of parentheses and dots
    int countParentheses = 0;
    int countPoints = 0;

    for(int i = 0; i < equation.length(); i++){

        // Throws an error if there are more 
        // than two dots in a number
        if(equation.at(i) == '.' && countPoints > 0){
            throw MathException("Unnecessary dot in equation");
        }

        if(equation.at(i) == '.'){
            countPoints++;
        }

        // Prevents two operands from being next to one another
        else if(equation.at(i) == '^' || equation.at(i) == '*' || 
                equation.at(i) == '/' || equation.at(i) == '+' || 
                equation.at(i) == '-'){
            
            int temp = i;
            temp++;

            if(countPoints > 0)
                countPoints--;

            switch (equation.at(temp)) {
            case '^':
                throw MathException("Unnecessary exponant symbol");
                break;
            case '*':
                throw MathException("Unnecessary multiplication symbol");
                break;
            case '/':
                throw MathException("Unnecessary division symbol");
                break;
            case '+':
                throw MathException("Unnecessary addition symbol");
                break;
            case '-':
                throw MathException("Unnecessary subtraction symbol");
                break;
            case ')':
                throw MathException("Missing digit");
                break;
            }
        }

        // Assures that parentheses are placed after a function
        else if(equation.at(i) == 'R' || equation.at(i) == 'L' || 
                equation.at(i) == 'N' || equation.at(i) == 'S' ||
                equation.at(i) == 'C' || equation.at(i) == 'T' || 
                equation.at(i) == 's' || equation.at(i) == 'c' ||
                equation.at(i) == 't'){
            
            int temp = i;
            temp++;

            if(countPoints > 0)
                countPoints--;

            if(equation.at(temp) != '('){
                throw MathException("Missing parentheses after function");
            }
            
        }

        // Increases parentheses count and prevents
        // a pair of parentheses from being empty
        else if(equation.at(i) == '(') {
            countParentheses++;

            int temp = i;
            temp++;

            if(equation.at(temp) == ')')
                throw MathException("Cannot have an empty set of parentheses");

            if(countPoints > 0)
                countPoints--;
        }

        // Decreases parentheses count
        else if(equation.at(i) == ')') {
            countParentheses--;

            if(countPoints > 0)
                countPoints--;
        }

        // Throw an exception if an illegal value is examined
        else if(!isdigit((equation.at(i)))){
            throw MathException("Invalid syntax");
        }
    }

    // Assures that there's not mismatched parentheses within the equation
    if(countParentheses != 0){
        throw MathException("Mismatched parentheses in equation");
    }

    return equation;
}