#include <iostream>
#include <vector>
#include <regex>
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"



bool IsBetween(int x, int upper, int lower = 0){
    if((x<=upper) & (x>=lower))
        return true;
    else return false;
}

class VertexCover{
public:
    VertexCover(); //default constructor
    VertexCover(int v_n, std::string E_info);
    VertexCover(int v_n, int c_size); //constructor
    //Minisat::Var toVar(int n_th, int k_th);  //map a int to a var
    bool solve(); //solve the problem
    //void exactly_one_true(Minisat::vec<Minisat::Lit> const& literals);
    bool getModel(Minisat::Solver *s); //verify the vars in V_i_j a model or not
    void init_variables(Minisat::Solver *s, int k);
    void print();
    

private:
    int ver_num;
    int cover_size;
    std::vector<int> vCover;
    std::vector<int> e_info;
    std::vector<std::vector<Minisat::Var> > V_i_j; //if an element is in cover set, will be set true
    std::vector<std::vector<Minisat::Lit> > L_i_j;
    //Minisat::Solver s;
    
    //std::vector<Minisat::Var> *variables;
    
public:
    void build(Minisat::Solver *s, int c_size);//build a set of cnf, pass it to Solver
    
    bool parse(std::string V_info, std::string E_info);//parse vertices, edges info from string
};

VertexCover::VertexCover(){}

VertexCover::VertexCover(int v_num, int c_size): ver_num(v_num), cover_size(c_size){
    //build();
}

VertexCover::VertexCover(int v_num, std::string Es_info): ver_num(v_num), cover_size(0){
    //build();
    
}



//init the variables and literals. Like allocating?
///use it every time you have a new cover_size
void VertexCover::init_variables(Minisat::Solver *s, int k){
    //reset the vectors
    V_i_j.clear();
    L_i_j.clear();
    //allocating for the variables and literals
    for(int i = 0; i < ver_num; i++){
        std::vector<Minisat::Var> vars;
        std::vector<Minisat::Lit> lits;
        for(int j = 0; j < k; j++){
            vars.push_back(s->newVar());
            lits.push_back(Minisat::mkLit(vars.back()));
        }
        V_i_j.push_back(vars);
        L_i_j.push_back(lits);
    }
}

bool VertexCover::solve(){
    bool solved = false;
    for (int i = 1; i <= ver_num; i++){//looping to find a minimum vertex
        Minisat::Solver s;
        init_variables(&s, i);
        build(&s, i);
        solved = s.solve();
        if (solved == true){
            bool modeled = getModel(&s);
            if (modeled)
                print();
            break;
        }
        //std::cout << "for k = " << i << " no solution\n";
    }
    return solved;
}

//form all the literals and add them as clauses
void VertexCover::build(Minisat::Solver *s, int c_size){
    assert(c_size <= ver_num); // k <= n
    //rule 1:
    for (int j = 0; j < c_size; j++){
        Minisat::vec<Minisat::Lit> literals;
        for (int i = 0; i < ver_num; i++){
            literals.push(L_i_j.at(i).at(j));
        }
        s->addClause(literals);
    }
    
    //rule 2
    for (int i = 0; i < ver_num; i++){
        for (int p = 0; p < c_size; p++){
            for (int q = p + 1; q < c_size; q++){
                if (q >= c_size) break;
                Minisat::Lit l1 = L_i_j.at(i).at(p);
                Minisat::Lit l2 = L_i_j.at(i).at(q);
                s->addClause(~l1, ~l2);
                //s->addClause(~L_i_j.at(i).at(p),~L_i_j.at(i).at(q));
            }
        }
    }
    
    //rule 3
    for (int j = 0; j < c_size; j++){
        for (int p = 0; p < ver_num; p++){
            for (int q = p + 1; q < ver_num; q++){
                if (q >= ver_num) break;
                Minisat::Lit l1 = L_i_j.at(p).at(j);
                Minisat::Lit l2 = L_i_j.at(q).at(j);
                s->addClause(~l1, ~l2);
                //s->addClause(~L_i_j.at(p).at(j),~L_i_j.at(q).at(j));
            }
        }
    }
    
    //rule 4
    for(int i = 0; i < e_info.size(); i += 2){
        int idx = e_info.at(i);
        int jdx = e_info.at(i+1);
        Minisat::vec<Minisat::Lit> literals;
        for (int k = 0; k < c_size; k++){            
            literals.push(L_i_j.at(idx).at(k));
            literals.push(L_i_j.at(jdx).at(k));
        }
        s->addClause(literals);
    }
}

