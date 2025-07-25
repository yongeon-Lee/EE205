/*
 * Skeleton code for project 4 in EE205 2018 FALL KAIST
 * Created by Joonki Hong
 */

#include "ADT_graph.h"
#include <iostream>

using namespace std;

/*
 * Tips!!!!
 *
 * 1. Search 'YOUR CODE GOES HERE' to find where to implement.
 * 2. Use commented Debug to get the insight of adjacency list structure.
 * 3. You can compile this file by 'g++ -c ADT_graph.cpp'.
 * 4. You can compile with main.cpp by 'g++ main.cpp ADT_graph.cpp' after you fill the blanks.
 */


/*
 * I know that this prokcet is a little bit tough, but I beleive you can do this!!!
 * Feel free to ask TA!!!
 */


    // _    ____ _____   _   _           _
   // / \  |  _ \_   _| | \ | | ___   __| | ___
  // / _ \ | | | || |   |  \| |/ _ \ / _` |/ _ \
 // / ___ \| |_| || |   | |\  | (_) | (_| |  __/
// /_/   \_\____/ |_|___|_| \_|\___/ \__,_|\___|
                // |_____|

/*************************** ADT_Node ***************************/

/* Get node name */
template <class T>
string ADT_Node<T>::get_node_name(void) {
	return node_name;
}

/* Get node value */
template <class T>
T ADT_Node<T>::get_node_value(void) {
	return node_value;
}
template <class T>
bool
ADT_Node<T>::get_visit(void)
{
    return visit;
}

template<class T>
void
ADT_Node<T>::set_visit(bool visit)
{
    this->visit = visit;
}
template <class T>
ADT_Node<T>*
ADT_Node<T>::get_parent(void)
{
    return parent;
}

template <class T>
void
ADT_Node<T>::set_parent(ADT_Node<T>* parent)
{
    this->parent = parent;
}
template <class T>
void ADT_Node<T>::set_node_value(T node_value)
{
    this->node_value = node_value;
}

/* Add new incidence collection */
template <class T>
int ADT_Node<T>::add_incidence(void){
	incidence = new ADT_Incidence<T>;
	return 1;
}

/* Remove incidence */
template <class T>
int ADT_Node<T>::remove_incidence(void){
	delete incidence;
	return 1;
}

/* erase one edge from incidence list */
template <class T>
int ADT_Node<T>::erase_edge_from_incidence(ADT_Edge<T>* edge) {
	incidence->remove_incidence_list(edge);
	return 1;
}

/* return the begining of incidence list */
template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Node<T>::get_begin(void){
	return incidence->get_begin();
}

/* return the end of incidence list */
template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Node<T>::get_end(void){
	return incidence->get_end();
}

/* Call add_incidence_list in incidence collection */
template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Node<T>::add_incidence_list(ADT_Edge<T>* edge){
	return incidence->add_incidence_list(edge);
}

/* Save the node position information */
template <class T>
int ADT_Node<T>::add_nodelist_info(typename list<ADT_Node<T>*>::iterator node_position){
	this->node_position = node_position;
	return 1;
}

/* Basic functionality of ADT_Node */
template <class T>
list<ADT_Edge<T>*> ADT_Node<T>::incidentEdges(void) {
	/* use incidentEdges in incidence list */
	/*
	 * YOUR CODE GOES HERE
	 */
    return (this->incidence)->incidentEdges();
}

template <class T>
int ADT_Node<T>::isAdjacentTo(string node_name) {
	/* use isAdjacentTo() function in incidence list	 */

	/*
	 * YOUR CODE GOES HERE
	 */
    return (this->incidence)->isAdjacentTo(node_name);
}

/* Constructor, initializing the node name and the node value, add new incidence collcetion*/
template <class T>
ADT_Node<T>::ADT_Node(string node_name, T node_value) {

	this->node_name = node_name;
	this->node_value = node_value;
	add_incidence();
	/* Debug */
	/* cout << "Test2: node name "<< get_node_name()<<", node_value "<<get_node_value() <<endl << endl; */
}

 // ___            _     _
// |_ _|_ __   ___(_) __| | ___ _ __   ___ ___
 // | || '_ \ / __| |/ _` |/ _ \ '_ \ / __/ _ \
 // | || | | | (__| | (_| |  __/ | | | (_|  __/
