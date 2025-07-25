/*
* Skeleton code for project 3 in EE205 2018 Fall KAIST
* Created by Yoonpyo Koo.
*/

#include "avl_tree.h"
#include <iostream>
#include <string>
#include "linked_list.h"
/* 
* Include your linked list here 
* e.g., #include "your_linked_list_header.h"
*/


using namespace std;

/* 
* You can do this! Feel free to ask to TA if you have anything unclear. 
* I'm here to help you!
*/

/* Return the height of the tree. Remember external nodes are valid nodes. 
* Suppose we have a tree as follows. * means an external node.
*           a
*         /   \
*        b     c
*       / \   / \
*      d   * *   *
*     / \
*    *   *
* Then this tree has the height of 3
*
* ### Already implemented.
*/
template <class T>
AVLTree<T>::AVLTree() {
	root = new AVLNode<T>("", NULL);
}

template <class T>
void
AVLTree<T>::destroy(AVLNode<T>* n)
{
    if(n == NULL) return;

    destroy(n->leftChild);
    destroy(n->rightChild);

    // destroy
    T* tmp = n->value;
    T* tmp1;
    while(tmp != NULL)
    {
        tmp1 = tmp;
        tmp = tmp->get_next();
        delete(tmp1);
    }
    if(is_root(n)) root = NULL;
    else
    {
        AVLNode<T> *parent = n->parent;
        if(parent->rightChild == n) parent->rightChild = NULL;
        else parent->leftChild = NULL;
    }
    delete(n);

}

template <class T>
AVLTree<T>::~AVLTree()
{
    destroy(root);
}


template <class T>
bool AVLTree<T>::is_external(AVLNode<T> *n) {

	return (n->leftChild == NULL && n->rightChild == NULL);
}

template <class T>
bool AVLTree<T>::is_root(AVLNode<T> *n) {
	
	return n->parent == NULL;
}

template <class T>
int AVLTree<T>::balance_factor(AVLNode<T> *n) {
	if (is_external(n))
		return 0;
	else
		return height(n->leftChild) - height(n->rightChild);
}

template <class T>
bool AVLTree<T>::is_balance(AVLNode<T> *n)
{
    return ((balance_factor(n) >= -1) && (balance_factor(n) <= 1));
}


template <class T>
AVLNode<T>* AVLTree<T>::removeAboveExternal(AVLNode<T> *n)
{
   AVLNode<T>* parent = n->parent;
   AVLNode<T>* sibling = (n == parent->leftChild ? parent->rightChild : parent->leftChild);
   if(is_root(parent))
   {
       root = sibling;
       sibling->parent = NULL;
       delete(n->value);
       delete(n);
       delete(parent);
       return sibling;
   }

   if(parent->parent->leftChild == parent)
   {
       parent->parent->leftChild = sibling;
   }
   else
   {
       parent->parent->rightChild = sibling;
   }
   sibling->parent = parent->parent;
   update_height(parent->parent);
   delete(n->value);
   delete(n);
   delete(parent);
   return sibling;
}



template <class T>
int AVLTree<T>::height(AVLNode<T> *n) {
	return n->height;
}

/*
* Assign proper height value after operations on nodes.
* You will need this function in some functions.
* such as rotate_right(), rotate_left(), balance(), etc.
*
* Make sure all children have proper heights before you execute
* this function on a node.
*
* ### Already implemented.
*/
template <class T>
void AVLTree<T>::update_height(AVLNode<T> *n) {
	if (is_external(n)) {
		n->height = 0;
	}
	else {
		int lh = height(n->leftChild);
		int rh = height(n->rightChild);

		n->height = (lh >= rh ? lh : rh) + 1;
	}
}

/* Print keys along inorder traversal. Separate each key by a single space.
* Do not print external node's key, which is an empty string. The input is
* the root node of the tree you want to tarverse.
* e.g.,
*           a
*         /   \
*        b     c
*       / \   / \
*      d   * *   *
*     / \
*    *   *
* Then this function should print "d b a c " (with no newline character).
* 
*/
template <class T>
void AVLTree<T>::inorder_print(AVLNode<T> *n) {
    if(is_external(n)) return;

    inorder_print(n->leftChild);

    cout << n->key << " ";
    cout << n->height << " ";
    T* search = n->value;
    do{
    cout << "value: " <<search->get_line() << " ";
    search = search->get_next();
    }
    while(search != NULL);

    inorder_print(n->rightChild);
}

