#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <algorithm>
#include <map>
#include <iostream>
#include <fstream>

class BitcoinExchange {

    public:
        BitcoinExchange( void ) {}
        ~BitcoinExchange( void ) {}
        BitcoinExchange( const BitcoinExchange& cpy ) { *this = cpy; }
        BitcoinExchange& operator=(const BitcoinExchange& rhs ) {
            (void)rhs;
            return *this;
        }

        bool parseData( void );

    private:
        std::map<std::string, float> _data;
        std::map<std::string, float> _input;
};

#endif