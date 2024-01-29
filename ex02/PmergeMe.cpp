#include "PmergeMe.hpp"

void printPairs(const std::vector<Pair>& pairs) {
    for (size_t i = 0 ; i < pairs.size() ; i++) {
        std::cout << pairs[i].first << "," << pairs[i].second << std::endl;
    }
}

void PmergeMe::doSort(int argc, char **argv) {

    PmergeMe inst;

    try {
        inst.parseInput(argc, argv);
        inst.sortBySecond();

        inst.createMainChain();
        inst.createPendChain();

        printPairs(inst.pairs);

        //ajouter le premier element de pend au debut de main
        inst.main.insert(inst.main.begin(), inst.pend[0]);

        //ajouter chaque element en suivant la liste d'indice
        //et ajouter avec une recherche dichotomique qui porte sur les elements qui vont du debut a x(i) non compris
        // inst.JacobsthalSuite();
        // std::cout << std::endl;

        // size_t i = 0;
        //  std::cout << "main" << std::endl;
        // while (i < inst.main.size()) {
        //     std::cout << inst.main[i] << ", ";
        //     i++;
        // }
        // std::cout << std::endl << "pend" << std::endl;
        // i = 0;
        // while (i < inst.pend.size()) {
        //     std::cout << inst.pend[i] << ", ";
        //     i++;
        // }
    } catch (const std::exception& e) {
        std::cerr << "Error." << std::endl;
    }
}

// Fonction de fusion pour le tri
void PmergeMe::merge(int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Création de tableaux temporaires
    std::vector<Pair> leftArray(n1);
    std::vector<Pair> rightArray(n2);

    // Copie des données dans les tableaux temporaires
    for (int i = 0; i < n1; i++) {
        leftArray[i] = pairs[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = pairs[middle + 1 + j];
    }

    // Fusion des tableaux temporaires dans le vecteur original
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

    // Copie des éléments restants de leftArray, le cas échéant
    while (i < n1) {
        pairs[k] = leftArray[i];
        i++;
        k++;
    }

    // Copie des éléments restants de rightArray, le cas échéant
    while (j < n2) {
        pairs[k] = rightArray[j];
        j++;
        k++;
    }
}

// Fonction de tri fusion récursif
void PmergeMe::mergeSort(int left, int right) {
    if (left < right) {
        // Trouver le milieu de l'array
        int middle = left + (right - left) / 2;

        // Tri des deux moitiés
        mergeSort(left, middle);
        mergeSort(middle + 1, right);

        // Fusion des deux moitiés triées
        merge(left, middle, right);
    }
}

// Fonction de tri par la plus grande valeur de la paire
void PmergeMe::sortBySecond() {
    mergeSort(0, pairs.size() - 1);
}

void PmergeMe::orderPairs() {
    for (size_t i = 0 ; i < pairs.size() ; i++) {
        if (pairs[i].first > pairs[i].second) {
            std::swap(pairs[i].first, pairs[i].second);
        }
    }
}

void PmergeMe::parseInput(int argc, char **argv) {
    int i = 1;
    Pair newPair;
    while (i < argc) {
        int a = std::stoi(argv[i]);
        if (a < 0)
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
    orderPairs();
}

void PmergeMe::createMainChain() {

    size_t i = 0;
    while (i < pairs.size()) {
        main.insert(main.begin(), pairs[i].second);
        i++;
    }
}

void PmergeMe::createPendChain() {

    size_t i = 0;
    while (i < pairs.size()) {
        if (pairs[i].first == -1)
            break;
        pend.insert(pend.begin(), pairs[i].first);
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
                }
                std::cout << i + 1 << ", ";
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