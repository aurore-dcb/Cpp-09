#include "RPN.hpp"
#include <cctype>

void RPN::doOperations(std::string input) {
    
    try {
        RPN ope;
        ope.parsing(input);
        ope.resolve(input);
        std::cout << "resultat: " << ope._s.top() << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool isWhitespace(const std::string& str) {

    for (std::string::const_iterator it = str.begin() ; it != str.end() ; ++it) {
        if (!std::isspace(static_cast<unsigned char>(*it)))
            return false;
    }
    return true;
}

void afficherStack(const std::stack<int>& maPile) {
    std::stack<int> pileTemporaire = maPile;

    std::cout << "Contenu de la pile : ";

    while (!pileTemporaire.empty()) {
        std::cout << pileTemporaire.top() << " ";
        pileTemporaire.pop();
    }

    std::cout << std::endl;
}

void RPN::resolve(std::string input) {

    char tab[4] = {'+', '-', '*', '/'};
    int res = 0;
    for (size_t i = 0 ; i < input.size() ; i++) {
        if (isdigit(input[i])) {
            _s.push(input[i] - '0');
        }
        else if (isOperator(input[i])) {
            int n2 = _s.top();
            _s.pop();
            int n1 = _s.top();
            _s.pop();
            for (int j = 0 ; j < 4 ; j++) {
                if (tab[j] == input[i]) {
                    res = (this->*fct_ptr[j])(n1, n2);
                    _s.push(res);
                }
            }
        }
    }
    // afficherStack(_s);
}

void RPN::parsing(std::string input) {

    if (input.empty() || isWhitespace(input))
        std::cout << "Error: input is empty" << std::endl;
    for (size_t i = 0 ; i < input.size() ; i++) {
        if (!isdigit(input[i]) && !isOperator(input[i]) && input[i] != ' ')
            throw ExceptionCharNotAuth();
        else if ((i == input.size() - 1 && !isOperator(input[i])) || (i == 0 && !isdigit(input[i])))
            throw ExceptionWrongFormat();
        else if (isdigit(input[i]) || isOperator(input[i])) {
            if (i == 0 && !isdigit(input[i]))
                throw ExceptionWrongFormat();
            else if (i == input.size() - 1 && !isOperator(input[i]))
                throw ExceptionWrongFormat();
            else if (i > 0 && i < input.size() - 1) {
                if (input[i - 1] != ' ' || input[i + 1] != ' ')
                    throw ExceptionWrongFormat();
            }
        } else if (input[i] == ' ' && (input[i + 1] == ' ' || input[i - 1] == ' '))
            throw ExceptionWrongFormat();
    }
}