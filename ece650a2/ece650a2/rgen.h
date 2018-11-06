//
//  rgen.h
//  test
//
//  Created by Bu's love on 2018/10/29.
//  Copyright © 2018年 DanWang. All rights reserved.
//

#ifndef rgen_h
#define rgen_h
#include <vector>
#include <string>
//class Point{
//public:
//    int x;
//    int y;
//public:
//    Point();
//    Point(int x, int y);
//    bool LessThan(Point other);
//    bool GreaterThan(Point other);
//};
//class Line{
//private:
//    Point src;
//    Point dst;
//public:
//    Line();
//    Line(Point x, Point y);
//    bool IsIntersect(Line other);
//    bool GreaterThan(Line other);
//};

//struct Range{
//    int low;
//    int high;
//    //int width;
//    Range(std::initializer_list<int> list){}
//};

class RGen{
public:
    RGen();
    std::string a_gen(int point_range = 20, int edge_range = 5);
    
    void rgen(int st_num_max = 10, int edge_max = 5, int wait_sec = 5, int point_range = 20, int max_try = 25);
    
    void rgen(int argc, char** argv);
    
    bool IsDupPt(int *arr);
    bool IsDupName(const std::vector<std::string> &history, const std::string& name);
private:
    std::vector<int*> pt_history;
    std::vector<std::string> name_history;
};

#endif /* rgen_h */
