#include <iostream>
#include "BitcoinExchange.hpp"

int main(int argc, char  *av[])
{
    try
    {
        BitcoinExchange btc;
        btc.analise_doc("input.txt");
    }
    catch(const std::exception& e)
    {  
        std::cout << e.what() << std::endl;

    }
    return 0;
}
