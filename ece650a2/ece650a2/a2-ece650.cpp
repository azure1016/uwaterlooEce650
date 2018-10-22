#include <string>
#include <iostream>
#include "graph.hpp"
using namespace std;

int test(){
    Graph* g3 = NULL;
    string v3,e3,s3;
    while(!cin.eof()){
        getline(cin,v3);
        if(v3 != ""){
            if(v3[0] == 'V'){
                getline(cin,e3);
                if(e3[0] == 'E'){
                    try{
                        if(g3 != NULL) delete g3;
                        g3 = new Graph(v3,e3);
                        getline(cin,s3);
                        if(s3[0] == 's'){
                            int src =0, dst=0;
                            g3->GetS(s3, src, dst);
                            g3->BFS(src);
                            g3->PrintPath(src,dst);
                        }
                    }
                    catch(char const* i){
                        std::cerr<<i;
                    }
                }
            }
            else if(g3 != NULL){
                if(v3[0] == 's'){
                    int src =0, dst=0;
                    g3->GetS(v3, src, dst);
                    try{
                        g3->BFS(src);
                        g3->PrintPath(src,dst);
                    }
                    catch(char const* i){
                        std::cerr<<i;
                    }
                }
                else std::cerr<<"Error: invalid input!\n"<<std::endl;
            }
            else{
                std::cerr<<"Error: invalid input! Graph object is null!\n";
            }
        }
        else
            break;
    }
//    if(g3 != nullptr){
//        delete g3;
//        g3 = nullptr;
//    }
    return 0;
}

int main(){
    test();
    std::cout<<"ends\n";
}
