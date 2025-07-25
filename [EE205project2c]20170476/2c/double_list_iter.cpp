#include <iostream>
#include <string>

#include "double_list_iter.h"

using namespace std;

//////////////////////////////////////////////
// YOU CAN CHANGE INCLUDED HEADERS ^0^ //
//////////////////////////////////////////////

/* Our doubly linked lists have two header elements: the "head"
   just before the first element and the "tail" just after the
   last element. The "prev" link of the front header is null, as
   is the "next" link of the back header. Their other two links
   point toward each other via the interior elements of the list.

   An empty list looks like this:

                      +------+     +------+
                  <---| head |<--->| tail |--->
                      +------+     +------+

   A list with two elements in it looks like this:

        +------+     +-------+     +-------+     +------+
    <---| head |<--->|   1   |<--->|   2   |<--->| tail |<--->
        +------+     +-------+     +-------+     +------+

   The symmetry of this arrangement eliminates lots of special
   cases in list processing. That's a lot simpler than the code 
   would be without header elements.

   (Because only one of the pointers in each header element is used,
   we could in fact combine them into a single header element
   without sacrificing this simplicity.  But using two separate
   elements allows us to do a little bit of checking on some
   operations, which can be valuable.) 

   You SHOULD NOT change the name, input arguments, and
   input/output data types of existing functions. */

double_list::double_list()
{
    head = new d_list_elem;
    tail = new d_list_elem;
    head->next = tail;
    head->prev = NULL;
    tail->next = NULL;
    tail->prev = head;
}

double_list::~double_list()
{
    while(!list_empty()) list_remove(head->next);
    delete head;
    delete tail;
}

int
double_list::get_data1(d_list_elem* elem)
{
    return elem->data1;
}

int
double_list::get_data2(d_list_elem* elem)
{
    return elem->data2;
}

string
double_list::get_data3(d_list_elem* elem)
{
    return elem->data3;
}

d_list_elem*
double_list::list_next(d_list_elem* elem)
{
    return elem->next;
}

d_list_elem*
double_list::list_head()
{
    return head;
}

d_list_elem*
double_list::list_tail()
{
    return tail;
}

void
double_list::insert_front(d_list_elem* elem)
{
    elem->prev = head;
    elem->next = head->next;
    (head->next)->prev = elem;
    head->next = elem;
}

void
double_list::insert_before(d_list_elem* before, d_list_elem* elem)
{
    if(before == head) return;
    elem->prev = before->prev;
    elem->next = before;
    (before->prev)->next = elem;
    before->prev = elem;
}

void
double_list::insert_after(d_list_elem* after, d_list_elem* elem)
{
    if(after == tail) return;
    elem->prev = after;
    elem->next = after->next;
    (after->next)->prev = elem;
    after->next = elem;
}

void
double_list::list_replace(d_list_elem* from, d_list_elem* to)
{
    to->prev = from->prev;
    to->next = from->next;
    (from->prev)->next = to;
    (from->next)->prev = to;
    delete from;
}

void
double_list::list_remove(d_list_elem* elem)
{
    if(elem == head || elem == tail) return;
    if(elem->prev == NULL && elem->next == NULL) return;
    (elem->prev)->next = elem->next;
    (elem->next)->prev = elem->prev;
    delete elem;
}

bool
double_list::list_empty(void)
{
    return head->next == tail;
}

int
double_list::Iter::operator*()
{
    return node->data1;
}

bool
double_list::Iter::operator==(const Iter& p) const
{
    return node == p.node;
}

bool
double_list::Iter::operator!=(const Iter& p) const
{
    return node != p.node;
}


double_list::Iter&
double_list::Iter::operator++(void)
{
    node = node->next;
    return *this;
}

double_list::Iter&
double_list::Iter::operator--(void)
{
    node = node->prev;
    return *this;
}

double_list::Iter
double_list::begin(void)
{
    return Iter(head->next);
}

double_list::Iter
double_list::end(void)
{
    return Iter(tail);
} 


