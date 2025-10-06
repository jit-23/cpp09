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
#include <ctime>
#include <unistd.h>
void PmergeMe::fill_vt(std::string str)
{
    this->raw_vt = split(str);
    int x;
    int y;
    //std::cout << raw_vt.size();
    //exit(1);// wtf
    std::cout << "" << std::endl;
    std::vector<int>::iterator it = raw_vt.begin();
    std::cout << "it :" << *it << std::endl;
    for (std::vector<int>::iterator it = raw_vt.begin(); it != raw_vt.end(); it++)
    {
        //std::cout << "it : " << *it << std::endl;
        //std::cout << "1\n";
        if (it + 1 != raw_vt.end())
        {
            it++;
            y = *it;
            --it;
            x = *it;
            it++;
            pair_vt.push_back(std::make_pair(x,y));
        }
    }

    for (std::vector<std::pair<int,int> >::iterator it = pair_vt.begin();  it != pair_vt.end(); it++)
    {
        std::cout  << "("<< it->first << "), "<<  " ("<< it->second << ")"<<  std::endl;
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
