//#include "regex.hpp"
#include <regex>
#include <string>
#include <iostream>
using namespace std;

struct Vertex{
             int idx;
             //use template to allow different value?
             int* next;
         };

 class Graph{
     public:
         Graph(int r);
         Graph(std::string v_cmd, std::string e_cmd);//generate a list of vertex
         Vertex FirstAdjVertex(int idx);
         bool BFS(int headVer);
         ~Graph();

     private:
         int verticesNum;
         Vertex* graph;//point to a list of vertex, need dynamic allocating?
 };

 Graph::Graph(int r):verticesNum(r){}

 Graph::Graph(std::string v_cmd, std::string e_cmd){
     std::string pattern_v{ "V\\s(\\d+)" };
     std::string pattern_e{ "E\\s\{(<(\\d+),(\\d+)>,*)+\}" };
     std::regex re_v(pattern_v);
     std::regex re_e(pattern_e);
     bool isValidV = std::regex_match(v_cmd,re_v);
     std::cout<<isValidV<<std::endl;
     //return new Graph();
 }

 Vertex Graph::FirstAdjVertex(int idx){}

 bool Graph::BFS(int headVer){}

 Graph::~Graph(){}
 int main(){
     std::string v="V 15";
     std::string e = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
     Graph g = Graph(v, e);
     
     return 0;
 }
