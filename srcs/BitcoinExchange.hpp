#pragma once

#include <iostream>
#include <cstring>
#include <map>
#include <isstream>
#include <unistd.h>
#include <cstdio>
#include <fstream>

 class BitcoinExchange
{
private:
    std::map<int, std::string> mapp;
    int fd_file;
    std::string file_name;
public:
    BitcoinExchange(std::string _file_name);
    ~BitcoinExchange();
};



BitcoinExchange::BitcoinExchange(std::string file_name)  
{
    //std::iss
    //fd_file = open(file_name, O_RDWR);
    //if (fd_file < 0)
    //    perror("lol");
    std::string buffer;

    std::ifstream read_f(file_name);

    while(std::getline(read_f, buffer))
    {
        int i = 0;
        while(buffer[i] && std::isspace(buffer[i]))
            i++;
        map
        }
    int i = 0;
    while(buffer[i] && std::isspace(buffer[i]))
        i++

}

BitcoinExchange::~BitcoinExchange()
{
}