// |___|_| |_|\___|_|\__,_|\___|_| |_|\___\___|

           // _ _           _   _
  // ___ ___ | | | ___  ___| |_(_) ___  _ __
 // / __/ _ \| | |/ _ \/ __| __| |/ _ \| '_ \
// | (_| (_) | | |  __/ (__| |_| | (_) | | | |
 // \___\___/|_|_|\___|\___|\__|_|\___/|_| |_|

/*************************** Incidence Collection ***************************/

/* Add new edge connection in the incidence collection */
template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Incidence<T>::add_incidence_list(ADT_Edge<T>* edge) {
	return incidence_list.insert(incidence_list.end(), edge); // pointer will be replaced later
}

/* Remove an edge connection in the incidence collection */
template <class T>
int ADT_Incidence<T>::remove_incidence_list(ADT_Edge<T>* edge) {
	incidence_list.remove(edge);
	return 1;
}

template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Incidence<T>::get_begin(void){
	return incidence_list.begin();
}

template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Incidence<T>::get_end(void){
	return incidence_list.end();
}


template <class T>
int ADT_Incidence<T>::isAdjacentTo(string node_name) {
	/* check through incidence list for input node_name  */
	/* return 1 if you find it return 0 if you don't find it  */
        
	/*
	 * YOUR CODE GOES HERE
	 */
    typename list<ADT_Edge<T>*>::iterator it;
    for(it = get_begin(); it != get_end(); it++)
    {
        ADT_Node<T> node_1 = (*it)->get_first_node();
        string node_1_name = node_1.get_node_name();
        ADT_Node<T> node_2 = (*it)->get_second_node();
        string node_2_name = node_2.get_node_name();
        if(node_name == node_1_name || node_name == node_2_name) return 1;
    }
    return 0;
}

template <class T>
list<ADT_Edge<T>*> ADT_Incidence<T>::incidentEdges(void) {
	/* return list of incident edges */
	/*
	 * YOUR CODE GOES HERE
	 */
    return this->incidence_list;
}



    // _    ____ _____   _____    _
   // / \  |  _ \_   _| | ____|__| | __ _  ___
  // / _ \ | | | || |   |  _| / _` |/ _` |/ _ \
 // / ___ \| |_| || |   | |__| (_| | (_| |  __/
// /_/   \_\____/ |_|___|_____\__,_|\__, |\___|
                // |_____|          |___/
/*************************** ADT_Edge ***************************/

/* Get edge name */
template <class T>
string ADT_Edge<T>::get_edge_name(void) {
	return edge_name;
}

/* Get edge value */
template <class T>
T ADT_Edge<T>::get_edge_value(void) {
	return edge_value;
}

/* Get first node */
template <class T>
ADT_Node<T> ADT_Edge<T>::get_first_node(void) {
	return *first_node;
}


/* Get second node */
template <class T>
ADT_Node<T> ADT_Edge<T>::get_second_node(void) {
	return *second_node;
}
template <class T>
ADT_Node<T>*
ADT_Edge<T>::get_first(void)
{
    return first_node;
}

template <class T>
ADT_Node<T>*
ADT_Edge<T>::get_second(void)
{
    return second_node;
}
/* Save pointer to the incidence collection of the first vertex and the second vertex */
template <class T>
int ADT_Edge<T>::add_incidence_info(typename list<ADT_Edge<T>*>::iterator first_incidence_position, typename list<ADT_Edge<T>*>::iterator second_incidence_position) {
	this->first_incidence_position = first_incidence_position;
	this->second_incidence_position = second_incidence_position;
	return 1;
}

/* Save the edge position information */
template <class T>
int ADT_Edge<T>::add_edgelist_info(typename list<ADT_Edge<T>*>::iterator edge_position) {
	this->edge_position = edge_position;
	return 1;
}

template <class T>
list<ADT_Node<T>*> ADT_Edge<T>::endVertices(void) {
	/* return a list that have pointer to the first node and second node of the edge */
    list<ADT_Node<T>*> node_list;
    node_list.push_back(first_node);
    node_list.push_back(second_node);
    return node_list;
	/*
	 * YOUR CODE GOES HERE
	 */
}


