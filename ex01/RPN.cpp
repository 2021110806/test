#include "RPN.hpp"

RPN::RPN()
{
    std::cout << "default constructro called" << std::endl;
}

RPN::RPN(std::stack<int> numbers)
{
    std::cout << "stack constructor called" << std::endl;
    this -> numbers = numbers;
}

RPN::RPN(const RPN &other)
{
    std::cout << "copy constructor called" << std::endl;
    this -> numbers = other.numbers;
}

RPN::~RPN()
{
    std::cout << "destructor called" << std::endl;
}

RPN &RPN::operator=(const RPN &other)
{
    std::cout << "copy assigned operator called" << std::endl;
    if (this == &other) {
        return *this;
    }
    this -> numbers = other.numbers;
    return *this;
}

bool RPN::isOperator(char s)
{
    if (s == '+' || s == '-' || s == '*' || s == '/')
        return true;
    return false;
}

int RPN::calculate(int num1, char op, int num2)
{
    if (op == '+')
        return num1 + num2;
    if (op == '-')
        return num1 - num2;
    if (op == '*')
        return num1 * num2;
    if (op == '/')
        return num1 / num2;
    return 0;

}

bool RPN::isWhiteSpace(char s)
{
    if (s== ' ' || s == '\t')
        return true;
    return false;
}

void RPN::play(std::string input)
{
    for (size_t i = 0; i < input.size(); i++)
    {
        if (isWhiteSpace(input[i]))
            continue;
        else if (numbers.size() >= 2 && isOperator(input[i]))
        {   
            int num1 = numbers.top();
            numbers.pop();
            int num2 = numbers.top();
            numbers.pop();
            numbers.push(calculate(num2, input[i], num1));
        }
        else if (std::isdigit(input[i]))
        {
            numbers.push(input[i] - '0');
        }
		else
		{
			std::cout << "[ERROR] Invalid elements" << std::endl;
		}
    }
	if (numbers.size() == 1)
	{
		std::cout << "Result : " << numbers.top() << std::endl;
	}
	else
	{
		std::cout << "[ERROR] Invalid form" << std::endl;
	}
}