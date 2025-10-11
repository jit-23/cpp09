#include "PmergeMe.hpp"

PmergeMe::vtr PmergeMe::split(const std::string &str, PmergeMe::vtr token_vector)
{
	std::string 		 token;
	std::istringstream 	 iss(str);

	while(iss >> token)
		token_vector.push_back(atoi(token.c_str()));
	return token_vector;
}

PmergeMe::lst PmergeMe::split(const std::string &str, PmergeMe::lst token_vector)
{
	std::string 		 token;
	std::istringstream 	 iss(str);

	while(iss >> token)
		token_vector.push_back(atoi(token.c_str()));
	return token_vector;
}
/*  */

void PmergeMe::fill_vt(std::string str) {
    PmergeMe::vtr tk_vt;
    this->raw_vt = split(str, tk_vt);
}

static void print_list(std::list<int> x)
{
    for (std::list<int>::iterator it = x.begin(); it != x.end(); it++)
    {
        std::cout << "print_list : " << *it << std::endl;
    }
    std::cout << "\n";
}


static void print_listpair(std::list<std::pair<int, int> >x)
{
    for (std::list<std::pair<int, int> >::iterator it = x.begin(); it != x.end(); it++)
    {
        std::cout << "print_listpair : " << it->first <<  ", " << it->second  << std::endl;
    }
    std::cout << "\n";
}


void PmergeMe::fill_lst(std::string str) {
    PmergeMe::lst tk_lst;
    this->raw_lst = split(str, tk_lst);
    printf(RED);
    printf("im in fill_lst\n");
    printf(END);
    
    

}

/*  */
PmergeMe::vtr PmergeMe::extract_larger_number(std::vector<std::pair< int, int> > target)
{
    PmergeMe::vtr x;
    for (vector_pair::iterator it = target.begin() ; it != target.end(); it++)
    {
        x.push_back(it->second);
    }
    return x;
}

PmergeMe::lst PmergeMe::extract_larger_number(PmergeMe::list_pair target)
{
    PmergeMe::lst x;
    for (PmergeMe::list_pair::iterator it = target.begin() ; it != target.end(); it++)
    {
        x.push_back(it->second);
    }
    return x;
}

/*  */

PmergeMe::vtr PmergeMe::extract_smaller_number(PmergeMe::vector_pair target)
{
    PmergeMe::vtr x;
    for (vector_pair::iterator it = target.begin() ; it != target.end(); it++)
    {
        x.push_back(it->first);
    }
    return x;
}

PmergeMe::lst PmergeMe::extract_smaller_number(PmergeMe::list_pair target)
{
    PmergeMe::lst x;
    for (PmergeMe::list_pair::iterator it = target.begin() ; it != target.end(); it++)
    {
        x.push_back(it->first);
    }
    return x;
}
/*  */


PmergeMe::vtr insert_nbr(PmergeMe::vtr vt, int  to_insert){
    int max = vt.size() - 1;
    int pos;
    int min = pos = 0;
    while(min <= max){
        pos = (min + max) / 2;
        if (to_insert == vt[pos])
        {
            vt.insert(vt.begin() + pos, to_insert);
            return (vt);    
        }
        else if (to_insert < vt[pos])
            max = pos - 1;
        else
            min = pos + 1;
    }    
    vt.insert(vt.begin() + min, to_insert);
    return vt;
}

PmergeMe::lst insert_nbr(PmergeMe::lst lt, int  to_insert){
    int max = lt.size() - 1;
    int pos;
    int min = pos = 0;
    PmergeMe::lst::iterator it = lt.begin();
    while(min <= max){
        pos = (min + max) / 2;
        it = lt.begin();
        std::advance(it, pos);
        if (to_insert == (int)*it)
        {
            lt.insert(it, to_insert);
            return (lt);    
        }
        else if (to_insert < *it)
        {
            std::cout << "to_insert: "  << to_insert << std::endl;
            
            max = pos - 1;
        }
        else
        {
            min = pos + 1;
        }
    }
    it  = lt.begin();
    std::advance(it, min);

    lt.insert(it, to_insert );
    return lt;
}


int PmergeMe::get_vt_size()const {  return raw_vt.size();}
int PmergeMe::get_lst_size()const {  return raw_lst.size();}

