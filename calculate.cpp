#include "calculator.h"
#include "qmath.h"

// Uses the value given and does the appropriate calculation
double Calculate::calculations(double value, char opt){

    double result;

    switch(opt){
        case 'R':
            if(value < 0)
                throw MathException("Cannot square root a negative number");
            else
                result = sqrt(value);
            break;
        case 'L':
            if(value <= 0)
                throw MathException("Cannot have a zero or negative number in log");
            else
                result = log10(value);
            break;
        case 'N':
            if(value <= 0)
                throw MathException("Cannot have a zero or negative number in ln");
            else
                result = log(value);
            break;
    }
    return result;
}


// Uses the value and the type of angle and does the appropriate calculation
double Calculate::calculations(double value, char opt, bool angle){

    double result;
    double PI = M_PI;

    // If angle is equal to true, then calculates using radians
    // If angle is equal to false, then calculates using degree
    switch(opt){
        case 'S':
            if(angle)
                result = sin(value);
            else
                result = sin(value * PI/180);
            break;
        case 'C':
            if(angle)
                result = cos(value);
            else
                result = cos(value * PI/180);
            break;
        case 'T':
            if(angle)
                result = tan(value);
            else
                result = tan(value * PI/180);
            break;
        case 's':
            if(value < -1 || value > 1)
                throw MathException("Cannot have a value less then -1 or greater then 1");
            else if(angle)
                result = asin(value);
            else
                result = asin(value) * 180/PI;
            break;
        case 'c':
            if(value < -1 || value > 1)
                throw MathException("Cannot have a value less then -1 or greater then 1");
            else if(angle)
                result = acos(value);
            else
                result = acos(value) * 180/PI;
            break;
        case 't':
            if(angle)
                result = atan(value);
            else
                result = atan(value) * 180/PI;
            break;
    }
    return result;
}
    
// Uses the two values given and does the appropriate calculation
double Calculate::calculations(double value1, double value2, char opt){

    double result;

    switch(opt){
        case '^':
            result = pow(value1, value2);
            break;
        case '/':
            if(value2 == 0)
                throw MathException("Cannot divide by zero");
            else
                result = value1 / value2;
            break;
        case '*':
            result = value1 * value2;
            break;
        case '+':
            result = value1 + value2;
            break;
        case '-':
            result = value1 - value2;
            break;
    }
    return result;
}
