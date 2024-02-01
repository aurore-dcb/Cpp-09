#include "BitcoinExchange.hpp"

void BitcoinExchange::doExchange(char *infile) {

    try {
        BitcoinExchange inst;
        inst.parseData();
        inst.parseInfile(infile);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

bool BitcoinExchange::isdigitRange(std::string date, size_t inf, size_t sup) {
    for (size_t i = inf ; i <= sup ; i++) {
        if (!isdigit(date[i]))
            return false;
    }
    return true;
}

bool BitcoinExchange::dateFormat(std::string date) {

    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    if (!isdigitRange(date, 0, 3) || !isdigitRange(date, 5, 6) || !isdigitRange(date, 8, 9))
        return false;
    if (!validDate(date))
        return false;
    return true;
}

bool BitcoinExchange::doubleDate(std::string date) {

    std::map<std::string, float>::iterator it = _data.begin();
    std::map<std::string, float>::iterator ite = _data.end();
    for (it = _data.begin() ; it != ite ; ++it) {
        if (it->first == date)
            return false;
    }
    if (_data.size() > 0) {
        std::map<std::string, float>::reverse_iterator last = _data.rbegin();
        if (!isMoreRecentDate(date, last->first))
            return false;
    }
    return true;
}

bool BitcoinExchange::parseData( void ) {

    std::ifstream infile("data.csv");
    if (infile) {
        std::string line;
        getline(infile, line);
        if (line != "date,exchange_rate") {
            throw BitcoinExchange::ExceptionDataCorrupted();
        }
        while (getline(infile, line)) {
            if (line.find(',') == std::string::npos) {
                throw BitcoinExchange::ExceptionDataCorrupted();
            }
            std::string date = line.substr(0, line.find(","));
            if (!doubleDate(date))
                 throw BitcoinExchange::ExceptionDataCorrupted();
            std::string value = line.substr(line.find(",") + 1, line.size() - 1);
            std::stringstream ss(value);
            double valueDouble;
            if (!(ss >> valueDouble) || !ss.eof() || !dateFormat(date)) {
                throw BitcoinExchange::ExceptionDataCorrupted();
            }
            _data[date] = valueDouble;
        }
        return true;
    }
    throw BitcoinExchange::ExceptionDataCorrupted();
}

bool BitcoinExchange::valueFormat(std::string value) {

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
    if (pts > 1)
        return false;
    return true;
}

void BitcoinExchange::parseInfile(char *infile) {

    std::ifstream stream(infile);
    if (stream) {
        std::string line;
        getline(stream, line);
        if (line != "date | value") {
            std::cout << "Error: first line of input file must be \033[3mdate | value\033[0m." << std::endl;
            return ;
        }
        while (getline(stream, line)) {
            if (line.find(" | ") == std::string::npos) {
                std::cout << "Error: bad input => " << line << std::endl;
            } else {
                std::string date = line.substr(0, line.find(" | "));
                if (!dateFormat(date))
                    std::cout << "Error: bad input => " << line << std::endl;
                else {
                    std::string value = line.substr(line.find(" | ") + 3, line.size() - line.find(" | ") - 3);
                    if (!valueFormat(value))
                        std::cout << "Error: bad input => " << line << std::endl;
                    else {
                        std::stringstream ss(value);
                        double valueDouble;
                        ss >> valueDouble;
                        if (valueDouble < 0) {
                            std::cout << "Error: not a positive number." << std::endl;
                        } else if (valueDouble > 1000)
                            std::cout << "Error: too large a number." << std::endl;
                        else {
                            searchRate(date, valueDouble);
                        }
                    }
                }
            }
        }
        return;
    }
    throw std::ios_base::failure("Error: Unable to open the file");
}

// true si data est plus recent que input
bool BitcoinExchange::isMoreRecentDate(std::string data, std::string input) {

    int i;
    for (i = 0 ; i < 4 ; i++) {
        if (data[i] > input[i]) {
            return true;
        } else if (data[i] < input[i])
            return false;
    }
    i++;
    for (i = 0 ; i < 7 ; i++) {
        if (data[i] > input[i]) {
            return true;
        } else if (data[i] < input[i])
            return false;
    }
    i++;
    for (i = 0 ; i < 10 ; i++) {
        if (data[i] > input[i]) {
            return true;
        } else if (data[i] < input[i])
            return false;
    }
    return false;
}

void BitcoinExchange::searchRate( std::string date, float value ) {

    std::map<std::string, float>::iterator it = _data.begin();
    std::map<std::string, float>::iterator ite = _data.end();
    std::string tmp;
    tmp = it->first;
    if (isMoreRecentDate(it->first, date)) {
        std::cout << "Error: no exchange rate could be found." << std::endl;
        return;
    }
    for (it = _data.begin(); it != ite ; ++it) {
        if (it->first == date) {
            std::cout << date << " => " << value << " = " << std::fixed << std::setprecision(2) << value * _data[date] << std::endl;
            return;
        } else if (isMoreRecentDate(it->first, date)) {
            std::cout << date << " => " << value << " = " << value * _data[tmp] << std::endl;
            return ;
        }
        tmp = it->first;
    }
    std::cout << date << " => " << value << " = " << value * _data[tmp] << std::endl;
}

bool BitcoinExchange::validDate( std::string date ) {

    std::string month = date.substr(5, 2);
    std::istringstream iss(month);
    int monthValue;

    std::string day = date.substr(8, 2);
    std::istringstream iss2(day);
    int dayValue;

    std::string year = date.substr(0, 4);
    std::istringstream iss3(year);
    int yearValue;

    if (iss >> monthValue && monthValue >= 1 && monthValue <= 12) { 
        if (monthValue == 2) {
            if (iss3 >> yearValue) {
                if ((yearValue % 4 == 0 && yearValue % 100 != 0) || (yearValue % 400 == 0)) { // leap year
                    if (iss2 >> dayValue && dayValue <= 29)
                        return true;
                }
                else {
                    if (iss2 >> dayValue && dayValue <= 28) // no leap year
                        return true;
                }
            }
            return false;
        } else if (monthValue == 1 || monthValue == 3 || monthValue == 5 || monthValue == 7 ||
            monthValue == 8 || monthValue == 10 || monthValue == 12) {
            if (iss2 >> dayValue && dayValue <= 31)
                return true;
            return false;
        } else {
            if (iss2 >> dayValue && dayValue <= 30)
                return true;
            return false;
        }
    }
    return false;
}