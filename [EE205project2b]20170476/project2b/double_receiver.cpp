#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>
#include <sstream>

#include "double_list.h"

using namespace std;

/* DO NOT CHANGE INCLUDED HEADERS */

int main(int argc, char* argv[])
{
  /* 1st arg: input file name , 2nd arg: output file name */
    /* Write input file */
    ifstream inFile;
    int data1, data2;
    string data3;
    double_list list;
    d_list_elem* node;
    time_t start_t, end_t;
    double diff_t;

    // start
    time(&start_t);
    inFile.open(argv[1]);
    while(inFile >> data1 >> data2 >> data3)
    {
        node = new d_list_elem(data1, data2, data3);
        /* case 0: first input case */
        if(list.d_list_empty())
        {
            list.d_list_insert_front(node);
            continue;
        }
        d_list_elem* search = list.d_list_next(list.d_list_head());
        while(search != list.d_list_tail())
        {
            int first = list.d_list_get_data1(search);
            int second  = list.d_list_get_data2(search);

            if(first == data1)
            {
                /* case 1: all same 
                 * replace the node */
                if(second == data2)
                {
                    list.d_list_replace(search,node);
                    break;
                }
                /* case 2: data1 is same, but data2 is smaller 
                 * insert before the search node */
                else if(second > data2)
                {
                    list.d_list_insert_before(search,node);
                    break;
                }
                /* case 3: data1 is same, but data2 is bigger 
                 * continue to find the right place to be inserted 
                 * if search is the final element in the linked list,
                 * insert the node just after the search node */
                else if(second < data2)
                {
                    if(list.d_list_next(search) == list.d_list_tail())
                    {
                        list.d_list_insert_after(search,node);
                        break;
                    }
                }
            }
            /* case 4: data1 is smaller
             * insert before the search node */
            else if(first > data1)
            {
                list.d_list_insert_before(search,node);
                break;
            }
            /* case 5: data1 is bigger 
             * continue to find the right place to be inserted 
             * if search is the final element in the linked list,
             * insert the node just after the search node */
            else if(first < data1)
            {
                if(list.d_list_next(search) == list.d_list_tail())
                {
                    list.d_list_insert_after(search,node);
                    break;
                }
            }
            search = list.d_list_next(search);
        }
    }
    inFile.close();
    /* Write output file */
    ofstream outFile;
    outFile.open(argv[2]);
    d_list_elem* print = list.d_list_next(list.d_list_head());
    while(print != list.d_list_tail())
    {
        int msg_num = list.d_list_get_data1(print);
        int pck_num = 1;
        outFile << "- Message " << msg_num << endl;
        while((print != list.d_list_tail()) && (list.d_list_get_data1(print) == msg_num))
        {
            if(list.d_list_get_data2(print) != pck_num)
            {
                outFile << "WARNING: packet " << pck_num << " of message " << msg_num << " is missing" << endl;
                pck_num++;
                continue;
            }
            outFile << list.d_list_get_data3(print) << endl;
            print = list.d_list_next(print);
            pck_num++;
        }
        outFile << "- End Message " << msg_num << endl << endl;
    }
    time(&end_t);
    diff_t = difftime(end_t, start_t);
    outFile << "Running Time: " << diff_t << " s.";
    outFile.close();
    return 0;
}
