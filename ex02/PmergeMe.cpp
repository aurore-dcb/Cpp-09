#include "PmergeMe.hpp"

void printPairs(const std::vector<Pair>& pairs) {
    for (size_t i = 0 ; i < pairs.size() ; i++) {
        std::cout << pairs[i].first << "," << pairs[i].second << std::endl;
    }
}

void PmergeMe::displayBefore(int argc, char **argv) const {

    int i = 1;
    while (i < argc && i <= 5) {
        std::cout << argv[i];
        if (i <= 4)
            std::cout << " ";
        i++;
    }
    if (argc > 6)
        std::cout << " [...]";
    std::cout << std::endl; 
}

void PmergeMe::displayAfter() const {

    size_t i = 0;
    while (i < main.size() && i < 5) {
        std::cout << main[i];
        if (i < 4)
            std::cout << " ";
        i++;
    }
    if (main.size() >= 6)
        std::cout << " [...]";
    std::cout << std::endl; 
}

void PmergeMe::doSort(int argc, char **argv) {

    PmergeMe inst;

    try {
        std::chrono::high_resolution_clock::time_point start_time;
        std::chrono::high_resolution_clock::time_point end_time;
        std::chrono::high_resolution_clock::time_point start_time2;
        std::chrono::high_resolution_clock::time_point end_time2;
        
        // vector
        start_time = std::chrono::high_resolution_clock::now();
        
        inst.parseInput(argc, argv);
        inst.mergeSort(0, inst.pairs.size() - 1);
        inst.createChain();
        inst.main.insert(inst.main.begin(), inst.pend[0]);
        inst.JacobsthalSuite();
        end_time = std::chrono::high_resolution_clock::now();

        // deque
        start_time2 = std::chrono::high_resolution_clock::now();

        inst.parseInput2(argc, argv);
        inst.mergeSort2(0, inst.pairs2.size() - 1);
        inst.createChain2();
        inst.main2.insert(inst.main2.begin(), inst.pend2[0]);
        inst.JacobsthalSuite2();
        end_time2 = std::chrono::high_resolution_clock::now();

        std::cout << "Before: ";
        inst.displayBefore(argc, argv);
        std::cout << "After:  ";
        inst.displayAfter();

        // time
        std::chrono::nanoseconds::rep duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        std::cout << "Time to process a range of " << inst.main.size() << " elements with std::vector : " << duration_ns << " ns." << std::endl;
        std::chrono::nanoseconds::rep duration_ns2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time2 - start_time2).count();
        std::cout << "Time to process a range of " << inst.main.size() << " elements with std::deque  : " << duration_ns2 << " ns." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error" << std::endl;
    }
}

