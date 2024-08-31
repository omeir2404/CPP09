#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error: No sequence provided." << std::endl;
        return 1;
    }

    std::vector<int> sequence;
    for (int i = 1; i < argc; i++)
    {
        try
        {
            int num = std::stoi(argv[i]);
            sequence.push_back(num);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: Invalid argument." << std::endl;
            return 1;
        }
    }

    PmergeMe pmergeMe;
    pmergeMe.sortSequence(sequence);

    return 0;
}