template <class T>
string ADT_Edge<T>::opposite(string node_name) {
	/* return the opposite node of given vertex in string */
	/* if given vertex is not included in this edge return 0 */
	/* e.g. for edge A-B, given A, return B */
	/* e.g. for edge A-B, given C, return 0 */

	/*
	 * YOUR CODE GOES HERE
	 */
   ADT_Node<T>* node_1 = first_node;
   ADT_Node<T>* node_2 = second_node;
   string name1 = node_1->get_node_name();
   string name2 = node_2->get_node_name();
   if(node_name == name1) return name2;
   else if(node_name == name2) return name1;
   else return 0;
}


template <class T>
int ADT_Edge<T>::isAdjacentTo(string edge_name) {
	/* check that the given edge is adjacent with first end node */
	/* check that the given edge is adjacent with second end node */
	/* return 1 if it is adjacent return 0 if not */

	/*
	 * YOUR CODE GOES HERE
	 */
    ADT_Node<T>* first_node = this->first_node;
    ADT_Node<T>* second_node = this->second_node;
    list<ADT_Edge<T>*> first_incidence = first_node->incidentEdges();
    list<ADT_Edge<T>*> second_incidence = second_node->incidentEdges();
    typename list<ADT_Edge<T>*>::iterator it1 = first_node->get_begin();
    typename list<ADT_Edge<T>*>::iterator it2 = second_node->get_begin();
    // check first end node 
    for(; it1 != first_node->get_end(); it1++)
    {
        string cmp_edge = (*it1)->get_edge_name();
        if(cmp_edge == edge_name) return 1;
    }
    // check second end node
    for(; it2 != second_node->get_end(); it2++)
    {
        string cmp_edge = (*it2)->get_edge_name();
        if(cmp_edge == edge_name) return 1;
    }

    return 0;

}


template <class T>
int ADT_Edge<T>::isIncidentOn(string node_name) {
	/* return 1 if given node is incident, return 0 if not  */
	/* check the first end node and the second end node  */
    string name1 = first_node->get_node_name();
    string name2 = second_node->get_node_name();
    if(node_name == name1 || node_name == name2) return 1;
    else return 0;
	/*
	 * YOUR CODE GOES HERE
	 */
}


/* Constuctor, initializing edge name, edge value, and vertex name */
template <class T>
ADT_Edge<T>::ADT_Edge(string edge_name, T edge_value, ADT_Node<T> *first_node, ADT_Node<T> *second_node) {

	list<ADT_Edge<T>*> temp_list;

	this->edge_name = edge_name;
	this->edge_value = edge_value;
	this->first_node = first_node;
	this->second_node = second_node;

	/* Debug */
	/* cout << "Test5: edge name "<< get_edge_name() <<", edge value " <<get_edge_value() << endl <<endl; */
}


    // _    ____ _____   _   _           _      _ _     _
   // / \  |  _ \_   _| | \ | | ___   __| | ___| (_)___| |_
  // / _ \ | | | || |   |  \| |/ _ \ / _` |/ _ \ | / __| __|
 // / ___ \| |_| || |   | |\  | (_) | (_| |  __/ | \__ \ |_
// /_/   \_\____/ |_|___|_| \_|\___/ \__,_|\___|_|_|___/\__|
                // |_____|
/*************************** ADT_Nodelist ***************************/

/* Add new node in the nodelist */
template <class T>
typename list<ADT_Node<T>*>::iterator ADT_Nodelist<T>::add_node_list(ADT_Node<T> *vertex) {
	return node_list.insert(node_list.end(),vertex);
}

/* Remove a node in the nodelist */
template <class T>
int ADT_Nodelist<T>::remove_node_list(ADT_Node<T> *vertex) {
	node_list.remove(vertex);
	return 1;
}


template <class T>
ADT_Node<T>* ADT_Nodelist<T>::search_vertex(string vertex) {
	/* return pointer to a node that has given node name */
	/* if there is no such node, return NULL */

	/*
	 * YOUR CODE GOES HERE
	 */
    typename list<ADT_Node<T>*>::iterator it = node_list.begin();
    for(; it != node_list.end(); it++)
    {
        string search_name = (*it)->get_node_name();
        if(vertex == search_name) return (*it);
    }
    return NULL;

}

