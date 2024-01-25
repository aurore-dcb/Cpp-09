#include "PmergeMe.hpp"

#include <iostream>
#include <vector>
#include <stdexcept>

struct Pair {
    int first;
    int second;
};

// Fonction de fusion pour le tri
void merge(std::vector<Pair>& pairs, int left, int middle, int right) {
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
void mergeSort(std::vector<Pair>& pairs, int left, int right) {
    if (left < right) {
        // Trouver le milieu de l'array
        int middle = left + (right - left) / 2;

        // Tri des deux moitiés
        mergeSort(pairs, left, middle);
        mergeSort(pairs, middle + 1, right);

        // Fusion des deux moitiés triées
        merge(pairs, left, middle, right);
    }
}

// Fonction de tri par la plus grande valeur de la paire
void sortBySecond(std::vector<Pair>& pairs) {
    mergeSort(pairs, 0, pairs.size() - 1);
}

void printPairs(const std::vector<Pair>& pairs) {
    for (size_t i = 0 ; i < pairs.size() ; i++) {
        std::cout << pairs[i].first << "," << pairs[i].second << std::endl;
    }
}

void orderPairs(std::vector<Pair>& pairs) {
    for (size_t i = 0 ; i < pairs.size() ; i++) {
        if (pairs[i].first > pairs[i].second) {
            std::swap(pairs[i].first, pairs[i].second);
        }
    }
}

void parseInput(int argc, char **argv, std::vector<Pair>& pairs) {
    int i = 1;
    Pair newPair;
    while (i < argc) {
        int a = std::stoi(argv[i]);
        if (a < 0)
            throw std::exception();
        if (i == argc - 1 && (argc - 1) % 2 != 0) {
            newPair.first = a;
            newPair.second = -1;
            pairs.push_back(newPair);
        } else if (i % 2 != 0) {
            newPair.first = a;
        } else {
            newPair.second = a;
            pairs.push_back(newPair);
        }
        i++;
    }
    orderPairs(pairs);
}

int main(int argc, char **argv) {
    
    std::vector<Pair> pairs;
    try {
        parseInput(argc, argv, pairs);
        sortBySecond(pairs);
        printPairs(pairs);
    } catch (const std::exception& e) {
        std::cerr << "Error." << std::endl;
    }
}


/* insertion et suppresion dans un vecteur 
myVector.insert(myVector.begin() + 1, 42); // Insertion de la valeur 42 à la position 1
myVector.erase(myVector.begin() + 2);      // Suppression de l'élément à la position 2 
*/