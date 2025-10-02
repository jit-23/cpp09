    #pragma once

#include <string>
#include <string.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <iterator>
#include <sstream>
#include <cerrno>     // For errno
#include <map>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m" 
#define BLUE  "\033[34m"
#define OLIVE "\033[38;5;3m"
#define PURPLE "\033[38;5;5m"
#define ORANGE "\033[38;5;208m"
#define CYAN "\033[38;5;6m"
#define LIGHT_GRAY "\033[38;5;7m"
#define DARK_GRAY "\033[38;5;8m"
#define END  "\033[0m"

 class BitcoinExchange
{
private:
    std::map< std::string, float> mapp;
    std::string file_name;
public:
    BitcoinExchange(std::string _file_name);
    BitcoinExchange(const BitcoinExchange &other);

    ~BitcoinExchange();
};



BitcoinExchange::BitcoinExchange(std::string _file_name) :file_name(_file_name)  
{
    std::string buffer;

    std::ifstream read_f;
    read_f.open(file_name.c_str());
    if (!read_f.is_open())  
    {
        /* std::cout  */
        throw  std::runtime_error("open function failed!"); 
    }
    std::string date;
    std::string value;
    while(std::getline(read_f, buffer))
    {
        int i = 0;
        while(buffer[i] && buffer[i] != ',')
            i++;
        date = buffer.substr(0, i);
        value = buffer.substr(i + 1, buffer.size());
        mapp[date] = atof(value.c_str());
    }
    //for(std::map<std::string, float>::iterator it = mapp.begin(); it != mapp.end(); it++ )
    //    std::cout << it->first << " | " << it->second << std::endl;
    
}


BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    std::cout << GREEN << "BitcoinExchange Copy Constructor called!" <<END<<  std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
    std::cout << RED << "BitcoinExchange Destructor called!" <<END<<  std::endl;

}
