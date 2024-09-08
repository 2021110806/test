#ifndef RPN_HPP
#define RPN_HPP
#include <iostream>
#include <stack>
class RPN
{
    private:
        std::stack<int> numbers;
		bool isOperator(char s);
		int calculate(int num1, char op, int num2);
		bool isWhiteSpace(char s);
    public:
        RPN();
        RPN(std::stack<int> num);
        RPN(const RPN &other);
        ~RPN();
        RPN &operator=(const RPN &other);
        void play(std::string input);
};

#endif