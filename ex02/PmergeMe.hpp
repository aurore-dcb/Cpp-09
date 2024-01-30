#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <ctime>
#include <chrono>
#include <deque>

struct Pair {
    int first;
    int second;
};

class PmergeMe {

    public:
        PmergeMe( void ) {}
        ~PmergeMe( void ) {}
        PmergeMe(const PmergeMe& cpy) { *this = cpy; }
        PmergeMe& operator=(const PmergeMe& rhs) {
            (void)rhs;
            return *this;
        }

        static void doSort(int argc, char **argv);
        void displayBefore(int argc, char **argv) const;
        void displayAfter() const;

    private:
        void merge(int left, int middle, int right);
        void mergeSort(int left, int right);
        void parseInput(int argc, char **argv);
        void createChain();
        int jacobsthal(int n);
        void JacobsthalSuite();
        int rechercheDichotomique(int max, int n);
        int findMax(int y);
        bool isInPair(int n);
        bool isDouble(int n);

        void merge2(int left, int middle, int right);
        void mergeSort2(int left, int right);
        void parseInput2(int argc, char **argv);
        void createChain2();
        int findMax2(int y);
        void JacobsthalSuite2();
        int rechercheDichotomique2(int max, int n);
        bool isInPair2(int n);
        bool isDouble2(int n);

    private:
        std::vector<Pair> pairs;
        std::vector<int> main;
        std::vector<int> pend;

        std::deque<Pair> pairs2;
        std::deque<int> main2;
        std::deque<int> pend2;
};

#endif