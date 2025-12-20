#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    std::string a = "3 2 1 4 6 5 8 7";
    std::string b = "5 7 3 1 8 2 6 4";
    std::string b1 = "8 2 6 4 5 7 3 1 81 21 61 41 51 71 31 11";
    std::string b2 = "81 21 61 41 51 71 31 11 8 2 6 4 5 7 3 1";
    std::string c = "3 2 1 4 6 5 8 7";
    PmergeMe merge(b2/* av[1] */);
    
    return 0;
}
