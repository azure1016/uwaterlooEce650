#include "regex.hpp"
#include <regex>
#include <string>
#include <iostream>
using namespace std;

 class Graph(){
     public:
         Graph();
         Graph CreateGraph(int vertices, string edges);//generate a list of vertex
         Vertex FirstAdjVertex(int idx);
         bool BFS(int headVer);
         ~Graph();

     private:
         int verticesNum;
         struct Vertex{
             int idx;
             //use template to allow different value?
             Vertex* next;
         };
         Vertex* graph;//point to a list of vertex, need dynamic allocating?
 };

 Graph::Graph(int r):verticesNum(r){}

 Graph::CreateGraph(const& std::string v_cmd, const& std::string e_cmd ){
     std::string pattern_v{"V\s(\d+)"}, pattern_e{"E\s{(<(\d+),(\d+)>,*)+}"};
     std::regex re_v(pattern_v), re_e(pattern_e);
     bool isValidV = std::regex_match(*v_cmd,re_v);
     std::cout<<isValidV<<std::endl;
     return new Graph();
 }
 int main(){
     std::string v="V 15", e = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
     Graph g = new Graph();
     g.CreateGraph(&v, &e);
     return 0；
 }
