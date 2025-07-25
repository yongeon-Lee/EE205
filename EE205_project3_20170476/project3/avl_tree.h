/*
* Skeleton code for project 3 in EE205 2018 Fall KAIST
* Created by Yoonpyo Koo.
*/

#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <string>
#include <iostream>

using namespace std;

/* 
* ############################CAUTION!!!############################
* You can define any additional features for your debugging purpose,
* but make sure you remove all of them before you submit this.
* ##################################################################
*/

template <class T>
class AVLNode
{
public:
	string key;
	T *value;
	int height;

	class AVLNode<T> *leftChild;
	class AVLNode<T> *rightChild;
	class AVLNode<T> *parent;

	AVLNode(string k, AVLNode<T> *p) {
		key = k;
		leftChild = NULL;
		rightChild = NULL;
		parent = p;
		value = new T;
		height = 0;
	}

};


template <class T>
class AVLTree {
public:
	AVLTree();
      ~AVLTree();
	void display();

	bool insert(string key, int line);
	bool remove(string key);
	AVLNode<T>* search(string key, AVLNode<T>*);
      void replace(string from, string to);

	bool is_external(AVLNode<T> *n);
	bool is_root(AVLNode<T> *n);
      AVLNode<T>* get_root(){return root;}


private:
	AVLNode<T> *root;
	int height(AVLNode<T> *n);
	void update_height(AVLNode<T> *n);
	int balance_factor(AVLNode<T> *n);
      bool is_balance(AVLNode<T> *n);
	void balance(AVLNode<T> *n);
      AVLNode<T>* removeAboveExternal(AVLNode<T> *n);
	AVLNode<T>* rotate_right(AVLNode<T> *n);
	AVLNode<T>* rotate_left(AVLNode<T> *n);
      void destroy(AVLNode<T>* n);
	void inorder_print(AVLNode<T> *n);
	void preorder_print(AVLNode<T> *n);
};

#endif /* __AVL_TREE_H__ */
