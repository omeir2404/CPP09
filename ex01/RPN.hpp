#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cmath>
#include <cctype>
#include <cstring> // For strtok

class RPN {

private: 
    std::stack<std::string> InputStack;

public: 
    RPN();
    ~RPN();
    RPN(const RPN &rpn);
    RPN &operator=(const RPN &rpn);

    int createInputStack(char *input[], int argc);
    void run();
    double handleOps(char token, double value1, double value2);
    void splitString(const std::string& str, char*** result, int* count, char delimiter = ' ') ;
    int checkValidInput(char *input[], int argc);

void printStack(std::stack<std::string> s);
};

#endif
