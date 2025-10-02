#include <iostream>
#include "BitcoinExchange.hpp"

int main(int argc, char  *av[])
{
    try
    {
        BitcoinExchange(std::string(av[1]));
    }
    catch(const std::exception& e)
    {  
        std::cout << e.what() << std::endl;

    }
    return 0;
}
