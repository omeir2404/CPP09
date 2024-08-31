#include "RPN.hpp"

int main (int argc, char *argv[]) {
    RPN rpn;
    createInputStack(argv[1]);
    rpn.run();
    return 0;
}