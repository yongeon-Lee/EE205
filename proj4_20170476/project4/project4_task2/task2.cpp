#include "ADT_graph.h"

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>

using namespace std;


void update (priority_queue <ADT_Node<int>*, vector<ADT_Node<int>*>, myComparator<int>> &pq)
{
    vector<ADT_Node<int>*> replace;
    while(!pq.empty())
    {
        replace.push_back(pq.top());
        pq.pop();
    }
    for(int i = 0; i < replace.size(); i++)
    {
        pq.push(replace[i]);
    }
}

void print_path(ADT_Node<int>* dst, ofstream& out)
{
    // base case
    if(dst->get_parent() == NULL) 
    {
        out << dst->get_node_name() << " ";
        return;
    }
    // recursively go to source vertex
    print_path(dst->get_parent(), out);
    // print
    out << dst->get_node_name() << " ";
}

void shortestpath(ADT_Graph<int>* graph, string src, string dst, ofstream& out)
{
    /* initialize */
    priority_queue <ADT_Node<int>*, vector<ADT_Node<int>*>, myComparator<int>> pq;
    list<ADT_Node<int>*> nodelist = graph->get_ADT_nodelist().get_node_list();
    list<ADT_Node<int>*>::iterator it = nodelist.begin();
    int i = 0;
    for(; it != nodelist.end(); it++)
    {
        string node_name = (*it)->get_node_name();
        if(node_name == src) (*it)->set_node_value(0);
        else (*it)->set_node_value(PLUS_INFINITY);
        (*it)->set_visit(false);
        (*it)->set_parent(NULL); 
        pq.push(*it);
    }
    /* run program while priority queue is empty */
    while(!pq.empty())
    {
        /* remove the minimum priority */
        ADT_Node<int>* target = pq.top();
        target->set_visit(true);
        /* search all of the incident vertex value of the certain vertex */
        list<ADT_Edge<int>*> incidence = target->incidentEdges();
        list<ADT_Edge<int>*>::iterator it1 = incidence.begin();
        int distance;
        for(; it1 != incidence.end(); it1++)
        {
            string opposite = (*it1)->opposite(target->get_node_name());
            //get opposite node
            string first = (*it1)->get_first_node().get_node_name();
            string second = (*it1)->get_second_node().get_node_name();
            if(first == opposite)
            {
                ADT_Node<int>* adjacent1 = (*it1)->get_first();
                distance = (*it1)->get_edge_value() + target->get_node_value(); 
                if((adjacent1->get_node_value() > distance) && (adjacent1->get_visit() == false))
                {
                    adjacent1->set_node_value(distance);
                    adjacent1->set_parent(target);
                }

            }
            else if(second == opposite)
            {
                ADT_Node<int>* adjacent2 = (*it1)->get_second();
                distance = (*it1)->get_edge_value() + target->get_node_value();
                if((adjacent2->get_node_value() > distance) && (adjacent2->get_visit() == false))
                {
                    adjacent2->set_node_value(distance);
                    adjacent2->set_parent(target);
                }
            }
        }
        if(target->get_node_name() == dst) break;
        pq.pop();
        update(pq);
    }
    if(pq.top()->get_parent() == NULL)
        out << "There is no path from " << src << " to " << dst << endl;
    else
    {
        print_path(pq.top(), out);
        out << pq.top()->get_node_value() << endl;
    }

}



void mst(ADT_Graph<int>* graph, ofstream& out)
{
    priority_queue <ADT_Edge<int>*, vector<ADT_Edge<int>*>, myComparator_mst<int>> pq_;
    list<ADT_Edge<int>*> edgelist = graph->get_ADT_edgelist().get_edge_list();
    list<ADT_Edge<int>*>::iterator it_edge = edgelist.begin();
    for(; it_edge != edgelist.end();it_edge++)
    {
        pq_.push(*it_edge);
    }
    mySet<int> vertex_set(graph);
    int edges = 0;
    while(!pq_.empty())
    {
        ADT_Edge<int>* target_edge = pq_.top();
        pq_.pop();
        list<ADT_Node<int>*> end_vertex = target_edge->endVertices();
        ADT_Node<int>* first_vertex = end_vertex.front();
        ADT_Node<int>* second_vertex = end_vertex.back();
        int a = vertex_set.find(first_vertex);
        int b = vertex_set.find(second_vertex);
        if(a != b)
        {
            vertex_set.set_union(a, b);
            edges++;
            if(first_vertex->get_node_name() < second_vertex->get_node_name())
                out << first_vertex->get_node_name() << " " << second_vertex->get_node_name() << " " << target_edge->get_edge_value() << endl;
            else
                out << second_vertex->get_node_name() << " " << first_vertex->get_node_name() << " " << target_edge->get_edge_value() << endl;
        }
    }

}


int main(int argc, char* argv[])
{
    ifstream inFile;
    inFile.open(argv[1]);
    string word1, word2;
    int word3;
    string line;
    ADT_Graph<int> *task2_graph = new ADT_Graph<int>("task2");
    // read Node
    while(getline(inFile, line))
    {
        if(line == "Node") continue;
        if(line == "\0") break;
        task2_graph->insertVertex(line, 0);
    }
    // read Edge
    while(getline(inFile, line))
    {
        if(line == "Edge") continue;
        istringstream iss(line);
        while(iss >> word1 >> word2 >> word3)
        {
            task2_graph->insertEdge(word1, word2, word1+word2, word3);
        }
    }
    ifstream inFile_short;
    string line_short;
    string src, dst;
    inFile_short.open(argv[2]);
    ofstream outFile1;
    outFile1.open(argv[3]);
    while(getline(inFile_short, line_short))
    {
        istringstream iss_short(line_short);
        while(iss_short >> src >> dst)
        {
            shortestpath(task2_graph, src, dst, outFile1);
        }
    }
    outFile1.close();
    ofstream outFile2;
    outFile2.open(argv[4]);
    mst(task2_graph, outFile2);
    outFile2.close();
    return 0;
}


