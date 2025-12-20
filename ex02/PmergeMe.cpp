#include "PmergeMe.hpp"


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
    pv(this->og_vt); // pv = print vector
    vt = this->og_vt;
    merge_insert(vt, 2);
    
}

void PmergeMe::pv(PmergeMe::vtr a)
{
    for (PmergeMe::vtr_it it = a.begin(); it != a.end() ; it++)
    {
        std::cout << *it << " ";
    }
    std::cout << ";" << std::endl;
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
#include <iterator>
void PmergeMe::merge_insert(PmergeMe::vtr &vetor, int cel_size)
{
    PmergeMe::vector_pair cels;
    PmergeMe::vtr head_cels;
    PmergeMe::vtr vector_sorted = this->vt;
    int index = 0;
    //int index = 1;
    static int flag = 0;
    for (PmergeMe::vtr::iterator it = vetor.begin(); it != vetor.end(); it += 2) 
    {
        if ((it - 1) == vetor.end())
            break;
        /* vetor og, e estamos inicialmente a fazer parcelas de 2, se trocarmos algo e o size e 2, n repcisamos fazer nada
        se o size == 4, precisamos  */
        if (!(it + 1 == vt.end()))
        {
            PmergeMe::vtr::iterator ax = it + 1;
           // std::cout << "*it : " << *it << std::endl;
           // std::cout << "*it+1 : " << *(it + 1) << std::endl;
            if (*it > *(it + 1))
            { 
                ax = (it);
                cels.push_back(std::make_pair(*(it + 1), *it)); // se trocarmos isto, tmb teremos que trocar ois numeros que estarao a ser representados pelo HEAD
                /* TROCA DOS ELEMENTOS DENTRO DA PARCELA AX, BX <-> */
                if (cel_size == 2)
                {
                    //std::cout << "ATENCION: " << vector_sorted[index - 1]<< std::endl;
                    //std::cout << "ATENCION: " << vector_sorted[index]<< std::endl;
                    //std::swap(vector_sorted[index - 1], vector_sorted[(index)]);
                 //   std::cout << "ATENCION: " << vector_sorted[index]<< std::endl;
                 //   std::cout << "ATENCION: " << vector_sorted[index+1]<< std::endl;
                    std::swap(vector_sorted[index], vector_sorted[(index+1)]);

                }
                else
                {
                    for (int i = 0; i < (cel_size/2); i++)
                    {   
                      //  pv(vector_sorted);
                        //std::cout << "||ATENCION: " << vector_sorted[((index*(cel_size/2))) + i] << std::endl; // vai apontar para o primeiro item do *it
                        // 
                       // std::cout << ((index*cel_size/2)) + i << std::endl;/* ((index*cel_size) + cel_size) - (cel_size/2) + i */
                        
                      //  std::cout << "||SWAP    : " << vector_sorted[((index*cel_size/2) + (cel_size/2) + i)] << std::endl; // vai apontar para o primeiro item do *it + 1
                      //  std::cout << ((index*cel_size/2) + (cel_size/2) + i)<< std::endl;/*  */
                        
                        std::swap(vector_sorted[((index*(cel_size/2))) + i], vector_sorted[((index*(cel_size/2)) + (cel_size/2) + i)]);
                    }
                }
                
                /* TROCA DOS ELEMENTOS DENTRO DA PARCELA AX, BX <-> */
            }
            else
                cels.push_back(std::make_pair(*it, *(it + 1)));
            head_cels.push_back(*ax);
            index +=2;
            }
        else
            break;
    }
    flag = 1;
    std::cout <<  "-=------" << std::endl;
    this->vt = vector_sorted; 
//    if (!(cel_size > this->og_vt.size()/2))
    std::cout << "cel_size:" << cel_size << std::endl; 
    if ((cel_size <= this->og_vt.size()/2))  
    {
        pv(vector_sorted);
        merge_insert(head_cels, cel_size * 2);
    }
    /* ate aqui consigo lidar em condicoes perfeitas caso nao haja sobras. */
}


PmergeMe::~PmergeMe(){}
