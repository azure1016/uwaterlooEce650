//
//  graph.cpp
//  ece650a2
//

#include "graph.hpp"
#include <regex>
#include <queue>

/// judge if an integer is between a certain range.
bool IsBetween(int x, int upper, int lower = 0){
    if((x<=upper) & (x>=lower))
        return true;
    else return false;
}

Graph::Graph(){}

Graph::Graph(int r):verticesNum(r){}

///using input strings to generate graph directly
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
            graph.push_back(new Vertex(i));
        }
        if(isValidE){
            for( ; it_e != end; it_e++){
                int v_src = stoi(it_e->str(1));
                int v_dst = stoi(it_e->str(2));
                if(IsBetween(v_src, verticesNum-1) && IsBetween(v_dst,verticesNum-1)){
                    graph.at(v_src)->adjacentVs.push_back(graph.at(v_dst));
                    graph.at(v_dst)->adjacentVs.push_back(graph.at(v_src));
                }
                else throw "Error: invalid input!\n";
            }
        }
        else throw "Error: invalid input!\n";
    }
    else
        throw "Error: invalid input!\n";
}

///reset vertex information
void Graph::Reset(){
    for(int i = 0; i < verticesNum; i++){
        graph.at(i)->visited = false;
        graph.at(i)->dist = INF;
        graph.at(i)->path = nullptr;
    }
}

///using BFS to find the path from source to destiny
bool Graph::BFS(int headVer){
    if(IsBetween(headVer, verticesNum-1)){
        Reset();
        graph.at(headVer)->dist = 0;
        std::queue<Vertex*> pa;
        pa.push(graph.at(headVer));
        graph.at(headVer)->visited = true;
        Vertex* tmp = nullptr;
        while(!pa.empty()){
            tmp = pa.front();
            pa.pop();
            if(tmp->adjacentVs.size() != 0 ){
                for(uint i = 0; i < tmp->adjacentVs.size(); i++){
                    Vertex* adjV = tmp->adjacentVs.at(i);
                    if(!adjV->visited){
                        adjV->visited = true;
                        if(adjV->dist == INF){
                            adjV->dist = tmp->dist + 1;
                            adjV->path = tmp;
                        }
                        pa.push(adjV);
                    }
                }
            }
        }
        return true;
    }
    else{
        throw "Error: invalid vertice number!\n";
        return false;
    }
}

///after BFS, print the path from source to destiny
void Graph::PrintPath(int src, int dst){
    if((IsBetween(src, verticesNum-1))&&(IsBetween(dst, verticesNum-1))){
        Vertex* n = graph.at(dst)->path;
        std::vector<int> path;
        path.push_back(dst);
        while(n != nullptr){
            path.push_back(n->idx);
            n = n->path;
        }
        if(path.back() != src){
            throw "Error: there is no path from the source to the destiny!\n";
            return;
        }
        std::reverse(path.begin(), path.end());
        for(auto i = path.begin(); i != path.end()-1; i++)
            std::cout<<*i<<"-";
        std::cout<<*(path.end()-1)<<std::endl;
    }
    else throw "Error: invalid vertex name!\n";
}


///parse the s command, get the indexes for source and destiny
void Graph::GetS(const std::string& s_cmd, int& src, int& dst){
    std::regex re_s("s\\s(\\d+)\\s(\\d+)");
    std::smatch m_s;
    bool isValidS = std::regex_search(s_cmd,m_s,re_s);
    if(isValidS){
        src = stoi(m_s[1]);
        dst = stoi(m_s[2]);
    }
    else throw "Error: invalid input!\n";
}

///the destructor
Graph::~Graph(){
    if(graph.size() != (uint)0){
        int len = (int)graph.size();
        for(int i = 0; i < len; i++){
            Vertex* p = graph[i];
            if(p){
                delete p;
                p = nullptr;
            }
        }
    }
    //std::cout<<"graph destroy\n";
}

Vertex::Vertex(){}


///constructor for Vertex
Vertex::Vertex(int idx, int dist, bool visited, Vertex* path){
    this->idx = idx;
    this->dist = dist;
    this->path = path;
    this->visited = false;
}

Vertex::~Vertex(){}
