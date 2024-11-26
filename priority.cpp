#include "calculator.h"

// A switch that returns the priority of the operator
int Priority::optCheck(char opt){

    switch(opt){
        case 'R':
            return 3;
            break;
        case 'L':
            return 3;
            break;
        case 'N':
            return 3;
            break;
        case 'S':
            return 3;
            break;
        case 'C':
            return 3;
            break;
        case 'T':
            return 3;
            break;
        case 's':
            return 3;
            break;
        case 'c':
            return 3;
            break;
        case 't':
            return 3;
            break;
        case '^':
            return 2;
            break;
        case '*':
            return 1;
            break;
        case '/':
            return 1;
            break;
        case '+':
            return 0;
            break;
        case '-':
                return 0;
             break;
        default:
            return -1;
    }
}