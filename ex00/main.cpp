#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {

    BitcoinExchange test;
    (void)argv;
    if (argc != 2) {
        std::cout << "Wrong number of arguments !" << std::endl;
        return (1);
    }
    BitcoinExchange inst;
    std::cout << std::boolalpha << test.parseData() << std::endl;
    std::cout << std::boolalpha << test.parseInfile(argv[1]) << std::endl;

    return (0);
}