PmergeMe::vtr PmergeMe::merge_insertion(PmergeMe::vtr vt)
{
    if (vt.size() <= 1) {return vt;}
    PmergeMe::vtr leftover;
    vector_pair pairs;
    for (PmergeMe::vtr::iterator it = vt.begin(); it != vt.end()/*  - 1 */ ; it+=2)
    {
        if (!(it + 1 == vt.end()))
        {
            if (*it > *(it + 1))
                pairs.push_back(std::make_pair(*(it + 1), *it));
            else
                pairs.push_back(std::make_pair(*it, *(it + 1)));
        }
        else
            break;
    }
    if (vt.size() % 2 == 1)
        leftover.push_back(vt[vt.size() - 1]);
    PmergeMe::vtr larger_nbr = extract_larger_number(pairs);
    PmergeMe::vtr smaller_nbr = extract_smaller_number(pairs);
    PmergeMe::vtr sorted = merge_insertion(larger_nbr);
    for (int i = 0; i < smaller_nbr.size(); i++)
        sorted = insert_nbr(sorted, smaller_nbr[i]);
    for (int i = 0; i < leftover.size(); i++)
        sorted = insert_nbr(sorted, leftover[i]);
    return sorted;
}

PmergeMe::lst PmergeMe::merge_insertion(PmergeMe::lst lst)
{
    if (lst.size() <= 1) {return lst;}
    PmergeMe::lst leftover;
    list_pair pairs;
//    print_list(lst);

    for (PmergeMe::lst::iterator it = lst.begin(); it != lst.end() ;)
    {
        PmergeMe::lst::iterator next = it;
        next++;
        if (!(next == lst.end()))
        {
            if (*it > *(next))
                pairs.push_back(std::make_pair(*next, *it));
            else
                pairs.push_back(std::make_pair(*it, *next));
        }
        else
            break;
        std::advance(it, 2);
    }
    print_listpair(pairs);

    if (lst.size() % 2 == 1)
    {
        if (leftover.empty())
        {
            PmergeMe::lst::iterator it = raw_lst.begin();
            std::advance(it, lst.size() - 1);
            leftover.push_back(*it);
        }
        else
            leftover = push_element(leftover, lst.size() - 1);
    }

    PmergeMe::lst larger_nbr = extract_larger_number(pairs);
    PmergeMe::lst smaller_nbr = extract_smaller_number(pairs);
    PmergeMe::lst sorted = merge_insertion(larger_nbr);
    printf("\nLARGER NBRS\n");
    print_list(larger_nbr);

    printf("\nSMALLER NBRS\n");
    print_list(larger_nbr);

    printf("\nSORTED NBRS\n");
    print_list(larger_nbr);

    for (int i = 0; i < smaller_nbr.size(); i++)
    {
        PmergeMe::lst::iterator it = smaller_nbr.begin();
        std::advance(it , i);
        std::cout << BLUE << "smaller :" << END<<*it <<  std::endl;

        sorted = insert_nbr(sorted, *it);
    }
    for (int i = 0; i < leftover.size(); i++)
    {
        PmergeMe::lst::iterator it = leftover.begin();
        std::advance(it , i);
        std::cout << BLUE << "leftovers :" << END<<*it <<  std::endl;
        sorted = insert_nbr(sorted, *it);
    }
    return sorted;
}

PmergeMe::lst PmergeMe::push_element(PmergeMe::lst list, int index)
{
    PmergeMe::lst::iterator it = this->raw_lst.begin();
    std::advance(it, index);
    list.push_back(*it);
    return list;
}

void PmergeMe::display_lst_info()
{
    std::cout << "Before Sorting(lst) : " ;
    for(PmergeMe::lst::iterator it = raw_lst.begin(); it != raw_lst.end(); it++)
        std::cout << *it <<  " ";
    std::cout << "" << std::endl;

    std::cout << "After Sorting(lst) : ";
    for(PmergeMe::lst::iterator it = sorted_lst.begin(); it != sorted_lst.end(); it++)
        std::cout << *it <<  " ";

    std::cout << "" << std::endl;
}

void PmergeMe::display_vt_info()
{
    std::cout << "Before Sorting(vt) : " ;
    for( int x = 0; x < raw_lst.size(); x++)
    {
        std::cout << raw_vt[x] <<  " ";
    }
    std::cout << "" << std::endl;
    /* .................. */

    std::cout << "After Sorting(vt) : ";
    for( int x = 0; x < sorted_vt.size(); x++)
    {
        std::cout << sorted_vt[x] << " ";
    }
    std::cout << "" << std::endl;
}

PmergeMe::PmergeMe(std::string str)
{
    gettimeofday(&start, NULL); // start of analisis
    if (str.empty())
        throw std::runtime_error("empty string");

    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ' && !isdigit(str[i]))
            throw std::runtime_error("non valid str");
    }
    gettimeofday(&vt_start, NULL);
    fill_vt(str);
    sorted_vt = merge_insertion(raw_vt);
    gettimeofday(&vt_end, NULL);
    fill_lst(str);
    sorted_lst = merge_insertion(raw_lst);
    std::cout << "\n" << std::endl;
    
    display_lst_info();
    std::cout << "\n" << std::endl;
    display_vt_info();
}

PmergeMe::~PmergeMe()
{
}
