#include "PmergeMe.hpp"
#include<unistd.h>
#include <stdio.h>
PmergeMe::vtr jn(int n)
{
    PmergeMe::vtr jn; 
    jn.push_back(0);
    jn.push_back(1);

    for (int i = 2; i <= n; i++)
    {
        int j1 = jn[i - 1];
        int j2 = jn[i - 2];
        jn.push_back(j1 + (2 * j2));
        if (jn[i] > n)
        {
            jn.erase(jn.begin());
            jn.erase(jn.begin());
            jn.erase(jn.begin());
            jn.pop_back();
            return jn;
        }
    }
    jn.erase(jn.begin());
    jn.erase(jn.begin());
    return jn;
}

int check_numbers(std::vector<int> s)
{
    for (std::vector<int>::iterator it = s.begin(); it + 1 != s.end() ; it++)
    {
        
        if (*it > *(it + 1))
            return 0;
    }
    return 1;
}


PmergeMe::PmergeMe(std::string str)
{

    iterations = 0;
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
    std::cout <<OLIVE <<  "ITERATIONS : " << iterations <<END<< std::endl;
    this->og_vt.clear();
    if (check_numbers(this->vt))
        std::cout << RED << "AAAAA CRLH RAHHHHH 🇺🇸🦅\n";
    else
        std::cout << "a .... fds....\n";
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

    int x = 0;
	while(iss >> token)
    {
        x = atoi(token.c_str());
        if (x == -1)
            throw std::runtime_error("overflow of the interger value!");;
        token_vector.push_back(x);
    }
	return token_vector;
}

int find_main_x(std::vector<std::string> v,  std::string pend_insert)
{
     
    pend_insert.erase(pend_insert.begin());
    int bx = atoi(pend_insert.c_str());
    for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
    {
        std::string tmp = *it;
        tmp.erase(tmp.begin());
        int b_num = atoi(tmp.c_str());
        if (b_num == bx)
            return std::distance(v.begin(), it);
    }
    return v.size() - 1; 
}

int find_pend_x(std::vector<std::string> &v,  int x)
{// x e o numero de jac que vamos procurar no pend para mandar para o main
    std::vector<std::string>::iterator max  = v.begin();
    int tmp = 0;

    for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
    {
        std::string s = *it;
        s.erase(s.begin()); 
        if (atoi(s.c_str()) >= tmp && atoi(s.c_str()) <= x)
        {
            tmp = atoi(s.c_str());
            max = it;
        }
        else
            break;
    }

    tmp = std::distance(v.begin(), max);
    std::cout << "tmp : " << tmp << "\n";
    return tmp;
}

int upgrade_jn(std::vector<std::string> pend_str, int jac_number, int bx_max )
{
    //if (pend_str)
    std::string str = pend_str[0];
    //std::cout << "~~~~~~~~~~~~~~~~~\n";
   // std::cout <<RED<< "str before  : " << str << std::endl;  
    str.erase(str.begin());
   // std::cout <<RED<< "str after   : " << str << std::endl; 
    int r  = atoi(str.c_str()) ;

    //std::cout << "r                :" << r << std::endl;
    //std::cout << "jac_number :" << jac_number << std::endl;
    if ((r > jac_number))
        return 1;
    return 0;
}

