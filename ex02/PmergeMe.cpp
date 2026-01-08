#include "PmergeMe.hpp"
#include<unistd.h>
int jn(int n)
{
    int jn[n + 1];
    jn[0] = 0;
    jn[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        int j1 = jn[i - 1];
        int j2 = jn[i - 2];
        jn[i] = j1 + (2 * j2);
    }
    if (jn[n] > n)
        return jn[n - 1];
    return jn[n];
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
    std::cout << BLUE <<"BEFORE FJ: ";
    pv(this->og_vt, BLUE); // pv = print vector
    vt = this->og_vt;
    merge_insert(vt, 2);
    std::cout << BLUE<< "AFTER FJ : ";
    pv(this->vt,BLUE);
}

void PmergeMe::pv(PmergeMe::vtr a, std::string color, int cel)
{
    int i = 0;
    for (PmergeMe::vtr_it it = a.begin(); it != a.end() ; it++)
    {
        if (i == cel/2)
        {
            std::cout << " | ";
            i = 0;
        }
        std::cout <<color<< *it << ", ";
        i++;
    }
    std::cout << ";" <<END<< std::endl;
}

void PmergeMe::pv(std::vector<std::string> a, std::string color, int cel)
{
    int i = 0;

    for (std::vector<std::string>::iterator it = a.begin(); it != a.end() ; it++)
    {
        if (i == cel/2)
        {
            std::cout << " | ";
            i = 0;
        }
        std::cout <<color<< *it << ", ";
        i++;
    }
    std::cout << ";" <<END<< std::endl;
}


void PmergeMe::pv(PmergeMe::vtr a, std::string color)
{
    for (PmergeMe::vtr_it it = a.begin(); it != a.end() ; it++)
    {
        std::cout <<color<< *it << ", ";
    }
    std::cout << ";" <<END<< std::endl;
}


void PmergeMe::pv(std::vector<std::string> a, std::string color)
{
    for (std::vector<std::string>::iterator it = a.begin(); it != a.end() ; it++)
    {
        std::cout <<color<< *it << " ";
    }
    std::cout << ";" <<END<< std::endl;
}


void PmergeMe::fill_vt(std::string str) {
    PmergeMe::vtr tk_vt;
    this->og_vt = split(str, tk_vt);
}

PmergeMe::vtr PmergeMe::split(const std::string &str, PmergeMe::vtr token_vector)
{
	std::string 		 token;
	std::istringstream 	 iss(str);

	while(iss >> token)
		token_vector.push_back(atoi(token.c_str()));
	return token_vector;
}

int find_main_x(std::vector<std::string> v,  std::string pend_insert)
{
    int bx = pend_insert[1];
    for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
    {
        if ((*it)[1] == bx)
            return std::distance(v.begin(), it);
    }
    return v.size(); 
}

int find_pend_x(std::vector<std::string> &v,  int x)
{// x e o numero de jac que vamos procurar no pend para mandar para o main
    std::vector<std::string>::iterator max  = v.begin();
    int tmp = 0;
    for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
    {
        std::string s = *it;
        if (s[1] - '0' >= tmp && s[1] - '0' <= x)
        {
            tmp = s[1] - '0';
            max = it;
        }
        else
            break;
    }
    tmp = std::distance(v.begin(), max);
    return tmp;
}
/* 
int find_pend_target(vtr pend,  int x)
{// x e o numero de bx que vamos procurar no pend para mandar para o main
    for (std::vector<std::string>::iterator it = pend.begin(); it != pend.end(); it++)
    {
        
        return tmp;
    }
} */


