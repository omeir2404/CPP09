#include "RPN.hpp"

int main (int argc, char *argv[]) {
    RPN rpn;
    if (rpn.checkValidInput(argv, argc) == 1) {
        return 1;
    }
    rpn.createInputStack(argv, argc);
    rpn.run();
    return 0;
}