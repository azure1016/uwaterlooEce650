//#include "regex.hpp"
//#include <regex>
#include <string>
#include <iostream>
#include "graph.hpp"
using namespace std;

int main(){
    std::string v1="V 15";
    std::string e1 = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    std::string v2="V 5";
    std::string e2 = "E {<0,2>,<2,1>,<2,3>,<3,4>,<4,1>}";

    Graph g = Graph(v1, e1);
    Graph g2 = Graph(v2,e2);
    g.BFS(2);
    g.PrintPath(2,10);
    g2.BFS(4);
    g2.PrintPath(4,0);
    return 0;
}
