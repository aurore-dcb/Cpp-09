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
        // for (std::map<std::string, float>::iterator it = _data.begin() ; it != _data.end() ; ++it) {
        //     std::cout << it->first << "," << std::fixed << std::setprecision(2) << it->second << std::endl;
        // }
        return true;
    }
    infile.close();
    return false;
}

bool isdigitRange(std::string date, size_t inf, size_t sup) {
    for (size_t i = inf ; i <= sup ; i++) {
        if (!isdigit(date[i]))
            return false;
    }
    return true;
}

bool dateFormat(std::string date) {

    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    if (!isdigitRange(date, 0, 3) || !isdigitRange(date, 5, 6) || !isdigitRange(date, 8, 9))
        return false;
    return true;
}

bool valueFormat(std::string value) {

    int pts = 0;
    size_t i = 0;
    while (i < value.size()) {
        if (i == 0 && (value[i] == '+' || value[i] == '-'))
            i++;
        if (value[i] == '.') {
            pts++;
            i++;
        } else if (isdigit(value[i])) {
            i++;
        } else
            return false;
    }
    return true;
}

bool BitcoinExchange::parseInfile(char *infile) {

    std::ifstream stream(infile);
    if (stream) {
        std::string line;
        getline(stream, line);
        if (line != "date | value") { // check first line of data file
            stream.close();
            return false;
        }
        while (getline(stream, line)) {
            if (line.find(" | ") == std::string::npos) {
                std::cerr << "Error: bad input => " << line << std::endl;
            } else {
                std::string date = line.substr(0, line.find(" | "));
                if (!dateFormat(date))
                    std::cerr << "Error: bad input => " << line << std::endl;
                else {
                    std::string value = line.substr(line.find(" | ") + 3, line.size() - 1);
                    if (!valueFormat(value))
                        std::cerr << "Error: bad input => " << line << std::endl;
                    else {
                        std::stringstream ss(value);
                        double valueDouble;
                        ss >> valueDouble;
                        if (valueDouble < 0) {
                            std::cerr << "Error: not a positive number." << std::endl;
                        } else if (valueDouble > 100)
                            std::cerr << "Error: too large a number." << std::endl;
                        else {
                            std::cout << date << " | " << std::fixed << std::setprecision(2) << value << std::endl;
                        }
                    }
                }
            }
            // chercher la date la plus proche dans le _data et affichier le resultat
        }
        // for (std::map<std::string, float>::iterator it = _input.begin() ; it != _input.end() ; ++it) {
        //     std::cout << it->first << " | " << it->second << std::endl;
        // }
        return true;
    }
    return false;
}