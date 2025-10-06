#pragma once

#include <iostream>
#include <sstream> // library that allows concatenation, insertion and extration from strings. (it allows big performance from std::strings)
#include <ostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <stdint.h>
#include <stack>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m" 
#define BLUE  "\033[34m"
#define END  "\033[0m"
#define OLIVE "\033[38;5;3m"
#define PURPLE "\033[38;5;5m"
#define ORANGE "\033[38;5;208m"


class RPN
{
private:
    std::stack<int> c;
    std::string str;
public:
    RPN(std::string string);
    int check_input(std::string str);
    void execute_RPN();

    void calculate(char chr);
    void sum_operator();
    void res_operator();
    void mult_operator();
    void div_operator();
    ~RPN();
};


int RPN::check_input(std::string str)
{
    std::string operators = "*+-/";
 
    for (int i = 0; i <  str.length() ; i++)
    {
        if (str[i] == ' ')
            continue;
        else  if (operators.find(str[i]) == std::string::npos && !isdigit(str[i]))
            return 0;
    }
    return 1;
}

RPN::RPN(std::string _str) : str(_str)
{
    std::cout << "RPN constructor called!" << std::endl;

    if (!check_input(str))
    {
        std::cout << "invalid str for RPN" << std::endl;
        return ;
    }
    execute_RPN();
}

void RPN::sum_operator()
{
    int x,y, result;

    x = c.top();
    c.pop();
    y = c.top();
    c.pop();
    result = y + x;
    c.push(result);
}

void RPN::res_operator()
{
    int x,y, result;

    x = c.top();
    c.pop();
    y = c.top();
    c.pop();
    result = y - x;
    c.push(result);
}

void RPN::mult_operator()
{
    int x,y, result;

    x = c.top();
    c.pop();
    y = c.top();
    c.pop();
    result = y * x;
    c.push(result);
}

void RPN::div_operator()
{
    int x,y, result;

    x = c.top();
    c.pop();
    y = c.top();
    c.pop();
    result = y / x;
    c.push(result);
}

void RPN::calculate(char op)
{
    std::cout << "op:" << op << std::endl;
    switch (op)
    {
    case '+':
        sum_operator();
        break;
    case '-':
        res_operator();
        break;
    case '*':
        mult_operator();
        break;
    case '/':
        div_operator();
        break;
    default:
        std::cerr << "error:" << std::endl;
        break;
    }
    std::cout << "on top rn: " << c.top() << std::endl;
}

void RPN::execute_RPN(){
    std::cout << "------------------\n";

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ')
            continue;
        else if (isdigit(str[i]))
        {
            int nbr = str[i] - '0';
            std::cout << nbr <<  std::endl;
            c.push(nbr);
        }
        else
            calculate(str[i]);
        std::cout << "------------------\n";
    }
    std::cout << "result: " << c.top() << std::endl;
}   



RPN::~RPN()
{
    std::cout << "RPN destructor called!" << std::endl;
}
