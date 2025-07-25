#ifndef __DOUBLE_LIST_H__
#define __DOUBLE_LIST_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <iterator>

#include <string>

using namespace std;

/* List element. */
class d_list_elem{

 friend class double_list;

 private:

  int data1; /* Data of list element. */
  int data2; /* Data of list element. */
  string data3; /* Data of list element. */
  d_list_elem *next; /* Next list element. */
  d_list_elem *prev;   /* Previous list element. */    

 public:
  /* List element constructor. */
  d_list_elem (){
    next = NULL;
    prev = NULL;
  }
  d_list_elem (int _data1, int _data2, string _data3, d_list_elem *_next =NULL, d_list_elem *_prev = NULL){
    data1 = _data1;
    data2 = _data2;
    data3 = _data3;
    next = _next;
    prev = _prev;
  }
};


/* Doubly Linked List. */
class double_list{

 private:
  d_list_elem *head; /* List head. */
  d_list_elem *tail; /* List tail. */

 public:

  class Iter{
      public:
          // specify the iterator class
          // only work with int variable data type
          using value_type = int;
          using reference = int&;
          using pointer = int*;
          using difference_type = ptrdiff_t;
          using iterator_category = forward_iterator_tag;

          int operator*();
          bool operator==(const Iter& p) const;
          bool operator!=(const Iter& p) const;
          Iter& operator++();
          Iter& operator--();
          Iter(d_list_elem* _node) : node(_node) { }
      private:
          d_list_elem* node;
  };

  double_list(); //constructor
  ~double_list(); //destructor

  int get_data1(d_list_elem*);
  int get_data2(d_list_elem*);
  string get_data3(d_list_elem*);
  d_list_elem* list_next(d_list_elem*);
  d_list_elem* list_head(void);
  d_list_elem* list_tail(void);
  void insert_front(d_list_elem*);
  void insert_before(d_list_elem*, d_list_elem*);
  void insert_after(d_list_elem*, d_list_elem*);
  void list_replace(d_list_elem*, d_list_elem*);
  void list_remove(d_list_elem*);
  bool list_empty(void);
  Iter begin(void);
  Iter end(void);
};



#endif /* __DOUBLE_LIST_H__ */
