//
//  graph.hpp
//  ece650a2
//

#ifndef graph_hpp
#define graph_hpp

#include <stdio.h>
#include <iostream>

class Vertex{
private:
    //do I have to use unsigned int?
    int idx;
    //use template to allow different value?
    Vertex* next;

public:
    Vertex();
    Vertex(int idx, Vertex* next);
    ~Vertex();
    void Insert(int inx);
    void Insert(Vertex *new_v);
    friend class Graph;
};

class Graph{
public:
    Graph(int r);
    Graph(const std::string& v_cmd, const std::string& e_cmd);//generate a list of vertex
    Vertex* FirstAdjVertex(int idx);
    
    bool BFS(int headVer);
    ~Graph();
    
private:
    int verticesNum;
    Vertex* graph; //point to a list of vertex, need dynamic allocating?
    bool* visited; // point to an array
};

#endif /* graph_hpp */
