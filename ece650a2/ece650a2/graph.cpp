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
        //if there exist a previous graph object, you have to delete it!
        if (graph != nullptr){
            delete graph;
            graph = nullptr;
        }
        if(visited != nullptr){
            delete visited;
            visited = nullptr;
        }
        graph = new Vertex[this->verticesNum];
        visited = new bool[verticesNum]();//initialize the array with false
        for(int i = 0; i < verticesNum; i++){
            graph[i].idx = i;
        }
        if(isValidE){
            for( ; it_e != end; it_e++){
                int v_src = stoi(it_e->str(1));
                int v_dst = stoi(it_e->str(2));
                if(IsBetween(v_src, verticesNum) && IsBetween(v_dst,verticesNum)){
                    graph[v_src].Insert(v_dst);
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


bool Graph::BFS(int headVer){
    if(this->visited[headVer] != false){
        std::queue<Vertex> pa;
    }
    return true;
}

Graph::~Graph(){
    //delete graph;
    if(graph != NULL){
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
    }
    delete graph;
    graph = nullptr;
}

Vertex::Vertex(){
    
}

Vertex::Vertex(int idx, Vertex* next){
    this->idx = idx;
    this->next = next;
}

void Vertex::Insert(int idx){
    Vertex new_v = Vertex(idx, this->next);
    this->next = &new_v;
}

void Vertex::Insert(Vertex *new_v){
    new_v->next = this->next;
    this->next = new_v;
}

Vertex::~Vertex(){
    
}
