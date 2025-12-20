#pragma once 

#include <list>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
/*value - "3 2 1 4 5 6 8 7" */
/*index -  0 1 2 3 4 5 6 7*/
/* 5 7 3 1 8 2 6 4 */



class PmergeMe
{
private:
    std::vector<int> vt;
    std::vector<int> og_vt;
public:
    typedef std::vector<std::pair<int, int> > vector_pair; 
    typedef std::vector<int>::iterator vtr_it; 
    typedef std::vector<int> vtr; 

    PmergeMe(std::string str_vt);
    vtr split(const std::string &str, vtr token_vector);
    void fill_vt(std::string str);
    void pv(PmergeMe::vtr a);
    void merge_insert(vtr &vetor, int cel_size);
    
    ~PmergeMe();
};
