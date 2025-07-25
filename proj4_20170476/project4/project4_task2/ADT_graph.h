#ifndef __ADT_GRAPH_H__
#define __ADT_GRAPH_H__

#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <limits>

enum {PLUS_INFINITY = std::numeric_limits<int>::max()};

using namespace std;

template <class T> class ADT_Incidence;
template <class T> class ADT_Edge;

/* ADT Node */
template <class T>
class ADT_Node {
	public:
		/* function */
		string get_node_name(void); 
		T get_node_value(void);
            bool get_visit(void);
            void set_visit(bool);
		int add_incidence(void); 
		int remove_incidence(void); 
		int add_nodelist_info(typename list<ADT_Node<T>*>::iterator node_position);
            void set_node_value(T);
            ADT_Node<T>* get_parent(void);
            void set_parent(ADT_Node<T>*);
 
		int erase_edge_from_incidence(ADT_Edge<T>* edge);
		typename list<ADT_Edge<T>*>::iterator get_begin(void);
		typename list<ADT_Edge<T>*>::iterator get_end(void);

		typename list<ADT_Edge<T>*>::iterator add_incidence_list(ADT_Edge<T> *);
		list<ADT_Edge<T>*> incidentEdges(void);
		int isAdjacentTo(string node_name);
		ADT_Node(string node_name, T node_value); 

	private:
		/* variable */
		string node_name;
		T node_value;
		ADT_Incidence<T> *incidence;
		typename list<ADT_Node<T>*>::iterator node_position;
            ADT_Node<T>* parent = NULL;
            bool visit = false;

};

template <class T>
class myComparator
{
    public:
        bool operator() (ADT_Node<T>* a, ADT_Node<T>* b)
        {
            return (a->get_node_value()) > (b->get_node_value());
        }
};

/* Incidence Collection */
template <class T>
class ADT_Incidence { 
	public:
		/* function */
		typename list<ADT_Edge<T>*>::iterator add_incidence_list(ADT_Edge<T>* edge);
		int remove_incidence_list(ADT_Edge<T> * edge);
		typename list<ADT_Edge<T>*>::iterator get_begin(void);
		typename list<ADT_Edge<T>*>::iterator get_end(void);
		int isAdjacentTo(string node_name);
		list<ADT_Edge<T>*> incidentEdges(void);
	private:
		/* variable */
		list<ADT_Edge<T>*> incidence_list; 
};

/* ADT Edge */
template <class T>
class ADT_Edge { 
	public:
            
		/* function */
		string get_edge_name(void);
		T get_edge_value(void);
		ADT_Node<T> get_first_node(void);
		ADT_Node<T> get_second_node(void);
            ADT_Node<T>* get_first(void);
            ADT_Node<T>* get_second(void);
		int add_incidence_info(typename list<ADT_Edge<T>*>::iterator first_incidence_position, typename list<ADT_Edge<T>*>::iterator second_incidence_position);
		int add_edgelist_info(typename list<ADT_Edge<T>*>::iterator edge_position);
		list<ADT_Node<T>*> endVertices(void) ;
		string opposite(string node_name) ;
		int isAdjacentTo(string edge_name) ;
		int isIncidentOn(string node_name) ;
		ADT_Edge(string edge_name, T edge_value, ADT_Node<T> *first_node, ADT_Node<T> *second_node); 
		
	private:
		/* variable */
		string edge_name;
		T edge_value;
		typename list<ADT_Edge<T>*>::iterator first_incidence_position;
		typename list<ADT_Edge<T>*>::iterator second_incidence_position;
		typename list<ADT_Edge<T>*>::iterator edge_position;

		ADT_Node<T> *first_node;
		ADT_Node<T> *second_node;
};


template <class T>
class myComparator_mst
{
    public:
        bool operator() (ADT_Edge<T>* a, ADT_Edge<T>* b)
        {
            if(a->get_edge_value() == b->get_edge_value())
            {
                return (a->get_first_node().get_node_name()) > (a->get_second_node().get_node_name());
            }
            return (a->get_edge_value()) > (b->get_edge_value());
        }
};


/* ADT Nodelist */
template <class T>
class ADT_Nodelist {
	public:
		/* function	 */
		typename list<ADT_Node<T>*>::iterator add_node_list(ADT_Node<T>* vertex);
		int remove_node_list(ADT_Node<T>* vertex);
		ADT_Node<T>* search_vertex(string vertex);
		int	print_all_vertices(void);
		list<ADT_Node<T>*> get_node_list(void);

	private: 
		/* variable */
		list<ADT_Node<T>*> node_list;
		typename list<ADT_Node<T>*>::iterator node_iter;
};

/* ADT Edgelist */
template <class T>
class ADT_Edgelist {
	public:
		typename list<ADT_Edge<T>*>::iterator add_edge_list(ADT_Edge<T>* edge);
		int remove_edge_list(ADT_Edge<T> *edge);
		ADT_Edge<T>* search_edge(string edge);
		int	print_all_edges(void);
		list<ADT_Edge<T>*> get_edge_list(void);

	private: 
		/* variable */
		list<ADT_Edge<T>*> edge_list;
		typename list<ADT_Edge<T>*>::iterator edge_iter;
};

/* ADT Graph */
template <class T>
class ADT_Graph {
	public:
		int vertices(void);
		int edges(void);
		int insertVertex(string node_name, T node_value);
		int insertEdge(string vertex_name1, string vertex_name2, string edge_name, T edge_value);
		int eraseVertex(string node_name);
		int eraseEdge(string edge_name);
		int eraseEdge(ADT_Edge<T> *edge);
		ADT_Nodelist<T> get_ADT_nodelist(void);
		ADT_Edgelist<T> get_ADT_edgelist(void);
		ADT_Graph(string graph_name);
            static int vertex_count;
            static int edge_count;
	private:
		string graph_name;
		ADT_Nodelist<T> *ADT_nodelist;
		ADT_Edgelist<T> *ADT_edgelist;


};

template <class T>
class mySet
{
    private:
        vector<pair<int, ADT_Node<T>*>> parent;
        vector<int> rank;
    public:
        mySet(ADT_Graph<T>*);
        int find(ADT_Node<T>*) const;
        void set_union(int, int);
};

template <class T>
mySet<T>::mySet(ADT_Graph<T>* graph)
{
    list<ADT_Node<T>*> nodelist = graph->get_ADT_nodelist().get_node_list();
    typename list<ADT_Node<T>*>::iterator it_vertex = nodelist.begin();
    for(int i = 0; i < graph->vertex_count; i++, it_vertex++)
    {
        parent.push_back(make_pair(i, *it_vertex));
        rank.push_back(0);
    }
}

template <class T>
int
mySet<T>::find(ADT_Node<T>* node) const
{
    int i;
    for(i = 0; i < parent.size(); i++)
    {
        if(node == parent[i].second)break;
    }
    if(i == parent.size()) return -1;

    if(parent[i].first == i) return i;
    return find(parent[parent[i].first].second);
}

template <class T>
void
mySet<T>::set_union(int subset_num1, int subset_num2)
{
    if(subset_num1 == subset_num2) return;
    if(rank[subset_num1] > rank[subset_num2])
    {
        parent[subset_num2].first = subset_num1;
    }
    else
    {
        parent[subset_num1].first = subset_num2;
    }
    if(rank[subset_num1] == rank[subset_num2])
    {
        rank[subset_num2]++;
    }
}


#endif /* __ADT_GRAPH_H__ */
