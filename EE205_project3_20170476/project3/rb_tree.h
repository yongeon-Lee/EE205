/*
* Skeleton code for project 3 in EE205 2018 Fall KAIST
* Created by Wan Ju Kang.
*/

#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include <string>
#include <iostream>

using namespace std;
enum Color { RED, BLACK };

/* 
* ############################CAUTION!!!############################
* You can define any additional features for your debugging purpose,
* but make sure you remove all of them before you submit this.
* ##################################################################
*/
class RB_node;
class RB_tree;

class list_node
{
    friend class RB_node;
    public:
        list_node* next;
        int line;
        list_node()
        {
            next = NULL;
        }
        list_node(int _line)
        {
            line = _line;
            next = NULL;
        }
};

class RB_node
{
    friend class RB_tree;
    public:
        Color color;
        string key;
        list_node* value;
        RB_node* right;
        RB_node* left;
        RB_node* parent;
        
        RB_node(string key, RB_node* parent)
        {
            this->key = key;
            this->parent = parent;
            left = NULL;
            right = NULL;
            value = new list_node;
            color = BLACK;
        }
};

class RB_tree
{
    private:
        RB_node* root;
    protected:
        RB_node* rotate_right(RB_node* n);
        RB_node* rotate_left(RB_node* n);
    public:
        void destroy(RB_node*);
        void insert(string key, int line);
        void remove(string key);
        RB_node* search(string, RB_node*);
        bool is_external(RB_node*);
        bool is_root(RB_node*);
        void double_red(RB_node*);
        void inorder_print(RB_node*);
        void preorder_print(RB_node*);
        void display();
        RB_node* sibling(RB_node*);
        void swapColor(RB_node*,RB_node*);
        RB_node* removeAboveExternal(RB_node*);
        void double_black(RB_node*);
        bool hasRed(RB_node*);
        RB_node* get_root();
        void replace(string, string);
        RB_tree();
        ~RB_tree();
};

#endif
