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

void PmergeMe::fill_lst(std::string str) {
    PmergeMe::lst tk_lst;
    this->raw_lst = split(str, tk_lst);
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

PmergeMe::lst PmergeMe::extract_larger_number(PmergeMe::lst_pair target)
{
    PmergeMe::lst x;
    for (lst_pair::iterator it = target.begin() ; it != target.end(); it++)
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
    for (vector_pair::iterator it = target.begin() ; it != target.end(); it++)
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

PmergeMe::lst insert_nbr(PmergeMe::lst lst, int  to_insert){
    int max =lst.size() - 1;
    int pos;
    int min = pos = 0;
    while(min <= max){
        pos = (min + max) / 2;
        if (to_insert == lst[pos])
        {
            lst.insert(lst.begin() + pos, to_insert);
            return (lst);    
        }
        else if (to_insert < lst[pos])
            max = pos - 1;
        else
            min = pos + 1;
    }    
    lst.insert(lst.begin() + min, to_insert);
    return lst;
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
    // todo: funcao que tire os numeros maiores dos pairs, para outro vetor
    PmergeMe::vtr larger_nbr = extract_larger_number(pairs);
    PmergeMe::vtr smaller_nbr = extract_smaller_number(pairs);
    PmergeMe::vtr sorted = merge_insertion(larger_nbr);
    for (int i = 0; i < smaller_nbr.size(); i++)
        sorted = insert_nbr(sorted, smaller_nbr[i]);
    for (int i = 0; i < leftover.size(); i++)
        sorted = insert_nbr(sorted, leftover[i]);
    return sorted;
}

PmergeMe::vtr PmergeMe::merge_insertion(PmergeMe::vtr lst)
{
    if (lst.size() <= 1) {return lst;}
    PmergeMe::vtr leftover;
    vector_pair pairs;
    for (PmergeMe::vtr::iterator it = lst.begin(); it != lst.end()/*  - 1 */ ; it+=2)
    {
        if (!(it + 1 == lst.end()))
        {
            if (*it > *(it + 1))
                pairs.push_back(std::make_pair(*(it + 1), *it));
            else
                pairs.push_back(std::make_pair(*it, *(it + 1)));
        }
        else
            break;
    }
    if (lst.size() % 2 == 1)
        leftover.push_back(lst[lst.size() - 1]);
    // todo: funcao que tire os numeros maiores dos pairs, para outro vetor
    PmergeMe::vtr larger_nbr = extract_larger_number(pairs);
    PmergeMe::vtr smaller_nbr = extract_smaller_number(pairs);
    PmergeMe::vtr sorted = merge_insertion(larger_nbr);
    for (int i = 0; i < smaller_nbr.size(); i++)
        sorted = insert_nbr(sorted, smaller_nbr[i]);
    for (int i = 0; i < leftover.size(); i++)
        sorted = insert_nbr(sorted, leftover[i]);
    return sorted;
}


PmergeMe::PmergeMe(std::string str)
{
    if (str.empty())
        throw std::runtime_error("empty string");
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ' && !isdigit(str[i]))
            throw std::runtime_error("non valid str");
    }
    fill_vt(str);
    display_vt_info();
    fill_lst(str);
    display_lst_info();

}

PmergeMe::~PmergeMe()
{
}
