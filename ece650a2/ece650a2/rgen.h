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

struct Range{
    int low;
    int high;
    int width;
};

class RGen{
public:
//    std::string a_gen(const std::string& street_name, int point_range = 5, int edge_range = 20);
//    std::string a_gen(int point_range = 20, int edge_range = 5);
//    
//    std::string rgen(int st_num_max = 10, int edge_max = 5, int wait_sec = 5, int point_range = 20, int max_try = 25);
    std::string a_gen(const std::string& street_name, int point_range = 5, int edge_range = 20);
    std::string a_gen(int point_range = 20, int edge_range = 5);
    
    std::string rgen(int st_num_max = 10, int edge_max = 5, int wait_sec = 5, int point_range = 20, int max_try = 25);
    bool IsDup(int *arr);
private:
    std::vector<int[2]> st_history;
};

#endif /* rgen_h */
