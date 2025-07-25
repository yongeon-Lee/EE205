/*
* Skeleton code for project 3 in EE205 2018 Fall KAIST
* Created by Wan Ju Kang.
*/

#include "rb_tree.h"
#include <iostream>
#include <string>


RB_tree::RB_tree()
{
    root = new RB_node("",NULL);
}
RB_tree::~RB_tree()
{
    destroy(root);
}

void
RB_tree::destroy(RB_node* n)
{
    if(n == NULL) return;

    destroy(n->left);
    destroy(n->right);
    
    //destroy
    list_node* tmp = n->value;
    list_node* tmp1;
    while(tmp != NULL)
    {
        tmp1 = tmp;
        tmp = tmp->next;
        delete(tmp1);
    }
    if(is_root(n)) root = NULL;
    else
    {
        RB_node* parent = n->parent;
        if(parent->right == n) parent->right = NULL;
        else parent->left = NULL;
    }
    delete(n);
}

bool
RB_tree::is_external(RB_node* n)
{
    return (n->left == NULL && n->right == NULL);
}

bool
RB_tree::is_root(RB_node* n)
{
    return n->parent == NULL;
}

RB_node*
RB_tree::sibling(RB_node* n)
{
    return (n->parent->left == n ? n->parent->right : n->parent->left);
}

void
RB_tree::swapColor(RB_node* n1, RB_node* n2)
{
    Color tmp = n1->color;
    n1->color = n2->color;
    n2->color = tmp;
}

RB_node*
RB_tree::removeAboveExternal(RB_node* n)
{
    RB_node* parent = n->parent;
    RB_node* _sibling = sibling(n);
    if(is_root(parent))
    {
        root = _sibling;
        _sibling->parent = NULL;
        delete(n->value);
        delete(n);
        delete(parent);
        return _sibling;
    }
    if(parent->parent->left == parent)
    {
        parent->parent->left = _sibling;
    }
    else
    {
        parent->parent->right = _sibling;
    }
    _sibling->parent = parent->parent;
    delete(n->value);
    delete(n);
    delete(parent);
    return _sibling;
}

bool
RB_tree::hasRed(RB_node* n)
{
    if(is_external(n)) return false;
    return (n->left->color == RED || n->right->color == RED);
}

RB_node*
RB_tree::get_root()
{
    return root;
}


void
RB_tree::inorder_print(RB_node* n)
{
    if(is_external(n)) return;

    inorder_print(n->left);
    cout << n->key << " ";
    if(n->color == RED) cout << "color: RED ";
    else cout << "color: BLACK ";
    list_node* search = n->value;
    do
    {
        cout << "value: " << search->line << " ";
        search = search->next;
    }
    while(search != NULL);
    inorder_print(n->right);

}

void
RB_tree::preorder_print(RB_node* n)
{
    if(is_external(n)) return;
    cout << n->key << " ";
    if(n->color == RED) cout << "color: RED ";
    else cout << "color: BLACK ";
    list_node* search = n->value;
    do
    {
        cout << "value: " << search->line << " ";
        search = search->next;
    }
    while(search != NULL);
    preorder_print(n->left);
    preorder_print(n->right);
}

void
RB_tree::display()
{
    if(is_external(root))
    {
        cout << "Tree is empty." << endl;
        return;
    }
    cout << "root: " << root->key << endl;
    if(root->color == RED) cout << "color: RED";
    else cout << "color: BLACK";
    cout << endl;
    cout << "inorder print\n";
    inorder_print(root);
    cout << endl;
    cout << "preorder print\n";
    preorder_print(root);
    cout << endl;
}

RB_node*
RB_tree::rotate_right(RB_node* n)
{
   RB_node*x = n->left;
   n->left = x->right;
   n->left->parent = n;

   x->right = n;
   x->parent = n->parent;
   if(is_root(x)) root = x;

   if(!is_root(n))
   {
       if(n->parent->left == n) n->parent->left = x;
       else n->parent->right = x;
   }
   n->parent = x;
   return x;
}

