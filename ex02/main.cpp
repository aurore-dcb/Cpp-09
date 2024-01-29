#include "PmergeMe.hpp"



int main(int argc, char **argv) {
    
    if (argc >= 3)
        PmergeMe::doSort(argc, argv);
}


/* insertion et suppresion dans un vecteur 
myVector.insert(myVector.begin() + 1, 42); // Insertion de la valeur 42 à la position 1
myVector.erase(myVector.begin() + 2);      // Suppression de l'élément à la position 2 
*/