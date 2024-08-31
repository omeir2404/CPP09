#include "RPN.hpp"

RPN::RPN() {
}

RPN::~RPN() {
}

RPN::RPN(const RPN &rpn) {
}

RPN &RPN::operator=(const RPN &rpn) {
    return *this;
}

int RPN::createInputStack(std::string input) {
    InputStack = std::stack<std::string>();
    std::istringstream iss(input);
    std::string token;
    while (std::getline(iss, token, ' ')) {
        InputStack.push(token);
    }
    return 0;
}

void RPN::run(){
    char token;
    int *buffer = new int[InputStack.size()];
    int value1;
    while(!InputStack.empty()){
        while(isdigit(InputStack.top()[0])){

        }
    }


    std::cout << InputStack.top() << std::endl;
}

void printStack(std::stack<std::string> s) {
    std::stack<std::string> temp;
    temp = s;
    while (!temp.empty()) {
        std::cout << temp.top() <<" ";
        temp.pop();
    }
    std::cout << std::endl;
}