/* 
* Print keys along preorder traversal. 
* The rule is the same as inorder_print(), except the order. 
*/
template <class T>
void AVLTree<T>::preorder_print(AVLNode<T> *n) {
    if(is_external(n)) return;

    cout << n->key << " ";
    cout << n->height << " ";
    T* search = n->value;
    do{
    cout << "value: " <<search->get_line() << " ";
    search = search->get_next();
    }
    while(search != NULL);

    preorder_print(n->leftChild);
    preorder_print(n->rightChild);
}

template <class T>
void AVLTree<T>::display() {
	if (is_external(root)) {
		cout << "Tree is empty." << endl;
		return;
	}
	cout << "root: " << root->key << endl;
      cout << "height: " << root->height << endl;
      cout << "inorder\n";
	inorder_print(root);
	cout << endl;
      cout << "preorder\n";
	preorder_print(root);
	cout << endl;
}


/* Refer to the supplementary PPT file. */
template <class T>
void AVLTree<T>::balance(AVLNode<T> *n) {
    AVLNode<T>* z = n;
    while(!is_root(z))
    {
        z = z->parent;
        update_height(z);
        if(!is_balance(z))
        {
            enum { left, right };
            int balance = balance_factor(z);
            int factor_1, factor_2;
            AVLNode<T>* y = (height(z->leftChild) >= height(z->rightChild) ? z->leftChild : z->rightChild);
            if(y == z->leftChild) factor_1 = left;
            else factor_1 = right;
            AVLNode<T>* x = (height(y->leftChild) >= height(y->rightChild) ? y->leftChild : y->rightChild);
            if(x == y->leftChild) factor_2 = left;
            else factor_2 = right;

            // divide into 4 cases
            // case 1: inorder z,y,x
            if(balance < -1 && factor_1 == right && factor_2 == right)
            {
                rotate_left(z);
            }
            // case 2 : inorder x,y,z
            else if(balance > 1 && factor_1 == left && factor_2 == left)
            {
                rotate_right(z);
            }
            // case 3: inorder z,x,y
            else if(balance < -1 && factor_1 == right && factor_2 == left)
            {
                rotate_right(y);
                rotate_left(z);
            }
            // case 4: inorder y,x,z
            else if(balance > 1 && factor_1 == left && factor_2 == right)
            {
                rotate_left(y);
                rotate_right(z);
            }
        }
    }
}

/* For your reference, the function has already been implemented. */
template <class T>
AVLNode<T>* AVLTree<T>::rotate_right(AVLNode<T> *n) {
	AVLNode<T> *x = n->leftChild;
	n->leftChild = x->rightChild;
	n->leftChild->parent = n;

	x->rightChild = n;
	x->parent = n->parent;
      if(is_root(x)) root = x;

	if (!is_root(n)) {
		if (n->parent->leftChild == n)
			n->parent->leftChild = x;
		else
			n->parent->rightChild = x;
	}
	n->parent = x;
	/* the order of updates is important */
	update_height(n);
	update_height(x);
	return x;
}

/* Refer to the supplementary PPT file. And right above ↑↑↑ */
template <class T>
AVLNode<T>* AVLTree<T>::rotate_left(AVLNode<T> *n) {
    AVLNode<T> *x = n->rightChild;

    // modify left child
    n->rightChild = x->leftChild;
    (n->rightChild)->parent = n;

    x->leftChild = n;
    x->parent = n->parent;
    if(is_root(x)) root = x;

    // modify parent of original tree
    if(!is_root(n))
    {
        if((n->parent)->leftChild == n)
        {
            (n->parent)->leftChild = x;
        }
        else
        {
            (n->parent)->rightChild = x;
        }
    }
    n->parent = x;

    // update the height
    update_height(n);
    update_height(x);
    return x;

}

