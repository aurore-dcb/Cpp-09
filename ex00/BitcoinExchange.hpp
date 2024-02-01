#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <stdexcept>

class BitcoinExchange {

    public:
        BitcoinExchange( void ) {}
        ~BitcoinExchange( void ) {}
        BitcoinExchange( const BitcoinExchange& cpy ) { *this = cpy; }
        BitcoinExchange& operator=(const BitcoinExchange& rhs ) {
            (void)rhs;
            return *this;
        }

        class ExceptionDataCorrupted : public std::exception {
            virtual const char* what() const throw() {
                return "Error: the database is corrupted. It can not be used.";
            }
        };

        static void doExchange( char *infile );

    private:
        bool parseData( void );
        void parseInfile( char *infile );
        void searchRate( std::string date, float value );

        bool doubleDate(std::string date);
        bool validDate( std::string date );
        bool isdigitRange(std::string date, size_t inf, size_t sup);
        bool dateFormat(std::string date);
        bool valueFormat(std::string value);
        bool isMoreRecentDate(std::string data, std::string input);

    private:
        std::map<std::string, float> _data;
};

#endif