bool VertexCover::getModel(Minisat::Solver *s){
    Minisat::lbool modeled = Minisat::l_False;
    for (int i = 0; i < V_i_j.size(); i++){
        for (int j = 0; j < V_i_j.at(i).size(); j++){
            modeled = s->modelValue(V_i_j.at(i).at(j));
            if (modeled == Minisat::l_True){
                vCover.push_back(i);
            }
        }
    }
    cover_size = (int)vCover.size();
    if (cover_size != 0) return true;
    else return false;
}

bool VertexCover::parse(std::string v_cmd, std::string e_cmd){
    e_info.clear();
    vCover.clear();
    std::smatch m_v;
    std::regex re_v("V\\s(\\d+)");
    std::regex re_e("E\\s\\{(<(\\d+),(\\d+)>,*)+\\}");
    std::regex re_coor("<(\\d+),(\\d+)>");
    std::sregex_iterator it_e(e_cmd.cbegin(),e_cmd.cend(),re_coor);
    std::sregex_iterator end;
    bool isValidV = std::regex_search(v_cmd,m_v,re_v);
    bool isValidE = std::regex_search(e_cmd,re_e);
    if(isValidV){
        this->ver_num = stoi(m_v[1]);
        if(isValidE){
            for( ; it_e != end; it_e++){
                int v_src = stoi(it_e->str(1));
                int v_dst = stoi(it_e->str(2));
                if(IsBetween(v_src, ver_num-1) && IsBetween(v_dst, ver_num-1)){
                    e_info.push_back(v_src);
                    e_info.push_back(v_dst);
                }
                else throw "Error: invalid input!\n";
            }
        }
        else throw "Error: invalid input!\n";
    }
    else
        throw "Error: invalid input!\n";
    return (isValidE & isValidV);
}

void VertexCover::print(){
    int i = 0;
    do{
        std::cout<<vCover.at(i)<<" ";
        ++i;
    }while(i < vCover.size()-1);
    if(vCover.size() > 1)
        std::cout<< vCover.back() << std::endl;
    else std::cout<<std::endl;
}
//initialize the variables
//Minisat::Var VertexCover::toVar(int n_th, int k_th){
//    //assert(n_th >= 0 && n_th < ver_num && k_th >= 0 && k_th < cover_size);
//    ///actually I think n_th >= k_th is always true
//    int var_int = n_th * ver_num + k_th;
//    //s.newVar();
//}

//void VertexCover::exactly_one_true(Minisat::vec<Minisat::Lit> const& literals) {
//    s.addClause(literals);
//    for (size_t i = 0; i < literals.size(); ++i) {
//        for (size_t j = i + 1; j < literals.size(); ++j) {
//            s.addClause(~literals[i], ~literals[j]);
//        }
//    }
//}



int main(int argc, char **argv) {
    VertexCover vc;
    std::string v_cmd, e_cmd;
    while(!std::cin.eof()){
        std::getline(std::cin, v_cmd);
        std::getline(std::cin, e_cmd);
        if(v_cmd == "" || e_cmd == "")
            exit(1);
        try{
            vc.parse(v_cmd, e_cmd);
        }
        catch (char const* i){
            std::cerr << i << std::endl;
            continue;
        }
        vc.solve();
    }
    
}