template <class T>
int	ADT_Nodelist<T>::print_all_vertices(void){
	/* print all vertices' name in the nodelist */

	/*
	 * YOUR CODE GOES HERE
	 */
    typename list<ADT_Node<T>*>::iterator it = node_list.begin();
    for(; it != node_list.end(); it++)
    {
        cout << "Node Name: " << (*it)->get_node_name() << endl;
    }
}

/* Return node list */
template <class T>
list<ADT_Node<T>*> ADT_Nodelist<T>::get_node_list(void) {
	return node_list;
}


    // _    ____ _____   _____    _            _ _     _
   // / \  |  _ \_   _| | ____|__| | __ _  ___| (_)___| |_
  // / _ \ | | | || |   |  _| / _` |/ _` |/ _ \ | / __| __|
 // / ___ \| |_| || |   | |__| (_| | (_| |  __/ | \__ \ |_
// /_/   \_\____/ |_|___|_____\__,_|\__, |\___|_|_|___/\__|
                // |_____|          |___/
/*************************** ADT_Edgelist ***************************/

/* Add new edge in the edgelist */
template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Edgelist<T>::add_edge_list(ADT_Edge<T> *edge) {
	return edge_list.insert(edge_list.end(),edge);
}

/* Remove a edge in the edgelist */
template <class T>
int ADT_Edgelist<T>::remove_edge_list(ADT_Edge<T> *edge) {
	edge_list.remove(edge);
	return 1;
}


template <class T>
ADT_Edge<T>* ADT_Edgelist<T>::search_edge(string edge) {
	/* return pointer to certain edge that has given edge name */
	/* if there is no such edge, return NULL */

	/*
	 * YOUR CODE GOES HERE
	 */
    typename list<ADT_Edge<T>*>::iterator it = edge_list.begin();
    for(; it != edge_list.end(); it++)
    {
        string search_name = (*it)->get_edge_name();
        if(search_name == edge) return (*it);
    }
    return NULL;
}

template <class T>
int	ADT_Edgelist<T>::print_all_edges(void){
	/* print all edges' name in the edgelist */

	/*
	 * YOUR CODE GOES HERE
	 */
    typename list<ADT_Edge<T>*>::iterator it = edge_list.begin();
    for(; it != edge_list.end(); it++)
    {
        cout << "Edge Name: " << (*it)->get_edge_name() << endl;
    }

}
/* Return edge list */
template <class T>
list<ADT_Edge<T>*> ADT_Edgelist<T>::get_edge_list(void) {
	return edge_list;
}


    // _    ____ _____   ____                 _
   // / \  |  _ \_   _| / ___|_ __ __ _ _ __ | |__
  // / _ \ | | | || |  | |  _| '__/ _` | '_ \| '_ \
 // / ___ \| |_| || |  | |_| | | | (_| | |_) | | | |
// /_/   \_\____/ |_|___\____|_|  \__,_| .__/|_| |_|
                // |_____|             |_|

/*************************** ADT_Graph ***************************/
template <class T>
int ADT_Graph<T>::vertex_count = 0;

template <class T>
int ADT_Graph<T>::edge_count = 0;

template <class T>
int ADT_Graph<T>::vertices(void) {
	/*
	 * YOUR CODE GOES HERE
	 */
    (this->ADT_nodelist)->print_all_vertices();
}


template <class T>
int ADT_Graph<T>::edges(void) {
	/*
	 * YOUR CODE GOES HERE
	 */
    (this->ADT_edgelist)->print_all_edges();
}


template <class T>
int ADT_Graph<T>::insertVertex(string node_name, T node_value) {

	/* 1. make new node object */
	/* 2. add new node object to nodelist */
	/* 3. add nodelist info to node object */
    
	/*
	 * YOUR CODE GOES HERE
	 */
    // make new node object
    ADT_Node<T>* n_node = new ADT_Node<T>(node_name, node_value);
    // add new node object to nodelist
    typename list<ADT_Node<T>*>::iterator new_it = ADT_nodelist->add_node_list(n_node);
    // add nodelist info to node object
    n_node->add_nodelist_info(new_it);
    vertex_count++;
	/* Debug */
	/* cout << "Test3: node iterator is working??? " << (*node_iterator)->get_node_name() << endl << endl; */

}


