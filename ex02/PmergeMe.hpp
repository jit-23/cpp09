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
#include <cstdio>


#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m" 
#define BLUE  "\033[34m"
#define END  "\033[0m"
#define OLIVE "\033[38;5;3m"
#define PURPLE "\033[38;5;5m"
#define ORANGE "\033[38;5;208m"

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


        void display_vt_info();
        void display_lst_info();

        vtr merge_insertion(vtr vt);
        lst merge_insertion(lst vt);
        
        // for list only//
        lst push_element(PmergeMe::lst list, int index);
        // for list only//
        
        int get_vt_size()const ;
        int get_lst_size()const ;
        
        ~PmergeMe();
};
