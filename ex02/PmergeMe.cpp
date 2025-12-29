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
    pv(this->og_vt, BLUE); // pv = print vector
    vt = this->og_vt;
    merge_insert(vt, 2);
    pv(this->vt,BLUE);
}

void PmergeMe::pv(PmergeMe::vtr a, std::string color)
{
    for (PmergeMe::vtr_it it = a.begin(); it != a.end() ; it++)
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
    PmergeMe::vector_pair cels;
    PmergeMe::vtr head_cels;
    PmergeMe::vtr vector_sorted = this->vt;
    int index = 0;
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
            if (*it > *(it + 1))
            { 
                ax = (it);
                cels.push_back(std::make_pair(*(it + 1), *it)); // se trocarmos isto, tmb teremos que trocar ois numeros que estarao a ser representados pelo HEAD
                /* TROCA DOS ELEMENTOS DENTRO DA PARCELA AX, BX <-> */
                if (cel_size == 2)
                    std::swap(vector_sorted[index], vector_sorted[(index+1)]);
                else
                {
                    for (int i = 0; i < (cel_size/2); i++)
                        std::swap(vector_sorted[((index*(cel_size/2))) + i], vector_sorted[((index*(cel_size/2)) + (cel_size/2) + i)]);
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
    this->vt = vector_sorted;
    if ((cel_size <= this->vt.size()/2))  
        merge_insert(head_cels, cel_size * 2);
    /* ate aqui consigo lidar em condicoes perfeitas caso nao haja sobras. */
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
    //todo : check for the main and pend vector, and fill the main/pend _str with the correspondent Ax and Bx 
    
    int x_val = 1;
    //for (vtr_it it = main.begin(); it != main.end(); it++)
    for (int i = 0; i <= main.size(); i += (cel_size / 2))
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
    //for (vtr_it it = pend.begin(); it != pend.end(); it++)
    for (int i = 0; i <= pend.size(); i += (cel_size / 2))
    {
        std::string b = "b";
        std::stringstream ss;
        ss << b << x_val;
        pend_str.push_back(ss.str());
        x_val++;
    }
   //pv(pend_str);
  
    
    /* exit(1); */
    //? number of blocks (ax + bx)
    int number_blocks = this->vt.size() / (cel_size/2);
    bool alone = false;
    if (number_blocks % 2 == 1)
        alone = true;
    int bx = number_blocks / 2 + alone;
    //pv(vt,BLUE);
    /* exit(1); */
    int bx_flag;
    //for (int  i = 0; i < pend_str.size(); i++)
    //{
    //    std::cout << pend_str[i] << std::endl;
    //}
    while(!pend.empty())
    {
       // std::cout << "pend_str :" << pend_str[0] << std::endl; 
        bx_flag = jn(bx); // bx flag aponta para 3, e vamos encontrar o bx menor mais proximo dele.
        int pend_idx = find_pend_x(pend_str,bx_flag);  //! -> VOU USAR ESTE INDEX PAR NO PEND ORIGINAL 
        // idx is the index of pend that is good to send to main        
        std::string pend_string = pend_str[pend_idx];
        //todo find the index to insert in main_str();
        int main_idx = find_main_x(main_str, pend_string); //! -> VOU USAR ESTE INDEX PAR NO MAIN ORIGINAL
        // Calculo no main og se pend.head(Bx) > A(x-1), se for ->  insiro, caso seja menor, continuo a comparar ate se maior;  
        //! BEFORE INSERTING , COMPARE THE NUMBERS OF THE HEADS NOW THAT U HAVE THE INDEX OF THE TARGET AND THE SENDER
        int sender_head = ((pend_idx * (cel_size)) + (cel_size/2)) - 1;
        int main_target_head = main[main_idx * (cel_size/2) + (cel_size/2) - 1]; // head do Ax correspondente a Bx
        //todo int main_target_head_start = main[main_idx * (cel_size/2)]; // inicio da parcela -> (Ax) correspondente a Bx
        std::cout << "cel size        :" << cel_size << std::endl;
        std::cout << YELLOW <<
        "sender_head     :" << sender_head << std::endl;
        std::cout << "pend[send_head]  :" << pend[sender_head] << std::endl;
        std::cout << "main_target_head: " << main_target_head << std::endl;
        std::cout << "main[main_idx]: " << main[main_idx] <<END<< std::endl;
        std::cout << "pend.size() :"<<  pend.size() << std::endl;
        std::cout << "main.size() :"<<  main.size() << std::endl;
        pv(pend, RED);
        std::cout << std::endl;
        pv(main, GREEN);
        std::cout << std::endl;

        sleep(1);
        std::cout << "-------------------------------" << std::endl;
        for (int i = main_idx; i >= 0; i--)
        {
         //   std::cout << "main[(main_idx - 1) * (cel_size/2) + ((cel_size/2) - 1)]: " << main[(main_idx - 1) * (cel_size/2) + ((cel_size/2) - 1)] << std::endl;
           // std::cout << "pend[sender_head] :" << pend[sender_head] << std::endl;
            // main[main_idx * (cel_size/2) + (cel_size/2) - 1
            if (pend[sender_head] > (main[(main_idx - 1) * (cel_size/2) + ((cel_size/2) - 1)])) // esta certo
            { // o if compara com o head do Ax certo, agora aqui adiciono o pend para o main 
                for (int i = 1; i < (cel_size/2) + 1; i++) // insert to main  //todo insert in main_str
                {
                    vtr_it it = main.begin() + (main_idx - 1) * (cel_size/2); 
                    std::cout << "pend sending: " << pend[sender_head - (cel_size/2) + i] << std::endl;
                    main.insert(it, (pend[sender_head - (cel_size/2) + i]));
                    pv(main, BLUE);
                }
                for (int i = 1; i < ((cel_size/2)); i++) // erase in  pend  //todo erase in pend_str
                {
                        if (pend.empty())
                            break ;
                        std::cout<< RED << "pend_erasing: " << *(pend.begin() + pend_idx*(cel_size))<<END << std::endl;
                        pend.erase(pend.begin() + pend_idx*(cel_size));
                        //vtr_it it1 = pend.begin() + pend_idx*(cel_size/2);
                        //vtr_it it2 = pend.begin() + pend_idx*(cel_size/2) + ((cel_size/2) -1);
                        //std::cout << "(cel_size/2) " << (cel_size/2)<< std::endl;
                        //std::cout << "it1 " << *it1<< std::endl;
                        //std::cout << "it2 " << *it2<< std::endl;
                        //pend.erase(pend.begin() + pend_idx * (cel_size/2), pend.begin() + pend_idx*((cel_size/2)-2));
                }
                    }
            }


                //todo  insert the whole section in it
        

        //todo erase pend[idx]
        
        //todo -> erase the bx in the pend_str and in the pend vector
        //todo -> then send it to main with the same logic to find the ax that correspond to bx;
        
        
       // it += jac; //? esta a apontar para o bx que sera inserido no main.

        //? it ate a apontar para o valor de bx;

    }


    //std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<< std::endl;
}


PmergeMe::~PmergeMe(){}
