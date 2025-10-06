#pragma once
#include <string>
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <sstream>
#include <vector>
#include <deque>
#include <utility>

class PmergeMe
{
    private:
        std::vector<std::pair<int, int> >pair_vt;
        int size;
        std::vector<int> raw_vt;
    public:
        std::vector<int> split(const std::string &str);
        void fill_vt( std::string str);
        PmergeMe(std::string str);
        ~PmergeMe();
};


std::vector<int> PmergeMe::split(const std::string &str)
{
	std::vector<int> token_vector;
	std::string 		 token;
	std::istringstream 	 iss(str);

	while(iss >> token)
		token_vector.push_back(atoi(token.c_str()));
	return token_vector;
}

void PmergeMe::fill_vt(std::string str)
{
    this->raw_vt = split(str);
    int x;
    int y;
    std::cout << raw_vt.size();
    exit(1);// wtf
    for (std::vector<int>::iterator it = raw_vt.begin(); it != raw_vt.end(); it++)
    {
        std::cout << "1\n";
        if (++it != raw_vt.end())
        {
            y = *it;
            --it;
            x = *it;
            pair_vt.push_back(std::make_pair(x,y));
        }
    }
    
    
}
PmergeMe::PmergeMe(std::string str)
{
    if (str.empty())
        throw std::runtime_error("empty string");
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ' && !isdigit(str[i]))
            throw std::runtime_error("non valid str");
    }
    fill_vt(str);
}

PmergeMe::~PmergeMe()
{
}
