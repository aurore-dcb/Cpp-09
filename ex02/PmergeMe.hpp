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

    private:
        void merge(int left, int middle, int right);
        void mergeSort(int left, int right);
        void sortBySecond();
        void parseInput(int argc, char **argv);
        void createChain();
        int jacobsthal(int n);
        void JacobsthalSuite();

        int rechercheDichotomique(int max, int n);

        int findMax(int y);
        bool isInPair(int n);
        bool isDouble(int n);


    private:
        std::vector<Pair> pairs;
        std::vector<int> main;
        std::vector<int> pend;
};

#endif