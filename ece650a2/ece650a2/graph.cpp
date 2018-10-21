//
//  graph.cpp
//  ece650a2
//

#include "graph.hpp"
#include <regex>
#include <queue>

//#include <iostream>

bool IsBetween(int x, int upper, int lower = 0){
    if((x<=upper) & (x>=lower))
        return true;
    else return false;
}
//Graph::Graph(){}

Graph::Graph(int r):verticesNum(r){}

Graph::Graph(const std::string& v_cmd, const std::string& e_cmd){
    std::smatch m_v;
    
    std::regex re_v("V\\s(\\d+)");
    std::regex re_e("E\\s\\{(<(\\d+),(\\d+)>,*)+\\}");
    std::regex re_coor("<(\\d+),(\\d+)>");
    std::sregex_iterator it_e(e_cmd.cbegin(),e_cmd.cend(),re_coor);
    std::sregex_iterator end;
    bool isValidV = std::regex_search(v_cmd,m_v,re_v);
    bool isValidE = std::regex_search(e_cmd,re_e);
    if(isValidV){
        this->verticesNum = stoi(m_v[1]);
        for(int i = 0; i < verticesNum; i++){
            //graph[i] = Vertex(i);
//            graph[i].idx = i;
//            graph[i].dist = INF;
//            graph[i].next = nullptr;
            visited[i] = false;
        }
        if(isValidE){
            for( ; it_e != end; it_e++){
                int v_src = stoi(it_e->str(1));
                int v_dst = stoi(it_e->str(2));
                if(IsBetween(v_src, verticesNum) && IsBetween(v_dst,verticesNum)){
                    Vertex src = Vertex(v_src);
                    Vertex dst = Vertex(v_dst);
                    src.adjacentVs.push_back(&dst);
                    dst.adjacentVs.push_back(&src);
                    graph.push_back(src);
                    graph.push_back(dst);
                    //graph[v_src].Insert(&graph[v_dst]);
                    //graph[v_dst].Insert(&graph[v_src]);
                }
            }
        }
        
    }
}

Vertex* Graph::FirstAdjVertex(int idx){
    for(Vertex* j = this->graph[idx].next; j != NULL; j = j->next){
        if(visited[j->idx] == false)
            return j;
        else continue;
    }
    return 0;
}

void Graph::Reset(){
    for(int i = 0; i < verticesNum; i++){
        visited[i] = false;
        graph[i].dist = INF;
        graph[i].path = nullptr;
    }
}

bool Graph::BFS(int headVer){
    Reset();
    graph[headVer].dist = 0;
    std::queue<Vertex*> pa;
    pa.push(&graph[headVer]);
    visited[headVer] = true;
    Vertex* tmp = nullptr;
    while(!pa.empty()){
        tmp = pa.front();
        pa.pop();
        if(tmp->next != nullptr){
            Vertex* n = &graph[tmp->next->idx];
            while((n != nullptr) && !visited[n->idx]){
                visited[n->idx] = true;
                pa.push(n);
                if(n->dist == INF){
                    n->dist = tmp->dist + 1;
                    n->path = tmp;
                }
                n = n->next;
            }
        }
    }
    
    return true;
}

void Graph::PrintPath(int src, int dst){
    BFS(src);
    Vertex* n = graph[dst].path;
    if(n != nullptr){
        PrintPath(n->idx, dst);
    }
    std::cout<<dst<<std::endl;
}


Graph::~Graph(){
    //delete graph;
    //if(graph != NULL){
        int len = sizeof(graph)/sizeof(graph[0]);
        for(int i = 0; i < len; i++){
//            while(graph[i]){
//                Vertex* n = graph[i].next;
//            }
            Vertex* p = &graph[i];
            while(p){
                Vertex* n = p->next;
                delete p;
                p = n;
            }
        }
    //}
    //delete graph;
    //graph = nullptr;
}

Vertex::Vertex(){}

//Vertex::Vertex(int idx){
//    idx = idx;
//    dist = INF;
//    next = nullptr;
//    path = nullptr;
//}

Vertex::Vertex(int idx, int dist, Vertex* next){
    this->idx = idx;
    this->dist = dist;
    this->next = next;
}

void Vertex::Insert(int idx){
    
    //this->next = &new_v;
}

void Vertex::Insert(Vertex *new_v){
    new_v->next = this->next;
    this->next = new_v;
}

Vertex::~Vertex(){
    
}
