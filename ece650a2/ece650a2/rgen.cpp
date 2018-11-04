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
#include "rgen.h"

//Point::Point(){}
//Point::Point(int x, int y){
//    x = x;
//    y = y;
//}
//
//bool Point::GreaterThan(Point other){}
//
////bool Point::LessThan(Point other){}
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

bool RGen::IsDup(int *arr){
    for(auto i = st_history.begin(); i != st_history.end(); i++){
        if((*arr == *i[0]) && (*(arr+1) == *i[1])) return true;
    }
    return false;
}

//does it have to return a random float?
///this should be executed k times to produce k streets; -s k
///@param int point_range: points between [-k,k]
std::string RGen::a_gen(const std::string& street_name, int point_range, int edge_range){
    std::string res = "a ";
    res += street_name;
    /// -n k >= 1
    int edges = rand() % edge_range + 1;
    char coor[12] ="";
    for(int i = 0; i < edges + 1; i++){
        int x = rand() % (point_range + 1);
        int y = rand() % (point_range + 1);
        int arr[2] = {x, y};
        if(!IsDup(arr)){
            st_history.push_back(arr);
            snprintf(coor, sizeof(coor)," (%d,%d)", x, y);
            std::string coor_s(coor);
            res += coor_s;
        }
        else i--;
        //error_times++
    }
    return res;
}

///overload, generates street names automatically
std::string RGen::a_gen(int point_range, int edge_range){
    std::string street_name =" ";
    std::string st_factory[6] = {"Daven", "Weber", "University", "George", "Cedarbrae", "Parkside"};
    std::string st_type[3] = {"Street", "Avenue", "Road"};
    int st_idx = rand() % 6;
    int st_type_idx = rand() % 3;
    street_name = "\""+st_factory[st_idx]+" "+st_type[st_type_idx]+"\"";
    std::string res = "a ";
    res += street_name;
    /// -n k >= 1
    int edges = rand() % edge_range + 1;
    char coor[12] ="";
    for(int i = 0; i < edges + 1; i++){     //n edges->n+1 points
        int x = rand() % (point_range + 1);
        int y = rand() % (point_range + 1);
        int arr[2] = {x, y};
        if(!IsDup(arr)){
            snprintf(coor, sizeof(coor)," (%d,%d)", x, y);
            std::string coor_s(coor);
            res += coor_s;
        }
        else i--;
    }
    return res;
}
std::string RGen::rgen(int st_num_max, int edge_max, int wait_sec, int point_range, int max_try){
    int st_num = rand()%st_num_max + 1;
    if(st_num == 1) st_num++;
    while(max_try>0){
        if(st_num == 0) break;
        std::cout<<a_gen(point_range, edge_max);//this will be redirect to pipe?
        max_try--;
    }
    return "";
    
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