/* 
* Refer to page 6 of the lecture note 'SearchTrees-BST_AVL'.
* CAUTION: You HAVE TO implement this function the way described in the lecture note.
* Use string::compare function for comparison between two keys.
*/
template <class T>
AVLNode<T>* AVLTree<T>::search(string key, AVLNode<T>* rt){
    if(is_external(rt)) return rt;
    if(key.compare(rt->key) < 0)
    {
        return search(key,rt->leftChild);
    }
    else if(key.compare(rt->key) == 0)
    {
        return rt;
    }
    else
    {
        return search(key,rt->rightChild);
    }
}

/*
* I have also implemented this function for your reference and convenience. 
* 조교 자비 오지고 지리고 렛잇고 아리랑 고개를 넘ㅇ...
*/
template <class T>
bool AVLTree<T>::insert(string key, int line) {
	AVLNode<T> *n = search(key, root);

	if (is_external(n)) {
		n->key = key;
            (n->value)->set_line(line);
		n->leftChild = new AVLNode<T>("", n);
		n->rightChild = new AVLNode<T>("", n);
            update_height(n);
		balance(n);

		return true;
	}
	else
      {
          T* tmp = n->value;
          while((tmp->get_next()) != NULL)
          {
              // already exist line number
              if(tmp->get_line() == line) return false;
             tmp = tmp->get_next();
          }

          if(tmp->get_line() == line) return false;
          T* new_node = new T(line);
          tmp->set_next(new_node);
          return false; // the key already exists
      }
}

/* 
* Remove a node. Return true if successful(if the key exists), false otherwise. 
* Refer to page 8~9, 22~23 of the lecture note 'SearchTrees-BST_AVL'.
* CAUTION: You HAVE TO implement this function the way described in the lecture note.
*/
template <class T>
bool AVLTree<T>::remove(string key) {
    AVLNode<T> *n = search(key, root);
    AVLNode<T> *tmp = NULL;
    if(is_external(n)) return false;
    else
    {
       // find external node
       if(is_external(n->leftChild))
       {
           tmp = removeAboveExternal(n->leftChild);
           balance(tmp);
           return true;
       }
       
       else if(is_external(n->rightChild))
       {
           tmp = removeAboveExternal(n->rightChild);
           balance(tmp);
           return true;
       }
       // if remove node's child is both internal, find leftmost
       else
       {
           AVLNode<T>* target = n->rightChild;
           while(!is_external(target))
           {
               target = target->leftChild;
           }
           AVLNode<T>* copy = target->parent;
           n->key = copy->key;
           n->value = copy->value;
           tmp = removeAboveExternal(target);
           balance(tmp);
           return true;
       }
    }

}

template <class T>
void AVLTree<T>::replace(string from, string to)
{
    AVLNode<T>* flag1 = search(from, root);
    AVLNode<T>* flag2 = search(to, root);
    if(flag1 == flag2) return;
    //case 1: if from is not in the tree
    if(is_external(flag1)) return;
    //case 2: if from is in the tree, and to is not in the tree.
    if(is_external(flag2))
    {
        T* tmp = flag1->value;
        T* tmp1;
        remove(from);
        while(tmp != NULL)
        {
            insert(to,tmp->get_line());
            tmp1 = tmp;
            tmp = tmp->get_next();
            delete(tmp1);
        }
        return;
    }
    //case 3: if from is in the tree, and to is also in the tree.
    //merge two sorted linked list
    T* src = flag1->value;
    T* dest = flag2->value;
    T* dest_tmp;
    T* new_ = new T;
    T* start = new_;
    remove(from);
    while(src != NULL && dest != NULL)
    {
        if(src->get_line() < dest->get_line())
        {
            start->set_next(src);
            src = src->get_next();
        }
        else if(src->get_line() == dest->get_line())
        {
            start->set_next(src);
            src = src->get_next();
            dest_tmp = dest;
            dest = dest->get_next();
            delete(dest_tmp);
        }
        else
        {
            start->set_next(dest);
            dest = dest->get_next();
        }
        start = start->get_next();
    }
    if(src == NULL && dest == NULL);
    else if(src == NULL) start->set_next(dest);
    else if(dest == NULL) start->set_next(src);

    flag2->value = new_->get_next();
    delete(new_);
}

/*
* You need to explicitly instantiate the template to use it in the main function.
* Instantiate here if you need to.
* e.g., 
* template class AVLTree<Your_linkedlist_class>;
*/
template class AVLTree<LL_node>;

/* You can do it! */

