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

class RGen{
public:
    RGen();
    std::string a_gen(int point_range = 20, int edge_range = 5);
    
    //void rgen(int st_num_max = 10, int edge_max = 5, int wait_sec = 5, int point_range = 20, int max_try = 25);
    
    int rgen(int argc, char** argv);
    int r_gen();
    
    bool IsDupPt(int x, int y);
    bool IsDupName(const std::vector<std::string> &history, const std::string& name);
private:
    //pt_history used for one street. so clear it everytime finishing a street
    std::vector<int> pt_history;
    //name_street used for all streets. Don't clear it.
    std::vector<std::string> name_history;
};

#endif /* rgen_h */
