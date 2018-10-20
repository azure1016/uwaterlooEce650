//#include "regex.hpp"
//#include <regex>
#include <string>
#include <iostream>
#include "graph.hpp"
using namespace std;

int main(){
    std::string v="V 15";
    std::string e = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    Graph g = Graph(v, e);
    
    return 0;
}
