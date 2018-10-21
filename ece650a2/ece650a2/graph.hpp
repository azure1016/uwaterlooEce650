//
//  graph.hpp
//  ece650a2
//

#ifndef graph_hpp
#define graph_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
const int INF = 1000;
class Vertex{
private:
    //do I have to use unsigned int?
    int idx;
    int dist;
    //use template to allow different value?
    Vertex* next;//use a int * maybe better?
    Vertex* path;//the previous node to the src
    std::vector<Vertex*> adjacentVs;
public:
    Vertex();
    //Vertex(int idx);
    Vertex(int idx, int dist = INF, Vertex* next = nullptr);
    ~Vertex();
    void Insert(int inx);
    void Insert(Vertex *new_v);
    friend class Graph;
};

class Graph{
public:
    //Graph();
    Graph(int r);
    Graph(const std::string& v_cmd, const std::string& e_cmd);//generate a list of vertex
    Vertex* FirstAdjVertex(int idx);
    void Reset();
    bool BFS(int headVer);
    void PrintPath(int src, int dst);
    ~Graph();
    
private:
    int verticesNum;
    //Vertex* graph; //point to a list of vertex, need dynamic allocating?
    std::vector<Vertex> graph;
    //bool* visited; // point to an array
    std::vector<bool> visited;
    //List<int> shortestPath;
};

#endif /* graph_hpp */
