#include "PmergeMe.hpp"

int main(int ac, char  *av[])
{
    try
    {
        std::string a = "6 5 2 3 4 1";
        PmergeMe merge(a);
    
        //PmergeMe merge(av[1]);

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
