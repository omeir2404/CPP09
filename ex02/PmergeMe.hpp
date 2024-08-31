#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <chrono>
#include <iterator>

class PmergeMe
{
public:
    PmergeMe();
    ~PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);

    void sortSequence(const std::vector<int> &sequence);
    void displaySequence(const std::vector<int> &sequence, const std::string &message);
    void displayTime(const std::chrono::microseconds &time, const std::string &container, int size);

private:
    std::vector<int> mergeInsertSort(const std::vector<int> &sequence);
    std::list<int> mergeInsertSort(const std::list<int> &sequence);
};


#endif