RB_node*
RB_tree::rotate_left(RB_node* n)
{
    RB_node* x = n->right;
    n->right = x->left;
    n->right->parent = n;

    x->left = n;
    x->parent = n->parent;
    if(is_root(x)) root = x;
    
    if(!is_root(n))
    {
        if(n->parent->left == n) n->parent->left = x;
        else n->parent->right = x;
    }

    n->parent = x;
    return x;
}
void
RB_tree::double_red(RB_node* n)
{
    RB_node* pos = n;
    RB_node* parent = NULL;
    RB_node* grandparent = NULL;
    RB_node* _sibling = NULL;

    while(!is_root(pos) && (pos->color == RED) && (pos->parent->color == RED))
    {
        RB_node* parent = pos->parent;
        RB_node* grandparent = pos->parent->parent;
        RB_node* _sibling = sibling(parent);
        // CASE 1: recoloring
        if(_sibling->color == RED)
        {
            grandparent->color = RED;
            parent->color = BLACK;
            _sibling->color = BLACK;
            pos = grandparent;
        }
        // CASE 2: restructure
        else
        {
           enum { left, right };
           int factor_1, factor_2;
           if(grandparent->left == parent) factor_1 = left;
           else factor_1 = right;
           if(parent->left == pos) factor_2 = left;
           else factor_2 = right;
           // CASE 2-1: left left case
           if(factor_1 == left && factor_2 == left)
           {
               swapColor(parent, grandparent);
               pos = rotate_right(grandparent);
           }
           // CASE 2-2: left right case
           else if(factor_1 == left && factor_2 == right)
           {
               swapColor(pos, grandparent);
               rotate_left(parent);
               pos = rotate_right(grandparent);
           }
           // CASE 2-3: right left case
           else if(factor_1 == right && factor_2 == left)
           {
               swapColor(pos, grandparent);
               rotate_right(parent);
               pos = rotate_left(grandparent);
           }
           // CASE 2-4: right right case
           else if(factor_1 == right && factor_2 == right)
           {
               swapColor(parent, grandparent);
               pos = rotate_left(grandparent);
           }
        }
        root->color = BLACK;
    }
}

RB_node*
RB_tree::search(string key, RB_node* rt)
{
    if(is_external(rt)) return rt;
    if(key.compare(rt->key) < 0)
    {
        return search(key ,rt->left);
    }
    else if(key.compare(rt->key) == 0)
    {
        return rt;
    }
    else
    {
        return search(key, rt->right);
    }
}

void
RB_tree::insert(string key, int line)
{
    RB_node* n = search(key, root);
    if(is_external(n))
    {
        if(is_root(n)) n->color = BLACK;
        else n->color = RED;
        n->key = key;
        n->value->line = line;
        n->left = new RB_node("",n);
        n->right = new RB_node("",n);
        if(n->color == BLACK) return;
        double_red(n);
        return;
    }
    list_node* tmp = n->value;
    while((tmp->next) != NULL)
    {
        if(tmp->line == line) return;
        tmp = tmp->next;
    }
    if(tmp->line == line) return;
    list_node* new_node = new list_node(line);
    tmp->next = new_node;

}

