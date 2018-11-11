
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string>
#include <vector>

class RGen{
public:
    RGen();
    std::string a_gen(int point_range = 20, int edge_range = 5);
    
    //void rgen(int st_num_max = 10, int edge_max = 5, int wait_sec = 5, int point_range = 20, int max_try = 25);
    
    int rgen(int argc, char** argv);
    
    bool IsDupPt(int x, int y);
    bool IsDupName(const std::vector<std::string> &history, const std::string& name);
private:
    //pt_history used for one street. so clear it everytime finishing a street
    std::vector<int> pt_history;
    //name_street used for all streets. Don't clear it.
    std::vector<std::string> name_history;
};


RGen::RGen(){}

bool RGen::IsDupPt(int x, int y){
    for(int i = 0; i < pt_history.size(); i += 2){
        if (x == pt_history.at(i))
            if (y == pt_history.at(i+1))
                return true;
    }
    return false;
}

bool RGen::IsDupName(const std::vector<std::string> &history, const std::string& name){
    if (history.size() == 0) return false;
    for(auto i = history.begin(); i != history.end(); i++){
        std::string old_name = *i;
        if(strcmp(name.c_str(), old_name.c_str()) == 0) return true;
    }
    return false;
}

//does it have to return a random float?
///this should be executed k times to produce k streets; -s k
///@param int point_range: points between [-k,k]
//std::string RGen::a_gen(const std::string& street_name,  int point_range, int edge_range){
//    std::string res = "a ";
//    res += street_name;
//    /// -n k >= 1
//    //int e_range = edge_range.high - edge_range.low;
//    int edges = rand() % edge_range + 1;
//    char coor[12] = "";
//    for(int i = 0; i < edges + 1; i++){
//        int x = rand() % (point_range + 1);
//        int y = rand() % (point_range + 1);
//        int arr[2] = {x, y};
//        if(!IsDup(arr)){
//            pt_history.push_back(arr);
//            snprintf(coor, sizeof(coor)," (%d,%d)", x, y);
//            std::string coor_s(coor);
//            res += coor_s;
//        }
//        else i--;
//        //error_times++
//    }
//    return res;
//}

///overload, generates street names automatically
std::string RGen::a_gen(int point_range, int edge_range){
    //setup for urandom
    std::ifstream urandom("/dev/urandom");
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return "";
    }
    int num = 0;//use it to read from urandom
    
    std::string street_name = "";
    std::string st_factory[10] = {"Daven", "Weber", "University", "George", "Cedarbrae", "Parkside",  "Wall", "London", "King", "Hazel"};
    std::string st_type[4] = {"Street", "Avenue", "Road", "Lane"};
    while(true){
        urandom.read((char*)&num, sizeof(int));
        int st_idx = (int)abs(num) % 10;
        urandom.read((char*)&num, sizeof(int));
        int st_type_idx = (int)abs(num) % 4;
        street_name = "\"" + st_factory[st_idx] + " " + st_type[st_type_idx] + "\"";
        if(!IsDupName(name_history, street_name)){
            name_history.push_back(street_name);
            break;
        }
    }
    std::string res = "a ";
    res += street_name;
    
    /// -n k >= 1
    urandom.read((char*)&num, sizeof(int));
    int edges = (int)abs(num) % edge_range + 1;
    char coor[12] = "";
    for(int i = 0; i < edges + 1; i++){     //n edges->n+1 points
        urandom.read((char*)&num, sizeof(int));
        int x = (int)num % (point_range + 1);
        urandom.read((char*)&num, sizeof(int));
        int y = (int)num % (point_range + 1);
        
        if(!IsDupPt(x,y)){
            pt_history.push_back(x);
            pt_history.push_back(y);
            snprintf(coor, sizeof(coor)," (%d,%d)", x, y);
            std::string coor_s(coor);
            res += coor_s;
        }
        else i--;
    }
    if (pt_history.size() != 0)
        pt_history.clear();//clear it for the next street;
    urandom.close();
    return res;
}


//void RGen::rgen(int st_num_max, int edge_max, int wait_sec, int point_range, int max_try){
//    while(true){
//        int st_num = rand()%(st_num_max - 1) + 2;
//        while(max_try>0){
//            if(st_num == 0){
//                std::cout<<"g"<<std::endl;
//                break;
//            }
//            std::cout<<a_gen(point_range, edge_max);//this will be redirect to pipe
//            max_try--;
//        }
//        sleep((unsigned)wait_sec);
//        for(auto i = name_history.begin(); i != name_history.end(); i++){
//            std::cout<<"r "+*i<<std::endl;
//            //i = name_history.erase(i);//invalidation of iterator?
//            //i++;
//        }
//        name_history.clear();
//    }
//}

int RGen::rgen(int argc, char** argv){
    
    int st_num_max = 10;
    int edge_max = 5;
    int wait_sec = 5;
    int point_range = 20;
    //int max_try = 25;
    int c = -1;
    std::string param = "";
    while ((c = getopt(argc, argv, "s:n:l:c:")) != -1){
        switch(c){
            case 's':
                param = optarg;
                st_num_max = atoi(param.c_str());
                break;
            case 'n':
                param = optarg;
                edge_max = atoi(param.c_str());
                break;
            case 'l':
                param = optarg;
                wait_sec = atoi(param.c_str());
                break;

            case 'c':
                param = optarg;
                point_range = atoi(param.c_str());
                break;
            case '?':
                //if (optopt == 's')
                std::cerr << "Error: option requires an argument." << std::endl;
                break;
            default:
                std::cerr << "Error: invalid argument!" << std::endl;
                break;
        }
    }
    while(true){
        std::ifstream urandom("/dev/urandom");
        if (urandom.fail()) {
            std::cerr << "Error: cannot open /dev/urandom\n";
            return 1;
        }
        //int st_num = rand()%(st_num_max - 1) + 2;
        int num = 42;
        urandom.read((char*)&num, sizeof(int));
        int st_num = (int)abs(num) % (st_num_max-1) + 2;

        while (st_num >= 0){
            if (st_num == 0){
                std::cout<<"g"<<std::endl;
                break;
            }
            std::cout<<a_gen(point_range, edge_max)<<std::endl;//this will be redirect to pipe
            //max_try--;
            st_num--;
        }
        sleep((unsigned)wait_sec);
        for (auto i = name_history.begin(); i != name_history.end(); i++){
            std::cout << "r " + *i << std::endl;
        }
        name_history.clear();
        // close random stream
        urandom.close();
    } 
    return 0;
}

int main(int argv, char** argc){
    RGen r;
    r.rgen(argv, argc);
    return 1;
}
