#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {

    BitcoinExchange test;
    (void)argv;
    if (argc != 2) {
        std::cout << "Wrong number of arguments !" << std::endl;
        return (1);
    }
    BitcoinExchange inst;
    if (!test.parseData())
        return (1);
    test.parseInfile(argv[1]);
    return (0);
}