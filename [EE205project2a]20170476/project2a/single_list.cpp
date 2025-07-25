#include <iostream>
#include <string>

#include "single_list.h"

using namespace std;


//////////////////////////////////////////////
// CAUTION: DO NOT CHANGE INCLUDED HEADERS  //
//////////////////////////////////////////////


/* Our singly linked lists have one header elements: the "head" which
   points the first element. The "next" link of the back header is
   NULL. 
   An empty list looks like this:

                  
          HEAD ---> NULL 
                  

   A list with two elements in it looks like this:
   
                   +-------+    +-------+
          HEAD --->|   1   |--->|   2   |--->NULL
                   +-------+    +-------+

   You should not change the name, input arguments, and
   input/output data types of existing functions. */



/*** COMPLETE FUNCTIONS BELOW ***/

/* SINGLY LINKED LIST */

/* Initializes LIST as an empty list with a head. */
single_list::single_list()
{
  /*** MODIFY HERE ***/
    head = NULL;
}

single_list::~single_list()
{
  /*** MODIFY HERE ***/
    while(!list_empty()) list_remove(head);
}

int
single_list::list_get_data1(list_elem *elem)
{
  /*** MODIFY HERE ***/
    return elem->data1;
}

int
single_list::list_get_data2(list_elem *elem)
{
  /*** MODIFY HERE ***/
    return elem->data2;
}

string
single_list::list_get_data3(list_elem *elem)
{
  /*** MODIFY HERE ***/
    return elem->data3;
}


/* Returns the element after ELEM in its list. */
list_elem *
single_list::list_next (list_elem *elem)
{
  /*** MODIFY HERE ***/
    return elem->next;
}


/* Returns LIST's head. */
list_elem *
single_list::list_head (void)
{
  /*** MODIFY HERE ***/
    return head;
}

/* Insert ELEM at the beginning of LIST, so that it becomes the head 
   in LIST. */
void 
single_list::list_insert_front (list_elem *elem)
{
    /*** MODIFY HERE ***/
    elem->next = head;
    head = elem;
}

/* Insert ELEM just before BEFORE, which may be either an interior
 element or a head. */
void 
single_list::list_insert_before (list_elem *before, list_elem *elem)
{
  /*** MODIFY HERE ***/
    if(before == NULL) return;
    // head 
    if(before == head) 
    {
        list_insert_front(elem);
        return;
    }
    // interior
    list_elem* flag1 = head;
    list_elem* flag2 = head;
    while(flag1 != before)
    {
        flag2 = flag1;
        flag1 = flag1->next;
    }
    flag2->next = elem;
    elem->next = flag1;
}

/* Insert ELEM just after AFTER, which may be either an interior
 element or a head. */
void 
single_list::list_insert_after (list_elem *after, list_elem *elem)
{
  /*** MODIFY HERE ***/
    if(after == NULL) return;
    elem->next = after->next;
    after->next = elem;
}

/* Replace FROM with TO and deconstruct FROM */
void 
single_list::list_replace (list_elem *from, list_elem *to)
{
  /*** MODIFY HERE ***/
    list_insert_before(from,to);
    to->next = from->next;
    delete from;
}


/* Removes ELEM from its list and deconstructs it. */
void
single_list::list_remove (list_elem *elem)
{
  /*** MODIFY HERE ***/
    // head
    if(elem = head)
    {
        list_elem* tmp = head;
        head = head->next;
        delete tmp;
        return;
    }
    // interior
    list_elem* flag1 = head;
    list_elem* flag2 = head;
    while(flag1 != elem)
    {
        flag2 = flag1;
        flag1 = flag1->next;
    }
    flag2->next = flag1->next;
    delete flag1;
}

/* Returns true if LIST is empty, false otherwise. */
bool 
single_list::list_empty (void)
{
  /*** MODIFY HERE ***/
    return head == NULL;
}


