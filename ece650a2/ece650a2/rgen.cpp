//
//  rgen.cpp
//  test
//
//  Created by Bu's love on 2018/10/29.
//  Copyright © 2018年 DanWang. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string>
#include <vector>
#include "rgen.h"


//Point::Point(){}
//Point::Point(int x, int y){
//    x = x;
//    y = y;
//}
//
//bool Point::GreaterThan(Point other){}
//
//bool Point::LessThan(Point other){}
//Line::Line(){}
//Line::Line(Point x, Point y){
//    src = x;
//    dst = y;
//}
//
//bool Line::GreaterThan(Line other){
//    bool ge1 = (src <= other.src) & (src <= other.dst) & (dst >= other.src) & (dst >= other.dst);
//    bool ge2 = (dst <= other.src) & (dst <= other.dst) & (src >= other.src) & (dst >= other.dst);
//    return (ge1 | ge2);
//}
RGen::RGen(){}

bool RGen::IsDupPt(int *arr){
    for(auto i = pt_history.begin(); i != pt_history.end(); i++){
        if((*arr == **i) && (*(arr+1) == *(*i+1))) return true;
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
    std::string street_name =" ";
    std::string st_factory[10] = {"Daven", "Weber", "University", "George", "Cedarbrae", "Parkside",  "Wall", "London", "King", "Hazel"};
    std::string st_type[4] = {"Street", "Avenue", "Road", "Lane"};
    while(true){
        int st_idx = rand() % 10;
        int st_type_idx = rand() % 4;
        street_name = "\""+st_factory[st_idx]+" "+st_type[st_type_idx]+"\"";
        if(!IsDupName(name_history, street_name)){
            name_history.push_back(street_name);
            break;
        }
    }
    std::string res = "a ";
    res += street_name;
    /// -n k >= 1
    int edges = rand() % edge_range + 1;
    char coor[12] = "";
    for(int i = 0; i < edges + 1; i++){     //n edges->n+1 points
        int x = rand() % (point_range + 1);
        int y = rand() % (point_range + 1);
        int arr[2] = {x, y};
        if(!IsDupPt(arr)){
            pt_history.push_back(arr);
            snprintf(coor, sizeof(coor)," (%d,%d)", x, y);
            std::string coor_s(coor);
            res += coor_s;
        }
        else i--;
    }
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

void RGen::rgen(int argc, char** argv){
    int st_num_max = 10;
    int edge_max = 5;
    int wait_sec = 5;
    int point_range = 20;
    int max_try = 25;
    int c;
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
        int st_num = rand()%(st_num_max - 1) + 2;
        while (max_try > 0){
            if (st_num == 0){
                std::cout<<"g"<<std::endl;
                break;
            }
            std::cout<<a_gen(point_range, edge_max);//this will be redirect to pipe
            max_try--;
        }
        sleep((unsigned)wait_sec);
//        for (auto i = name_history.begin(); i != name_history.end(); i++){
//            std::cout<<"r "+*i<<std::endl;
//            //i = name_history.erase(i);//invalidation of iterator?
//        }
//        name_history.clear();
    }
}

//
//bool Line::IsIntersect(Line l2){
//    int x1 = src.x;
//    int y1 = src.y;
//    int x2 = dst.x;
//    int y2 = dst.y;
//    int x3 = l2.src.x;
//    int y3 = l2.src.y;
//    int x4 = l2.dst.x;
//    int y4 = l2.dst.y;
////to determine whether the two lines would intersect on the 2 segments
//    int t_up = (x1-x3)*(y3-y4) - (y1-y3)*(x3-x4);
//    int u_up = -(x1-x2)*(y1-y3) + (y1-y2)*(x1-x3);
//    int denominator = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
////if they are parallel or coincident:
//    if (denominator == 0){
////coincident
//        if ((x1-x2) * (y2-y3) == (x2-x3) * (y1-y2)){
//            if (l1.__ge__(l2))
//                return true;
//            else if (l2.__ge__(l1))
//                return true;
//            else
//                return false;
//        }
////parallel
//        else{
//            return false;
//        }
//    }
//    else{
//        int t = t_up / denominator;
//        int u = u_up / denominator;
////if the intersection is on both segments
//        if (0 <= t and t <= 1 and 0 <= u and u <= 1)
//            return true;
//        else
//            return false;
//    }
//}
