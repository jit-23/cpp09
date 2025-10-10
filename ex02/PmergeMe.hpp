#pragma once
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <cctype>
#include <sstream>
#include <vector>
#include <deque>
#include <list>
#include <utility>
#include <sys/time.h> 


class PmergeMe
{
    private:
        int vt_size;
        std::vector<int> raw_vt;
        std::vector<int> sorted_vt;
        std::vector<std::pair<int, int> >pair_vt;
        
        timeval start;
        timeval end;

        timeval vt_start;
        timeval vt_end;
        timeval lst_time;

        int lst_size;
        std::list<int> raw_lst;
        std::list<int> sorted_lst;
        std::list<std::pair<int, int> >pair_lst;
    public:
        typedef std::vector<std::pair<int, int> > vector_pair; 
        typedef std::vector<int> vtr; 

        typedef std::list<std::pair<int, int> > list_pair; 
        typedef std::list<int> lst; 
        
        PmergeMe(std::string str);
        
        vtr extract_larger_number(vector_pair target);
        lst extract_larger_number(list_pair target);
        
        vtr extract_smaller_number(vector_pair target);
        lst extract_smaller_number(list_pair target);
        
        vtr split(const std::string &str, vtr ret);
        lst split(const std::string &str, lst ret);
        
        void fill_vt( std::string str);
        void fill_lst( std::string str);
        
        void display_info();

        vtr merge_insertion(vtr vt);
        lst merge_insertion(lst vt);
        
        // for list only//
        void push_element(PmergeMe::lst list, int index);
        // for list only//
        
        int get_vt_size()const ;
        int get_lst_size()const ;
        
        ~PmergeMe();
};
