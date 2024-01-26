#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <stdexcept>

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
        void merge(int left, int middle, int right);
        void mergeSort(int left, int right);
        void sortBySecond();
        void orderPairs();
        void parseInput(int argc, char **argv);
        void createMainChain();
        void createPendChain();
        int jacobsthal(int n);
        void JacobsthalSuite();


    private:

    private:
        std::vector<Pair> pairs;
        std::vector<int> main;
        std::vector<int> pend;
};

#endif