void PmergeMe::merge(int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;
    std::vector<Pair> leftArray(n1);
    std::vector<Pair> rightArray(n2);

    for (int i = 0; i < n1; i++) {
        leftArray[i] = pairs[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = pairs[middle + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i].second >= rightArray[j].second) {
            pairs[k] = leftArray[i];
            i++;
        } else {
            pairs[k] = rightArray[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        pairs[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < n2) {
        pairs[k] = rightArray[j];
        j++;
        k++;
    }
}

void PmergeMe::merge2(int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;
    std::deque<Pair> leftArray(n1);
    std::deque<Pair> rightArray(n2);

    for (int i = 0; i < n1; i++) {
        leftArray[i] = pairs2[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = pairs2[middle + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i].second >= rightArray[j].second) {
            pairs2[k] = leftArray[i];
            i++;
        } else {
            pairs2[k] = rightArray[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        pairs2[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < n2) {
        pairs2[k] = rightArray[j];
        j++;
        k++;
    }
}

void PmergeMe::mergeSort(int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(left, middle);
        mergeSort(middle + 1, right);
        merge(left, middle, right);
    }
}

void PmergeMe::mergeSort2(int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort2(left, middle);
        mergeSort2(middle + 1, right);
        merge2(left, middle, right);
    }
}

bool PmergeMe::isDouble(int n) {

    for (std::vector<Pair>::iterator it = pairs.begin(); it != pairs.end(); ++it) {
        if (n == it->first || n == it->second)
            return true;
    }
    return false;
}

bool PmergeMe::isDouble2(int n) {

    for (std::deque<Pair>::iterator it = pairs2.begin(); it != pairs2.end(); ++it) {
        if (n == it->first || n == it->second)
            return true;
    }
    return false;
}

void PmergeMe::parseInput(int argc, char **argv) {
    int i = 1;
    Pair newPair;
    while (i < argc) {
        int a = std::stoi(argv[i]);
        if (isDouble(a) || a < 0)
            throw std::exception();
        if (i == argc - 1 && (argc - 1) % 2 != 0) {
            pend.insert(pend.begin(), a);
        } else if (i % 2 != 0) {
            newPair.first = a;
        } else {
            newPair.second = a;
            pairs.push_back(newPair);
        }
        i++;
    }
    for (size_t i = 0 ; i < pairs.size() ; i++) {
        if (pairs[i].first > pairs[i].second) {
            std::swap(pairs[i].first, pairs[i].second);
        }
    }
}

void PmergeMe::parseInput2(int argc, char **argv) {
    int i = 1;
    Pair newPair;
    while (i < argc) {
        int a = std::stoi(argv[i]);
        if (isDouble2(a) || a < 0)
            throw std::exception();
        if (i == argc - 1 && (argc - 1) % 2 != 0) {
            pend2.insert(pend2.begin(), a);
        } else if (i % 2 != 0) {
            newPair.first = a;
        } else {
            newPair.second = a;
            pairs2.push_back(newPair);
        }
        i++;
    }
    for (size_t i = 0 ; i < pairs2.size() ; i++) {
        if (pairs2[i].first > pairs2[i].second) {
            std::swap(pairs2[i].first, pairs2[i].second);
        }
    }
}

void PmergeMe::createChain() {

    size_t i = 0;
    while (i < pairs.size()) {
        main.insert(main.begin(), pairs[i].second);
        i++;
    }
    i = 0;
    while (i < pairs.size()) {
        if (pairs[i].first == -1)
            break;
        pend.insert(pend.begin(), pairs[i].first);
        i++;
    }
}

void PmergeMe::createChain2() {

    size_t i = 0;
    while (i < pairs2.size()) {
        main2.insert(main2.begin(), pairs2[i].second);
        i++;
    }
    i = 0;
    while (i < pairs2.size()) {
        if (pairs2[i].first == -1)
            break;
        pend2.insert(pend2.begin(), pairs2[i].first);
        i++;
    }
}

int PmergeMe::jacobsthal(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
    }
}

int PmergeMe::findMax(int y) {

    int indice = pairs.size() - 1 - y;
    int n = pairs[indice].second;
    size_t i = 0;
    while (i < main.size()) {
        if (main[i] == n) {
            return i - 1;
        }
        i++; 
    }
    return (0);
}

int PmergeMe::findMax2(int y) {

    int indice = pairs2.size() - 1 - y;
    int n = pairs2[indice].second;
    size_t i = 0;
    while (i < main2.size()) {
        if (main2[i] == n) {
            return i - 1;
        }
        i++; 
    }
    return (0);
}

bool PmergeMe::isInPair(int n) {

    for (std::vector<Pair>::iterator it = pairs.begin(); it != pairs.end(); ++it) {
        if (n == it->first)
            return true;
    }
    return false;
}

bool PmergeMe::isInPair2(int n) {

    for (std::deque<Pair>::iterator it = pairs2.begin(); it != pairs2.end(); ++it) {
        if (n == it->first)
            return true;
    }
    return false;
}

void PmergeMe::JacobsthalSuite() {

    size_t N = 3;
    size_t i = jacobsthal(N) - 1;
    size_t back = jacobsthal(N - 1) - 1;
    bool quit = false;

    if (pend.size() > 1) {
        while (1) {
            while (i > back) {
                while (i >= pend.size()) {
                    quit = true;
                    i--;
                    if (back == pend.size() - 1)
                        return;
                }
                int max;
                if (!isInPair(pend[i]))
                    max = main.size() - 1;
                else
                    max = findMax(i);
                main.insert(main.begin() + rechercheDichotomique(max, pend[i]), pend[i]);
                i--;
            }
            if (quit)
                return;
            N++;
            i = jacobsthal(N) - 1;
            back = jacobsthal(N - 1) - 1;
        }
    }
}

void PmergeMe::JacobsthalSuite2() {

    size_t N = 3;
    size_t i = jacobsthal(N) - 1;
    size_t back = jacobsthal(N - 1) - 1;
    bool quit = false;

    if (pend2.size() > 1) {
        while (1) {
            while (i > back) {
                while (i >= pend2.size()) {
                    quit = true;
                    i--;
                    if (back == pend2.size() - 1)
                        return;
                }
                int max;
                if (!isInPair2(pend2[i]))
                    max = main2.size() - 1;
                else
                    max = findMax2(i);
                main2.insert(main2.begin() + rechercheDichotomique2(max, pend2[i]), pend2[i]);
                i--;
            }
            if (quit)
                return;
            N++;
            i = jacobsthal(N) - 1;
            back = jacobsthal(N - 1) - 1;
        }
    }
}

int PmergeMe::rechercheDichotomique(int max, int n) {
    
    int min = 0;
    if (n > main[max])
        return max + 1;
    while (min < max) {
        int middle = (min + max) / 2;
        if (n <= main[middle])
            max = middle;
        else
            min = middle + 1;
    }
    return min;
}

int PmergeMe::rechercheDichotomique2(int max, int n) {
    
    int min = 0;
    if (n > main2[max])
        return max + 1;
    while (min < max) {
        int middle = (min + max) / 2;
        if (n <= main2[middle])
            max = middle;
        else
            min = middle + 1;
    }
    return min;
}