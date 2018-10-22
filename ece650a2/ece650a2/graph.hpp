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
    bool visited;
    //use template to allow different value?
    Vertex* path;//the previous node to the src
    std::vector<Vertex*> adjacentVs;
public:
    Vertex();
    Vertex(int idx, int dist = INF, bool visited = false, Vertex* path = nullptr);
    ~Vertex();
    friend class Graph;
};

class Graph{
public:
    Graph();
    Graph(int r);
    Graph(const std::string& v_cmd, const std::string& e_cmd);//generate a list of vertex
    void Reset();
    bool BFS(int headVer);
    void PrintPath(int src, int dst);
    void GetS(const std::string& s_cmd, int& src, int& dst);
    ~Graph();
    
private:
    int verticesNum;
    std::vector<Vertex*> graph;

};

#endif /* graph_hpp */
