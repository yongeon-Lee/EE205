/*
* Skeleton code for project 3 in EE205 2018 Fall KAIST
* Created by Yoonpyo Koo
*
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include <vector>
#include <iterator>
#include "avl_tree.cpp"
/* Include more if you need */

using namespace std;

/* Use these functions to replace words in a string. 
* Make sure you add -std=c++11 option when you compile.
*/

bool replace_all(string& str, const string& from, const string& to) 
{
    string lower_str = str;
    transform(str.begin(), str.end(), lower_str.begin(), ::tolower);
    size_t pos = 0;
    while((pos = lower_str.find(from, pos)) != string::npos)
    {
        if(pos == 0)
        {
            if(pos + from.size() == str.size());
            else if(!isspace(str.at(pos + from.size())))
            {
                pos++;
                pos = lower_str.find(from, pos);
                continue;
            }
        }
        else if(pos + from.size() == str.size())
        {
            if(!isspace(str.at(pos-1)))
            {
                pos++;
                pos = lower_str.find(from, pos);
                continue;
            }
        }
        else
        {
            if(!isspace(str.at(pos-1)) || !isspace(str.at(pos + from.size())))
            {
                pos++;
                pos = lower_str.find(from, pos);
                continue;
            }
        }
        str.replace(pos, from.size(), to);
        pos ++;
        lower_str = str;
        pos = lower_str.find(from, pos);
    }
    return true;
}


int main(int argc, char* argv[])
{
    ifstream inFile;
    inFile.open(argv[1]);
    string words;
    string line;
    vector<string> storelist;
    int line_num = 1;
    int state = true;
    string command;

    // Make tree with input file
    AVLTree<LL_node> tree;
    while(getline(inFile,line))
    {
        storelist.push_back(line);
        istringstream iss(line);
        while(iss >> words)
        {
            std::transform(words.begin(), words.end(), words.begin(), ::tolower);
            tree.insert(words,line_num);
        }
        line_num++;
    }
    inFile.close();
    int R = false;
    while(state)
    {
        char command;
        string search, replace;
        cout << "R: replace Q: quit this program\n";
        cin >> command;
        switch(command)
        {
            case 'R':
                {
                    R = true;
                    ofstream outFile;
                    outFile.open(argv[2]);
                    cin >> search >> replace;
                    // lower the case
                    std::transform(search.begin(), search.end(), search.begin(), ::tolower);
                    AVLNode<LL_node>* find = tree.search(search, tree.get_root());
                    // if search is in the input file
                    if(!tree.is_external(find))
                    {
                        LL_node* t = find->value;
                        for(int i = 0; i < storelist.size(); i++)
                        {
                            // in-line operation
                            if(t != NULL && (i+1) == t->get_line())
                            {
                                cout << "<" << storelist[i] << endl;
                                replace_all(storelist[i], search, replace);
                                outFile << storelist[i] << endl;
                                cout << ">" << storelist[i] <<endl;
                                cout << endl;
                                t = t->get_next();
                            }
                            else outFile << storelist[i] << endl;
                        }
                    }
                    else
                    {
                        for(int i = 0; i < storelist.size(); i++)
                        {
                            outFile << storelist[i] << endl;
                        }
                    }
                    transform(replace.begin(), replace.end(), replace.begin(), ::tolower); 
                    tree.replace(search, replace);
                    outFile.close();
                }break;
            case 'Q':
                {
                    if(R == false)
                    {
                        ofstream outFile;
                        outFile.open(argv[2]);
                        for(int i = 0; i < storelist.size(); i++) outFile << storelist[i] << endl;
                        outFile.close();
                    }
                    cout << "Quit" << endl;
                    state = false;
                }break;
            default:
                {
                    cout << "Invalid argument" << endl;
                }break;
        }
    }
   return 0;

}