void PmergeMe::merge_insert(PmergeMe::vtr &vetor, int cel_size)
{
    static int iteration;
    iteration++;
    PmergeMe::vector_pair cels;
    PmergeMe::vtr head_cels;
    PmergeMe::vtr vector_sorted = this->vt;
    int index = 0;
    static int flag = 0;
    for (PmergeMe::vtr::iterator it = vetor.begin(); it != vetor.end(); it += 2) 
    {
        if ((it - 1) == vetor.end())
            break;
        if (!(it + 1 == vt.end()))
        {
            PmergeMe::vtr::iterator ax = it + 1;
            if (*it > *(it + 1))
            { 
                ax = (it);
                cels.push_back(std::make_pair(*(it + 1), *it)); // se trocarmos isto, tmb teremos que trocar ois numeros que estarao a ser representados pelo HEAD
                if (cel_size == 2)
                    std::swap(vector_sorted[index], vector_sorted[(index+1)]);
                else
                {
                    for (int i = 0; i < (cel_size/2); i++)
                        std::swap(vector_sorted[((index*(cel_size/2))) + i], vector_sorted[((index*(cel_size/2)) + (cel_size/2) + i)]);
                }
            }
            else
                cels.push_back(std::make_pair(*it, *(it + 1)));
            head_cels.push_back(*ax);
            index +=2;
            }
        else
            break;
    }
    this->vt = vector_sorted;
    if ((cel_size <= this->vt.size()/2))  
        merge_insert(head_cels, cel_size * 2);
    vtr pend;
    vtr main;
    index = 0;
  std::vector<std::string> main_str;
  std::vector<std::string> pend_str;
  for (vtr_it it = this->vt.begin(); it != this->vt.end() ;)
  {
      if (index % 2 == 0) // Bx
      {
          if (index == 0)
          {
              for (int i = 0; i < cel_size/2; i++)
              {
                  main.push_back(this->vt[index*(cel_size/2) + i]);
                }
            }
            else
            {
                for (int i = 0; i < cel_size/2; i++)
                {
                    pend.push_back(this->vt[index*(cel_size/2) + i]);
                }
            }
        }
        else // Ax
        {
            for (int i = 0; i < cel_size/2; i++)
            {
                main.push_back(this->vt[index*(cel_size/2) + i]);
            }
        }        
        index++;
        it += (cel_size / 2);
    }
    
    int x_val = 1;
    for (int i = 0; i < main.size(); i += (cel_size / 2))
    {
        std::string b = "b";
        std::string a = "a";
        std::stringstream ss;
        if (i == 0)
        {
            ss << b << x_val;
            main_str.push_back(ss.str());
        }
        else
        {
            ss << a << x_val;
            main_str.push_back(ss.str());
            x_val++;
        }
    }
    x_val = 2;
    for (int i = 0; i < pend.size(); i += (cel_size / 2))
    {
        std::string b = "b";
        std::stringstream ss;
        ss << b << x_val;
        pend_str.push_back(ss.str());
        x_val++;
    }
    int number_blocks = this->vt.size() / (cel_size/2);
    bool alone = false;
    if (number_blocks % 2 == 1)
        alone = true;
    int bx = number_blocks / 2 + alone;
    int bx_flag;
    
    std::cout << "pend vector: " << std::endl;
    pv(pend,CYAN, cel_size);
    pv(pend_str,CYAN);
    std::cout << "main vector: " << std::endl;
    pv(main, CYAN, cel_size);
    pv(main_str, CYAN);

    std::cout << "-----------------------." << std::endl;
    std::cout << "-----------------------." << std::endl;
    std::cout << "-----------------------." << std::endl;
    std::cout << "-----------------------." << std::endl;
    std::cout << "-----------------------." << std::endl;
    std::cout << "-----------------------." << std::endl;
    std::cout << "-----------------------." << std::endl;
    std::cout << "-----------------------." << std::endl;
    std::cout << "-----------------------." << std::endl;
    while(!pend.empty())
    {
      bx_flag = jn(bx); // bx flag aponta para 3, e vamos encontrar o bx menor mais proximo dele.
      int pend_idx = find_pend_x(pend_str,bx_flag);  //! -> VOU USAR ESTE INDEX PAR NO PEND ORIGINAL 
      std::string pend_string = pend_str[pend_idx]; // ! -> representa o pend cel que vamos inserir no main 
      int main_idx = find_main_x(main_str, pend_string); //! -> VOU USAR ESTE INDEX PAR NO MAIN ORIGINAL -> este e o index da celula correspondente ao pend_str
      int pend_target_start_idx = pend_idx*(cel_size/2); // 
      int pend_target_end_idx = (pend_idx*(cel_size/2) ) + ((cel_size/2) - 1); // 
      int main_target_start_idx = main_idx*(cel_size/2); // 
      int main_target_end_idx = (main_idx*(cel_size/2) ) + ((cel_size/2) - 1); // 
      int  i = 0;
      while (pend[pend_target_end_idx] < main[main_target_end_idx - ((cel_size/2) * i) ] && (main_target_end_idx - ((cel_size/2) * i) >= 0))
      i++;
      int ideal_main_insertion_idx = main_target_end_idx - ((cel_size/2) * i);
      int ideal_main_str_insertion_idx = main_target_end_idx / (cel_size/2);
        for (int i = (cel_size/2); i > 0 ; i--) // loop where am going to insert the whole chunk of bx in the ideal main_inserttoin indx
        {
            vtr_it it = main.begin() + ideal_main_insertion_idx + 1;
            if (cel_size == 1)
            {
                std::cout << "i    : " << i << std::endl;
                std::cout << "send : " << pend[pend_target_end_idx - (cel_size/2) + i] << std::endl;
                std::cout <<"*it   : " << *it << std::endl;
            }
            
            main.insert(it, pend[pend_target_end_idx - (cel_size/2) + i]);
            
        }
        main_str.insert(main_str.begin() + ideal_main_str_insertion_idx + 1 , pend_string);
        for (int i = 0; i < (cel_size/2) ; i++) // loop where am going to insert the whole chunk of bx in the ideal main_inserttoin indx
        {
            if (pend.empty())
                break;
            vtr_it it = pend.begin() + pend_target_start_idx;
            pend.erase(it);
        }
        pend_str.erase(pend_str.begin() + pend_idx);
        if (cel_size == 2)
        {            
            std::cout <<BLUE<< "PEND: ";
            pv(pend, BLUE, cel_size);
            pv(pend_str, BLUE, cel_size);
            std::cout <<GREEN<< "MAIN: ";
            pv(main, GREEN, cel_size);
            pv(main_str, GREEN, cel_size);
            std::cout << "\n" << std::endl;

        }
        
    }
    this->vt = main;    
}


PmergeMe::~PmergeMe(){}
