#ifndef RPN_HPP
# define RPN_HPP

#include <algorithm>
#include <stack>
#include <iostream>
#include <limits>
#include <cctype>

class RPN {

    public:
        RPN( void ) {
            fct_ptr[0] = &RPN::addition;
            fct_ptr[1] = &RPN::subtraction;
            fct_ptr[2] = &RPN::multiplication;
            fct_ptr[3] = &RPN::division;
        }
        ~RPN( void ) {} 
        RPN( const RPN& cpy ) { *this = cpy; }
        RPN& operator=( const RPN& rhs ) {
            (void)rhs;
            return *this;
        }

        class ExceptionCharNotAuth : public std::exception {
            virtual const char* what() const throw() {
                return "Error: use of an unauthorized character";
            }
        };

        class ExceptionWrongFormat : public std::exception {
            virtual const char* what() const throw() {
                return "Error: wrong format";
            }
        };

        class ExceptionErrorExpression : public std::exception {
            virtual const char* what() const throw() {
                return "Error: there is an error in the expression";
            }
        };

        class ExceptionDivisionbyZero : public std::exception {
            virtual const char* what() const throw() {
                return "Error: division by 0 is impossible";
            }
        };

        static void doOperations(std::string input);
        bool isOperator(char c) const;
        bool isWhitespace(const std::string& str) const;

        long addition(int n1, int n2) const {
            return n1 + n2; 
        }
        long subtraction(int n1, int n2) const {
            return n1 - n2;
        }
        long multiplication(int n1, int n2) const {
            return n1 * n2;
        }
        long division(int n1, int n2) const {
            if (n2 == 0) {
                throw ExceptionDivisionbyZero();
            }
            return n1 / n2;
        }       


    private:
        void parsing(std::string input);
        void resolve(std::string input);

    private:
        typedef long (RPN::*f)( int n1, int n2 ) const;
        f fct_ptr[4];
        std::stack<int> _s;
};

#endif