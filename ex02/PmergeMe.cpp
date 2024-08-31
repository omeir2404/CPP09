#include "PmergeMe.hpp"
#include <iomanip> // Add this line to include the necessary header for setprecision

PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    return *this;
}

void PmergeMe::sortSequence(const std::vector<int> &sequence)
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::vector<int> sortedVector = mergeInsertSort(sequence);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    displaySequence(sequence, "Before: ");
    displaySequence(sortedVector, "After: ");
    displayTime(duration, "vector", sequence.size());

    std::list<int> sequenceList(sequence.begin(), sequence.end());
    start = std::chrono::high_resolution_clock::now();
    std::list<int> sortedList = mergeInsertSort(sequenceList);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    displayTime(duration, "list", sequence.size());
}

void PmergeMe::displaySequence(const std::vector<int> &sequence, const std::string &message)
{
    std::cout << message;
    for (std::vector<int>::const_iterator it = sequence.begin(); it != sequence.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::displayTime(const std::chrono::microseconds &time, const std::string &container, int size)
{
    std::cout << "Time to process a range of " << size << " elements with std::" << container << " : " << std::fixed << std::setprecision(5) << static_cast<double>(time.count()) << " us" << std::endl;
}

std::vector<int> PmergeMe::mergeInsertSort(const std::vector<int> &sequence)
{
    if (sequence.size() <= 1)
    {
        return sequence;
    }

    int mid = sequence.size() / 2;
    std::vector<int> left(sequence.begin(), sequence.begin() + mid);
    std::vector<int> right(sequence.begin() + mid, sequence.end());

    left = mergeInsertSort(left);
    right = mergeInsertSort(right);

    std::vector<int> sortedVector;
    sortedVector.reserve(sequence.size());

    int i = 0, j = 0;
    while (i < left.size() && j < right.size())
    {
        if (left[i] <= right[j])
        {
            sortedVector.push_back(left[i]);
            i++;
        }
        else
        {
            sortedVector.push_back(right[j]);
            j++;
        }
    }

    while (i < left.size())
    {
        sortedVector.push_back(left[i]);
        i++;
    }

    while (j < right.size())
    {
        sortedVector.push_back(right[j]);
        j++;
    }

    return sortedVector;
}

// Helper function to merge two sorted lists
std::list<int> merge(const std::list<int>& left, const std::list<int>& right) {
    std::list<int> result;
    std::list<int>::const_iterator itLeft = left.begin();
    std::list<int>::const_iterator itRight = right.begin();

    while (itLeft != left.end() && itRight != right.end()) {
        if (*itLeft <= *itRight) {
            result.push_back(*itLeft);
            ++itLeft;
        } else {
            result.push_back(*itRight);
            ++itRight;
        }
    }

    result.insert(result.end(), itLeft, left.end());
    result.insert(result.end(), itRight, right.end());

    return result;
}

// Ford-Johnson algorithm for sorting a list
std::list<int> PmergeMe::mergeInsertSort(const std::list<int> &sequence) {
    if (sequence.size() <= 1) {
        return sequence;
    }

    // Step 1: Divide the list into pairs
    std::list<std::list<int>> pairs;
    std::list<int>::const_iterator it = sequence.begin();
    while (it != sequence.end()) {
        std::list<int> pair;
        pair.push_back(*it);
        ++it;
        if (it != sequence.end()) {
            pair.push_back(*it);
            ++it;
        }
        pairs.push_back(pair);
    }

    // Step 2: Sort each pair
    for (std::list<std::list<int>>::iterator it = pairs.begin(); it != pairs.end(); ++it) {
        (*it).sort();
    }

    // Step 3: Merge pairs into a single sorted list
    while (pairs.size() > 1) {
        std::list<std::list<int>> newPairs;
        std::list<std::list<int>>::iterator it = pairs.begin();
        while (it != pairs.end()) {
            std::list<int> left = *it;
            ++it;
            if (it != pairs.end()) {
                std::list<int> right = *it;
                ++it;
                newPairs.push_back(merge(left, right));
            } else {
                newPairs.push_back(left);
            }
        }
        pairs = newPairs;
    }

    return pairs.front();
}
