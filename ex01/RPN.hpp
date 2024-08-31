#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <cmath>
#include <cctype>

class RPN {

private: 
    std::stack<std::string> InputStack;

public: 
    RPN();
    ~RPN();
    RPN(const RPN &rpn);
    RPN &operator=(const RPN &rpn);

    int createInputStack(std::string input);
    void run();


};

#endif
