#include "RPN.hpp"

RPN::RPN()
{
}

RPN::~RPN()
{
}

RPN::RPN(const RPN &rpn)
{
}

RPN &RPN::operator=(const RPN &rpn)
{
    return *this;
}

void RPN::splitString(const std::string& str, char*** result, int* count, char delimiter) {
    // Count the number of tokens
    *count = 0;
    char* temp = new char[str.length() + 1];
    std::strcpy(temp, str.c_str());
    char delim[2] = {delimiter, '\0'};
    char* token = std::strtok(temp, delim);
    while (token != nullptr) {
        (*count)++;
        token = std::strtok(nullptr, delim);
    }
    delete[] temp;

    // Allocate memory for the result array
    *result = new char*[*count];

    // Tokenize the string again and copy the tokens into the result array
    temp = new char[str.length() + 1];
    std::strcpy(temp, str.c_str());
    token = std::strtok(temp, delim);
    int index = 0;
    while (token != nullptr) {
        (*result)[index] = new char[std::strlen(token) + 1];
        std::strcpy((*result)[index], token);
        token = std::strtok(nullptr, delim);
        index++;
    }
    delete[] temp;
}

int RPN::createInputStack(char *input[], int argc)
{
    InputStack = std::stack<std::string>();
    std::string inputString;
    std::istringstream iss(inputString);
    std::string token;
    for (int i = argc - 1; i > 0; i--)
    {
        char **splitResult;
        int count;
        inputString = input[i];
        splitString(inputString, &splitResult, &count, ' ');
        for(int j = count - 1; j >= 0; j--) {
            InputStack.push(splitResult[j]);
        }
        for(int j = 0; j < count; j++) {
            if(splitResult[j] != nullptr)
                delete[] splitResult[j];
        }
        if(splitResult != nullptr)
            delete[] splitResult;
    }

    // std::cout << "Input Stack on creation: ";
    // printStack(InputStack);
    return 0;
}


double RPN::handleOps(char token, double value1, double value2) {
    switch (token) {
        case '+':
            return value1 + value2;
        case '-':
            return value1 - value2;
        case '*':
            return value1 * value2;
        case '/':
            if (value2 == 0) {
                std::cerr << "Error: division by zero" << std::endl;
                exit(1);
            }
            return value1 / value2;
        default:
            std::cerr << "Error: unknown operator " << token << std::endl;
            exit(1);
    }
}

void RPN::run() {
    std::stack<double> evalStack;

    while (!InputStack.empty()) {
        std::string token = InputStack.top();
        InputStack.pop();

        if (isdigit(token[0])) {
            evalStack.push(std::strtod(token.c_str(), NULL));
        } else {
            if (evalStack.size() < 2) {
                std::cerr << "Error: insufficient values in the expression" << std::endl;
                return;
            }
            double value2 = evalStack.top(); evalStack.pop();
            double value1 = evalStack.top(); evalStack.pop();
            double result = handleOps(token[0], value1, value2);
            evalStack.push(result);
        }
    }

    if (evalStack.size() != 1) {
        std::cerr << "Error: the user input has too many values" << std::endl;
    } else {
        std::cout << "Result: " << evalStack.top() << std::endl;
    }
}

int RPN::checkValidInput(char *input[], int argc)
{
    if (argc < 2)
    {
        std::cerr << "Error: no input provided" << std::endl;
        return 1;
    }
    for(int i = 1; i < argc; i++) {
        std::string inputString = input[i];
        for(int j = 0; j < inputString.length(); j++) {
            if(!isdigit(inputString[j]) && inputString[j] != '+' && inputString[j] != '-' && inputString[j] != '*' && inputString[j] != '/' && inputString[j] != ' ') {
                std::cerr << "Error: invalid character in input: " << inputString[j] << std::endl;
                return 1;
            }
        }
    }
    return 0;
}

void RPN::printStack(std::stack<std::string> s)
{
    std::stack<std::string> temp;
    temp = s;
        std::cout << "Input Stack: ";
    while (!temp.empty())
    {
        std::cout << temp.top() << " | ";
        temp.pop();
    }
    std::cout << std::endl;
}