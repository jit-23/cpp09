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


PmergeMe::vtr PmergeMe::Jacobsthal_insert(PmergeMe::vtr vt, int  to_insert)
{
    PmergeMe::vtr j;
    j.push_back(0);
    j.push_back(1);
    //todo push x elements till the value of Jn is greater than vt.size()
    //? per ex: vt.size() = 6,  J = [0, 1, 1, 3, 5, 11] // 5 < 6 < 11
    //?                     index = [0, 1, 2, 3, 4, 5 ]
    while(j.back() <= vt.size())
    {
        int jn = j[j.size() - 1]/* j.back() */ + (2*(j[j.size() - 2]));
        j.push_back(jn);
    }
    // ? at this point i have the jacob vector to work with
   for (PmergeMe::vtr::iterator it = vt.begin(); it != vt.end(); it++)
   {
       std::cout << "sorted-> : "  << *it << std::endl;
   }
   printf("-------------------\n");


    int prev = 0;
    int k = 0;
    int index = 0;

    int x = vt.size();
    int y = j.size();
    while (k + 1 < j.size() && j[k + 1] < vt.size()) //(k + 1 < j.size() && j[k + 1] < vt.size()
        k++;
    index = j[k];
    prev = 
    //? quando o to_insert == 2
    //? comeca a dar errado ./PmergeMe " 6 5 4 3 2 1"
    while(k > 1)
    {
        if (vt[index] == to_insert)
            break;
        if (vt[index] < to_insert)
        {
            prev = index;
            index = std::max(index + j[k - 1], static_cast<int>(vt.size() - 1));
        }
        else if (vt[index] > to_insert)
            index = std::min(prev,index - j[k - 2]);
        k--;
    }

    //while(index < vt.size() && vt[index] < to_insert)
    //    index++;
    //while(index > 0 && vt[index - 1] > to_insert)
    //    index--;
    vt.insert(vt.begin() + index, to_insert);
return vt;
}


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
        sorted = Jacobsthal_insert(sorted, smaller_nbr[i]);
    for (int i = 0; i < leftover.size(); i++)
        sorted = Jacobsthal_insert(sorted, leftover[i]);
    return sorted;
}

    



PmergeMe::lst PmergeMe::merge_insertion(PmergeMe::lst lst)
{
    if (lst.size() <= 1) {
        return lst;
    }
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

            PmergeMe::lst::iterator it = lst.begin();
            std::advance(it, lst.size() - 1);
            std::cout << "???? -> :" << *it << std::endl;
            leftover.push_back(*it);
    }
    PmergeMe::lst larger_nbr = extract_larger_number(pairs);
    PmergeMe::lst smaller_nbr = extract_smaller_number(pairs);
    
    PmergeMe::lst sorted = merge_insertion(larger_nbr);
    print_list(sorted);

    for (int i = 0; i < smaller_nbr.size(); i++)
    {
        PmergeMe::lst::iterator it = smaller_nbr.begin();
        std::advance(it , i);
        std::cout << BLUE << "smaller :" << END<<*it <<  std::endl;
        sorted = insert_nbr(sorted, *it);
    }
    printf("smaller puted: \n");
    print_list(sorted);
    for (int i = 0; i < leftover.size(); i++)
    {
        PmergeMe::lst::iterator it = leftover.begin();
        std::advance(it , i);
        std::cout << BLUE << "leftovers :" << END<<*it <<  std::endl;
        sorted = insert_nbr(sorted, *it);
    }
    printf("leftover puted: \n");
    print_list(sorted);
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
   // sorted_lst = merge_insertion(raw_lst);
    std::cout << "\n" << std::endl;
    
    //display_lst_info();
    std::cout << "\n" << std::endl;
    display_vt_info();
}

PmergeMe::~PmergeMe()
{
}