void
RB_tree::double_black(RB_node * n)
{
    if(is_root(n)) return;
    if(is_external(sibling(n))) double_black(n->parent);
    else
    {
        RB_node* _sibling = sibling(n);
        RB_node* parent = _sibling->parent;
        // sibling is a black node
        // RESTRUCTURE
        if(_sibling->color == BLACK)
        {
            // CASE 1: if sibling's child has least one red
            if(hasRed(_sibling))
            {
                // let left is the first check order
                // left is the RED node
                if(_sibling->left->color == RED)
                {
                    // CASE 1-1: left-left case
                    if(parent->left == _sibling)
                    {
                        _sibling->left->color = BLACK;
                        _sibling->color = parent->color;
                        parent->color = BLACK;
                        rotate_right(parent);
                    }
                    // CASE 1-2: right-left case
                    else
                    {
                        _sibling->left->color = parent->color;
                        parent->color = BLACK;
                        rotate_right(_sibling);
                        rotate_left(parent);
                    }
                }
                // right is the RED node
                else
                {
                    // CASE 1-3: left-right case
                    if(parent->left == _sibling)
                    {
                        _sibling->right->color = parent->color;
                        parent->color = BLACK;
                        rotate_left(_sibling);
                        rotate_right(parent);
                    }
                    // CASE 1-4: right-right case
                    else
                    {
                        _sibling->right->color = _sibling->color;
                        _sibling->color = parent->color;
                        parent->color = BLACK;
                        rotate_left(parent);
                    }
                }
            }
            // CASE 2: if sibling's child is both BLACK
            else
            {
                // CASE 2-1: if sibling's parent is black
                // RECURSIVE
                if(parent->color == BLACK)
                {
                    _sibling->color = RED;
                    double_black(parent);
                }
                else
                {
                    parent->color = BLACK;
                    _sibling->color = RED;
                }
            }
        }//end if(_sibling color BLACK)
        // CASE 3: if sibling's color is RED
        else
        {
            // ADJUSTMENT
            RB_node* z = NULL;
            if(parent->right == _sibling) z = _sibling->right;
            else z = _sibling->left;
            // CASE 3-1: If z is the left child of sibling
            // left-left case
            if(_sibling->left == z)
            {
                parent->color = RED;
                _sibling->color = BLACK;
                rotate_right(parent);
            }
            // CASE 3-2: If z is the right child of sibling
            else
            {
                parent->color = RED;
                _sibling->color = BLACK;
                rotate_left(parent);
            }
            double_black(n);
        }
    }// end else-if(is external)
}

void
RB_tree::remove(string key)
{
    RB_node* n = search(key, root);
    RB_node* tmp = NULL;
    // no node that has a key
    if(is_external(n)) return;
    else
    {
        if(is_external(n->left))
        {
            // CASE 0 : either v or r is red
            if(n->color == RED || n->right->color == RED)
            {
                n->right->color = BLACK;
                removeAboveExternal(n->left);
            }
            // CASE 1 : both are black
            else
            {
                RB_node* r = removeAboveExternal(n->left);
                double_black(r);
            }
            return;
        }
        else if(is_external(n->right))  
        {
            // CASE 0
            if(n->color == RED || n->left->color == RED)
            {
                n->left->color = BLACK;
                removeAboveExternal(n->right);
            }
            // CASE 1: both are black
            else
            {
                RB_node* r = removeAboveExternal(n->left);
                double_black(r);
            }
            return;
        }
        // find inorder processor
        else
        {
            RB_node* target = n->right;
            RB_node* r = NULL;
            while(!is_external(target->left))
            {
                target = target->left;
            }
            n->key = target->key;
            n->value = target->value;
            // CASE 0
            if(target->color == RED || target->right->color == RED)
            {
                target->right->color = BLACK;
                r = removeAboveExternal(target->left);
            }
            // CASE 1: both are black
            else
            {
                r = removeAboveExternal(target->left);
                double_black(r);
            }

            return;

        }
    }
}

void
RB_tree::replace(string from, string to)
{
    RB_node* flag1 = search(from, root);
    RB_node* flag2 = search(to, root);
    if(flag1 == flag2) return; 
    // case 1: if from is not in the tree
    if(is_external(flag1)) return;
    // case 2: if from is in the tree and to is not in the tree.
    if(is_external(flag2))
    {
        list_node* tmp = flag1->value;
        list_node* tmp_;
        remove(from);
        while(tmp != NULL)
        {
            insert(to, tmp->line);
            tmp_ = tmp;
            tmp = tmp->next;
            delete(tmp_);
        }
        return;
    }
    // case 3: if from is in the tree and to is alos in the tree
    // merge two sorted linked list.
    list_node* src = flag1->value;
    list_node* dest = flag2->value;
    list_node* dest_tmp;
    list_node* new_ = new list_node;
    list_node* start = new_;
    remove(from);
    while(src != NULL && dest != NULL)
    {
        if(src->line < dest->line)
        {
            start->next = src;
            src = src->next;
        }
        else if(src->line == dest->line)
        {
            start->next = src;
            src = src->next;
            dest_tmp = dest;
            dest = dest->next;
            delete(dest_tmp);
        }
        else
        {
            start->next = dest;
            dest = dest->next;
        }
        start = start->next;
    }
    if(src == NULL && dest == NULL);
    else if(src == NULL) start->next = dest;
    else if(dest == NULL) start->next = src;

    flag2->value = new_->next;
    delete(new_);
}
