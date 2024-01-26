#include "PmergeMe.hpp"

// void printPairs(const std::vector<Pair>& pairs) {
//     for (size_t i = 0 ; i < pairs.size() ; i++) {
//         std::cout << pairs[i].first << "," << pairs[i].second << std::endl;
//     }
// }

int main(int argc, char **argv) {
    
    // std::vector<Pair> pairs;
    // std::vector<int> main;
    // std::vector<int> pend;

    PmergeMe::doSort(argc, argv);
    // try {
    //     parseInput(argc, argv, pairs, pend);
    //     sortBySecond(pairs);

    //     createMainChain(pairs, main);
    //     createPendChain(pairs, pend);

    //     //ajouter le premier element de pend au debut de main
    //     main.insert(main.begin(), pend[0]);

    //     //ajouter chaque element en suivant la liste d'indice
    //     //et ajouter avec une recherche dichotomique qui porte sur les elements qui vont du debut a x(i) non compris
    //     JacobsthalSuite(main, pend);
    //     std::cout << std::endl;
    //     // printPairs(pairs);

    //     // suite de Jacobsthal
    //     // for(int i = 0; i < 5 ; i++) {
    //     //     std::cout << jacobsthal(i) << ", ";
    //     // }
    //     // std::cout << std::endl;

    //     size_t i = 0;
    //      std::cout << "main" << std::endl;
    //     while (i < main.size()) {
    //         std::cout << main[i] << ", ";
    //         i++;
    //     }
    //     std::cout << std::endl << "pend" << std::endl;
    //     i = 0;
    //     while (i < pend.size()) {
    //         std::cout << pend[i] << ", ";
    //         i++;
    //     }
    // } catch (const std::exception& e) {
    //     std::cerr << "Error." << std::endl;
    // }
}


/* insertion et suppresion dans un vecteur 
myVector.insert(myVector.begin() + 1, 42); // Insertion de la valeur 42 à la position 1
myVector.erase(myVector.begin() + 2);      // Suppression de l'élément à la position 2 
*/