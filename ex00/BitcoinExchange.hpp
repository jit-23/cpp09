    #pragma once

#include <string>
#include <string.h>
#include <cstring>
#include <cctype>
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
    std::map< std::string, double> mapp;
    std::string file_name;
    std::ifstream read_f;

    std::string yr;
    std::string mth;
    std::string dy;

    int limit_year;
    int limit_month;
    int limit_day;

    int quantity_in_outlet;

    
public:
    BitcoinExchange(); // default will fill the database with the data.cvs info
    void analise_doc(std::string file_name); // will verify and read input.txt
    void check_doc(/* std::ifstream read_f */);
    void print_table(std::string date,double * quantity_nbr);
    int check_date_veracity(int y, int m,int d);

    void get_limit_date();
    int parse_date(std::string date/* ,std::string val */);
    int parse_value(std::string raw_val, double *value_nbr);
    //BitcoinExchange(std::string _file_name);
    BitcoinExchange(const BitcoinExchange &other);

    ~BitcoinExchange();
};


void BitcoinExchange::get_limit_date()
{
    time_t now = time(0);

    tm *current_time = localtime(&now);
    limit_year = 1900 + current_time->tm_year; 
    limit_month = 1 + current_time->tm_mon; 
    limit_day =  current_time->tm_mday;
}



int BitcoinExchange::check_date_veracity(int y, int m,int d)
{ // 0 if not valid
    if (y < 0 || y > limit_year)
        return 0;
    if (m <= 0 || m > 12)
        return 0;
    if (d < 1)
        return 0;
    switch (m)
    {
    case 1:
    {
        if (d > 31)
            return 0;
        break;
    }
    case 2:
    {
        if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) // leap year
        {
            if (d > 29)
                return 0;
        }
        else //(dayd > 31)
            if (d > 28)
                return 0;
        break;
    }
    case 3:
    {
        if (d > 31)
            return 0;
        break;
    }
    case 4: // april
    {
        if (d > 30)
            return 0;
        break;
    }
    case 5: // may
    {
        if (d > 31)
            return 0;
        break;
    }
    case 6: // june
    {
        if (d > 30)
            return 0;
        break;
    }
    case 7: // july
    {
        if (d > 31)
            return 0;
        break;
    }
    case 8: // august
    {
        if (d > 31)
            return 0;
        break;
    }
    case 9: // september
    {
        if (d > 30)
            return 0;
        break;
    }
    case 10: // october
    {
        if (d > 31)
            return 0;
        break;
    }
    case 11: // november
    {
        if (d > 30)
            return 0;
        break;
    }
    case 12: // december
    {
        if (d > 31)
            return 0;
        break;
    }
    default:
        return 0;
    }
    return 1;
}

int BitcoinExchange::parse_date(std::string date /* , std::string quantity */)
{
    std::string year; 
    std::string month; 
    std::string day;
    
    int flag = 0;
    for (int i = 0; i < date.size(); i++)
    {

        if (date[i] == '-' && flag == 0)
        {
            year = date.substr(0, i);
            flag++;
        }
        if(date[i] == '-' && flag == 1)
        {
            
            if (i < date.size())
            {
                int j = i;
                while(j > date.size() && date[j] != '-')
                    j++;
                j--;
                month = date.substr(i + 1, j - 1);
            flag++;
            }
        }
        if (date[i] == '-' && flag == 2)
        {
            day = date.substr(i + 1, date.size());
        }
    }
    // todo : check date is valid date

    if (!check_date_veracity(atoi(year.c_str()), atoi(month.c_str()), atoi(day.c_str())))
        return 0; // not valid
    return 1;
}
/* 
    TODO
    DATE => QUANTITY = VALUE IN OUTLET
*/
void BitcoinExchange::print_table(std::string date,double * quantity_nbr)
{
    // TODO loop throught mapp to get the most close date ;
    
    //std::string target;
//    double quantity_nbr = std::atof(quantity_str.c_str());
 //   std::stringstream buffer(quantity_str);
  //  buffer >> quantity_nbr;
   // if (buffer.fail())
   //std::cout << "quantity_nbr : ." << *quantity_nbr << "." << std::endl;
   double quantity_of_btc = *quantity_nbr;
    //    throw std::runtime_error("convertion on quantity var failed");
    for(std::map<std::string, double>::iterator it = mapp.begin(); it != mapp.end(); it++ )
    {
        if (date > it->first)
            continue;
        else
        {
            std::cout << date << " => " << quantity_of_btc << " = " << it->second * (quantity_of_btc) << std::endl; 
            break;
        }
    }
//    for(std::map<std::string, double>::iterator it = mapp.begin(); it != mapp.end(); it++ )
//    {
//        if (date == it->first)
//        {
//            std::cout << "(INPUT.TXT) value of bitcoin in this year: "<< date << " | quantity: " << quantity << std::endl; 
//            std::cout << "(data.cvs)value of bitcoin in this year  : "<< it->first << " | value: " << it->second << std::endl; 
//
            // ? date = it->first
            // ? quantity = this->quantity
            // ? value = it->second
            // ? quantity in outlet = quantity * value
//        }
//    }
}

