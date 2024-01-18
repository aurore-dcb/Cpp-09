#include "BitcoinExchange.hpp"
#include <string>
#include <cstdlib>
#include <iomanip>
#include <sstream>

bool BitcoinExchange::parseData( void ) {

    std::ifstream infile("data.csv");
    if (infile) {
        std::string line;
        getline(infile, line);
        if (line != "date,exchange_rate") { // check first line of data file
            infile.close();
            return false;
        }
        while (getline(infile, line)) {
            if (line.find(',') == std::string::npos) {
                std::cerr << "Error: wrong format. Format must be \033[3mdate,exchange_rate\033[0m" << std::endl;
                return false;
            }
            std::string date = line.substr(0, line.find(","));
            std::string value = line.substr(line.find(",") + 1, line.size() - 1);
            std::stringstream ss(value);
            double valueDouble;
            ss >> valueDouble;
            _data[date] = valueDouble; // add new elem in data std::map
        }
        for (std::map<std::string, float>::iterator it = _data.begin() ; it != _data.end() ; ++it) {
            std::cout << it->first << "," << std::fixed << std::setprecision(2) << it->second << std::endl;
        }
        return true;
    }
    infile.close();
    return false;
}