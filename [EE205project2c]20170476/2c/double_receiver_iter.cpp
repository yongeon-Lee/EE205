#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "double_list_iter.h"

using namespace std;

/* YOU CAN CHANGE INCLUDED HEADERS ^0^ */

int main(int argc, char* argv[])
{
  /* 1st arg: input file name , 2nd arg: output file name */
    double_list dlist;
    ifstream fin;
    int data1, data2;
    string data3;
    d_list_elem* node = NULL;
    /* Write the input file */
    fin.open(argv[1]);
    while(fin >> data1 >> data2 >> data3)
    {
        node = new d_list_elem(data1, data2, data3);
        if(dlist.list_empty())
        {
            dlist.insert_front(node);
            continue;
        }
        d_list_elem* search = dlist.list_next(dlist.list_head());
        while(search != dlist.list_tail())
        {
            int first = dlist.get_data1(search);
            int second  = dlist.get_data2(search);

            if(first == data1)
            {
                if(second == data2)
                {
                    dlist.list_replace(search,node);
                    break;
                }
                else if(second > data2)
                {
                    dlist.insert_before(search,node);
                    break;
                }
                else if(second < data2)
                {
                    if(dlist.list_next(search) == dlist.list_tail())
                    {
                        dlist.insert_after(search,node);
                        break;
                    }
                }
            }
            else if(first > data1)
            {
                dlist.insert_before(search,node);
                break;
            }
            else if(first < data1)
            {
                if(dlist.list_next(search) == dlist.list_tail())
                {
                    dlist.insert_after(search,node);
                    break;
                }
            }
            search = dlist.list_next(search);
        }
    }
    fin.close();
    /* Write the ouput file */
    ofstream fout;
    fout.open(argv[2]);
    /* Check whether the 4th Message exist or not */
    double_list::Iter p = find(dlist.begin(), dlist.end(), 4);
    if (p == dlist.end())
    {
        fout << "No 4th message" << endl;
    }
    else
    {
        fout << "4th message exists" << endl;
    }
    return 0;
}