int BitcoinExchange::parse_value(std::string raw_val, double *value_nbr)
{
    //double double_buffer;
    //value_nbr = &double_buffer; 
    //std::cout << "parse_value" << std::endl;
    double i = 0;
    while(raw_val[i] && !isdigit(raw_val[i]))
        i++;
    raw_val = raw_val.substr(i, raw_val.size());
   // std::cout << "raw_val str: ." << raw_val << "." <<  std::endl;
    for (int i = 0; i < raw_val.size(); i++)
    {
        if (!isdigit(raw_val[i]))
            return 0;
    }
    std::stringstream buffer(raw_val);
    if (buffer.fail())
    {
        return 0;
    }
    buffer >> *value_nbr;
    //std::cout << "value_nbr: " << *value_nbr << std::endl;
    
    return 1;
}
void BitcoinExchange::check_doc()
{
    std::string buffer;
    std::string raw_val = "0";
    double bf;
    double *parsed_val = &bf;
    while(std::getline(this->read_f, buffer))
    {
        int i = 0;
        while(buffer[i] && buffer[i] == ' ')
            i++;
            if (buffer[i] == '\n')
            continue;
            else
            {
                int j = i;
                while(buffer[j] && (isdigit(buffer[j]) || buffer[j] == '-'))
                j++;
                std::string date = buffer.substr(i, j);
                if (buffer.find('|') != std::string::npos && (buffer.size() - j >= 2))
                {
                    raw_val = buffer.substr(j, buffer.size());
            }

            if (!parse_date(date/* , val */) || !parse_value(raw_val, parsed_val))
                std::cout << "non valid" << std::endl;
            else
            {
                //std::cout << "parsed_val:" << *parsed_val <<  std::endl;
                //std::cout << "bf:" << bf <<  std::endl;
                print_table(date, parsed_val);
            }
            }
        }               
    
}

void BitcoinExchange::analise_doc(std::string file_name)
{
    read_f.open(file_name.c_str());
    if (!read_f.is_open())  
    {
        throw  std::runtime_error("open function failed!"); 
    }
    std::string f_line;
    std::getline(read_f, f_line);
    int i = 0;
    while (f_line[i] && std::isspace(f_line[i]))
        i++;
    f_line = f_line.substr(i, f_line.size());
    i = f_line.length() - 1 ;
    while (i >= 0 && std::isspace(f_line[i]))
    {
        std::cout << i;
        i--;
    }
    i++;
    f_line = f_line.substr(0, i);
    if (f_line.substr(0, 4) == "date")
    {
        f_line = f_line.substr(4, f_line.size());
        int i = 0;
        while(f_line[i] && std::isspace(f_line[i]))
            i++;
        if (f_line[i] != '|')
        {
            std::cout << RED << "ERROR(NOT PIPE): " << END <<  std::endl;
            return ;
        }
        i++;
        while(f_line[i] && std::isspace(f_line[i]))
            i++;
        f_line = f_line.substr(i, f_line.size());
        if (f_line != "value")
        {
            std::cout << RED << "ERROR(VALUE): " << END <<  std::endl;
            return ;
        }
        std::cout << "valid!\n";
        check_doc(/* read_f */);
    }
}

#include <iomanip>
BitcoinExchange::BitcoinExchange() 
{
    std::string buffer;
    std::cout << GREEN << "BitcoinExchange Constructor called!" <<END<<  std::endl;

    std::ifstream read_f;
    read_f.open("data.csv");
    if (!read_f.is_open())  
    {
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
    for (std::map<std::string, double>::iterator it = this->mapp.begin(); it != mapp.end() ; it++)
    {
        std::cout << RED<< std::setprecision(17) << it->second <<END<< std::endl;
    }
    
    get_limit_date();
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