template <class T>
int ADT_Graph<T>::insertEdge(string vertex_name1, string vertex_name2, string edge_name, T edge_value) {

	ADT_Node<T> *first_node, *second_node;
	typename list<ADT_Edge<T>*>::iterator edge_iterator, first_edge_iterator, second_edge_iterator;

	/* 1. Find corresponding ADT_Node with vertex name */
	/* 2. Make new edge and add it to edge list */
	/* 3. Add edge to incidence collection of the first and second vertex */
	/* 4. Add reverse connection to incidence collection */
      // find correspoinding ADT_Node with vertex name
      first_node = ADT_nodelist->search_vertex(vertex_name1);
      second_node = ADT_nodelist->search_vertex(vertex_name2);
      //name new edge and add it to edge list
      ADT_Edge<T>* n_edge = new ADT_Edge<T>(edge_name, edge_value, first_node, second_node);
      edge_iterator = ADT_edgelist->add_edge_list(n_edge);
      n_edge->add_edgelist_info(edge_iterator);
      // add edge to incidence collection of the first and second vertex
      first_edge_iterator = first_node->add_incidence_list(n_edge);
      second_edge_iterator = second_node->add_incidence_list(n_edge);
      // add reverse connection to incidence collection
      n_edge->add_incidence_info(first_edge_iterator, second_edge_iterator);
      edge_count++;
	/*
	 * YOUR CODE GOES HERE
	 */

	/* Debug */
	/* cout << "Test4: search_vertex??? "<< first_node->get_node_name() <<" "<< second_node->get_node_name() << endl <<endl; */
	/* cout << "Test6: edge iterator is working ??? "<< (*edge_iterator)->get_edge_name() <<" "<< (*edge_iterator)->get_edge_value() << endl <<endl; */

	return 1;
}


template <class T>
int ADT_Graph<T>::eraseVertex(string node_name) {
	/* 1. Use search_vertex() to find corresponding node pointer */
	/* 2. Erase all edges in incidence collection */
	/* 3. Remove node from nodelist */
	/* 4. Remove node */
    ADT_Node<T>* search_node = ADT_nodelist->search_vertex(node_name);
    typename list<ADT_Edge<T>*>::iterator it = search_node->get_begin();
    ADT_Edge<T>* tmp;
    while(it != search_node->get_end())
    {
        tmp = *it;
        it++;
        eraseEdge(tmp);
    }
    search_node->remove_incidence();
    ADT_nodelist->remove_node_list(search_node);
    delete search_node;
    vertex_count--;
	/*
	 * YOUR CODE GOES HERE
	 */
}


template <class T>
int ADT_Graph<T>::eraseEdge(string edge_name) {
	/* find correstponding edge and call eraseEdge agian */
    ADT_Edge<T>* search_edge = ADT_edgelist->search_edge(edge_name);
    eraseEdge(search_edge);
    edge_count--;

	/*
	 * YOUR CODE GOES HERE
	 */
}


template <class T>
int ADT_Graph<T>::eraseEdge(ADT_Edge<T>* erase_edge) {

	/* 1. Erase edge in the first node incidence collection */
	/* 2. Erase edge in the second node incidence collection */
	/* 3. Erase edge from the edgelist */
	/* 4. Erase edge  */
    (erase_edge->get_first_node()).erase_edge_from_incidence(erase_edge);
    (erase_edge->get_second_node()).erase_edge_from_incidence(erase_edge);
    ADT_edgelist->remove_edge_list(erase_edge);
    delete erase_edge; 
	/*
	 * YOUR CODE GOES HERE
	 */
}

template <class T>
ADT_Nodelist<T> ADT_Graph<T>::get_ADT_nodelist(void) {
	return *ADT_nodelist;
}

template <class T>
ADT_Edgelist<T> ADT_Graph<T>::get_ADT_edgelist(void) {
	return *ADT_edgelist;
}

template <class T>
ADT_Graph<T>::ADT_Graph(string graph_name) {
	graph_name = graph_name;
	ADT_nodelist = new ADT_Nodelist<T>;
	ADT_edgelist = new ADT_Edgelist<T>;

	/* Debug */
	/* cout<<"Test1: graph name is "<<graph_name<<endl<<endl; */

}

template class ADT_Graph<int>;
template class ADT_Node<int>;
template class ADT_Edge<int>;
template class ADT_Edgelist<int>;
template class ADT_Nodelist<int>;






