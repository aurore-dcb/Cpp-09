#ifndef RPN_HPP
# define RPN_HPP

#include <algorithm>
#include <stack>
#include <iostream>

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

        static void doOperations(std::string input);

        int addition(int n1, int n2) const { return n1 + n2; }
        int subtraction(int n1, int n2) const { return n1 - n2; }
        int multiplication(int n1, int n2) const { return n1 * n2; }
        int division(int n1, int n2) const { 
            if (n1 == 0 || n2 == 0)
                return 0;
            return n1 / n2;
        }       


    private:
        void parsing(std::string input);
        void resolve(std::string input);

    private:
        typedef int (RPN::*f)( int n1, int n2 ) const;
        f fct_ptr[4];
        std::stack<int> _s;
};

#endif