void PmergeMe::merge_insert(PmergeMe::vtr &head_vectors, int cel_size)
{
    /*  na iteracao para checar cad numero , eu tenho que criar blocos de numeros que irao ser denominados por
    // para saber o numero de blocks (A/B)x -> block_ n = head_vectors.size() / (celsize/2);
    (a / b)x para calcular o numero de blockos que podem sair do veotr inicial, eu
        numero_de_blocos = head_vectors.size() / (cel_size/2)
        no loop para criar CADA a e b x, terei um contador que sera incremetnado a cada ACAO de (acao == criar um bloco ax ou bx) quando chegar ao 
        maximo de blocos possiveis de criar, e se ainda tiver numeros para tal, entao esses serao nao participantes
        e serao adicionados no final do head_vectors
        // tenho que parar de checar por pares quando i > block_n; 
        */
    PmergeMe::vector_pair cels;
    PmergeMe::vtr head_cels;
    PmergeMe::vtr vector_sorted = this->vt;
    int index = 0;
    int max_blocks =  this->vt.size() / (cel_size/2);

    std::cout << "max_blocks : " << max_blocks << std::endl;

    int dist = 0;
    int i = 0; // vai confirmar se posso avacar com a criacao de (a/b)x;
    for (PmergeMe::vtr_it it = head_vectors.begin(); it != head_vectors.end();) 
    {
        
        if (i < max_blocks)
        {
            PmergeMe::vtr_it tmp;
            if ((it + 1 != head_vectors.end()))
            {
                tmp = it + 1;
                if (*tmp < *it)
                {
                    if (cel_size == 2)
                        std::swap(vector_sorted[index], vector_sorted[(index + 1)]);
                    else
                    {
                        for (int i = 0; i < (cel_size/2); i++)
                            std::swap(vector_sorted[((index*(cel_size/2))) + i], vector_sorted[((index*(cel_size/2)) + (cel_size/2) + i)]);
                    }
                    head_cels.push_back(*it); //! cuidado ?
                }
                else
                {
                    head_cels.push_back(*tmp); //! cuidado ?
                }
                index +=2;
                it+=2;
                pv(head_cels, ORANGE, 0);
                
            }
            i++;
        }
        else
        {
//            std::cout << "inside" << std::endl;
//            for (PmergeMe::vtr_it it2 = it; it2 < head_vectors.end(); it2++)
//                vector_sorted.push_back(*it2);
//            //adiciona os restantes (nao participantes ) no vetor principal 
            break;
        }
    }
    /* 
    for (PmergeMe::vtr::iterator it = vetor.begin(); it != vetor.end(); ) 
    { 
        if ((it - 1) == vetor.end())
            break;
        if (!(it + 1 == vt.end()))
        {
            PmergeMe::vtr::iterator ax = it + 1;
            if (*it > *(it + 1))
            { 
                ax = (it);
                if (cel_size == 2)
                    std::swap(vector_sorted[index], vector_sorted[(index+1)]);
                else
                {
                    for (int i = 0; i < (cel_size/2); i++)
                        std::swap(vector_sorted[((index*(cel_size/2))) + i], vector_sorted[((index*(cel_size/2)) + (cel_size/2) + i)]);
                }
            }
            head_cels.push_back(*ax);
            index +=2;
        }
        else
            break;
        it+=2;
    } */
    this->vt = vector_sorted;
    pv(this->vt, RED, 0);
    if ((cel_size <= this->vt.size()/2))
    {
        iterations++;
        merge_insert(head_cels, cel_size * 2);
    }
    //exit(1);
    vtr pend;
    vtr main;
    index = 0;
  std::vector<std::string> main_str;
  std::vector<std::string> pend_str;
  int increment = 0;

  for (vtr_it it = this->vt.begin(); it != this->vt.end() ;)
  {
    if(increment >= max_blocks)
    {
        if (this->vt.size() > (max_blocks * cel_size / 2))
        {
      //      std::cout << "INSIDE NEW IF\n";
            int index2 = max_blocks * cel_size / 2;
            while (this->vt.size() > index2)
            {
                pend.push_back(this->vt[index2++]);
            }
       //     std::cout << "THIS VECTPOR : ";
        //    pv(this->vt, ORANGE, 0);
      //      std::cout << "PEND : VECTOR : ";
        //    pv(pend, ORANGE, 0);
            break;
        }
    }
      if (index % 2 == 0) // Bx
      {
          if (index == 0)
          {
       //     std::cout << "INSIDE\n";
              for (int i = 0; i < cel_size/2; i++)
              {
                  main.push_back(this->vt[index*(cel_size/2) + i]);
                }
            }
            else
            {
                for (int i = 0; i < cel_size/2; i++)
                {
                    if ((index*(cel_size/2) + i) >= this->vt.size())
                        break;
                    pend.push_back(this->vt[index*(cel_size/2) + i]); //! SEGFAULTT
                }
            }
            increment++;
        }
        else // Ax
        {
        //    std::cout << "INSIDE\n";
            for (int i = 0; i < cel_size/2; i++)
            {
                if ((index*(cel_size/2) + i) >= this->vt.size())
                    break;
                main.push_back(this->vt[index*(cel_size/2) + i]); //! SEGFAULTTTT
            }
            increment++;
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
        if (pend.size() - i < cel_size/2)
            break;
        std::string b = "b";
        std::stringstream ss;
        ss << b << x_val;
        pend_str.push_back(ss.str());
        x_val++;
    }
    int number_blocks = this->vt.size() / (cel_size/2); //! THIS MIGH BE WRONG
    bool alone = false;
    if (number_blocks % 2 == 1)
        alone = true;
    int bx = number_blocks / 2 + alone;
    
    vtr jn_vtr = jn(bx); // bx flag aponta para 3, e vamos encontrar o bx menor mais proximo dele.
    int h = 0; // h =  o index do jc vector do qual vamos aplicar no pend (na insercao)
    while(!pend.empty())
    {
        if (pend_str.empty())
        {
            // -> 
            for (int i = 0; i < pend.size(); i++)
                main.push_back(pend[i]);
            break;
        }

        if (upgrade_jn(pend_str,jn_vtr[h], bx ))
            h++;
        
        int pend_idx = find_pend_x(pend_str,jn_vtr.size() >= h ?  jn_vtr[h] : bx );  //! -> VOU USAR ESTE INDEX PAR NO PEND ORIGINAL 



        std::string pend_string = pend_str[pend_idx]; // ! -> representa o pend cel que vamos inserir no main 
        
        int main_idx = find_main_x(main_str, pend_string); //! -> VOU USAR ESTE INDEX PAR NO MAIN ORIGINAL -> este e o index da celula correspondente ao pend_str
        
        //std::cout << "main_idx : " << main_idx << std::endl;

        int pend_target_start_idx = pend_idx*(cel_size/2); // 
        int pend_target_end_idx = (pend_idx*(cel_size/2) ) + ((cel_size/2) - 1); // 
        int main_target_start_idx = main_idx*(cel_size/2); // 
        int main_target_end_idx = (main_idx*(cel_size/2) ) + ((cel_size/2) - 1); // 
        int  i = 0;
        while (pend[pend_target_end_idx] <= main[main_target_end_idx - ((cel_size/2) * i) ] && (main_target_end_idx - ((cel_size/2) * i) >= 0))
            i++;

      int ideal_main_insertion_idx = main_target_end_idx - ((cel_size/2) * i);

      int ideal_main_str_insertion_idx = ideal_main_insertion_idx / (cel_size/2);   //main_target_end_idx / (cel_size/2);
    //std::cout << "BEFOREEEEE  "<< std::endl;
   // std::cout << "pend vector: " << std::endl;
   // pv(pend,CYAN, cel_size);
   // pv(pend_str,CYAN);
    //std::cout << "main vector: " << std::endl;
   // pv(main, CYAN, cel_size);
   // pv(main_str, CYAN);
 //   std::cout << "AFTER  "<< std::endl;
        for (int i = (cel_size/2); i > 0 ; i--) // loop where am going to insert the whole chunk of bx in the ideal main_inserttoin indx
        {
            vtr_it it = main.begin() + ideal_main_insertion_idx + 1;
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
      //      std::cout <<BLUE<< "PEND: ";
    ////        pv(pend, BLUE, cel_size);
      //      pv(pend_str, BLUE, cel_size);
      //      std::cout <<GREEN<< "MAIN: ";
      //      pv(main, GREEN, cel_size);
      //      pv(main_str, GREEN, cel_size);
      //      std::cout << "\n" << std::endl;
    }    
    //pv(main, OLIVE, 0);
    std::cout <<RED<< "=========================================" << std::endl;
    this->vt = main;    
    
}


PmergeMe::~PmergeMe(){}
