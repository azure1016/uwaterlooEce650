#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <queue>
#include <stack>
#include <algorithm>
#include <pthread.h>
#include <fstream>
#include <semaphore.h>
#include <time.h>
#include <chrono>
#include <atomic>
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"

using namespace std;
using namespace Minisat;
int nVerts;
vector<int> edges;
vector<int> satResult;
vector<int> vc1Result;
vector<int> vc2Result;
sem_t *IO_ret;
sem_t *VC_ret;
sem_t semaphoreIO;
sem_t semaphore;
int IO_end_flag = 0;
double timerResultVC;
double timerResultVC1;
double timerResultVC2;

ofstream fout("out.txt");
//string out_name[10]= {"out1.txt","out2.txt","out3.txt","out4.txt","out5.txt","out6.txt","out7.txt","out8.txt","out9.txt","out0.txt"};
////ofstream fout("out.txt");
ifstream fin("in.txt");
#define cin fin
//
class timer {
public:
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
    timer() : lastTime(std::chrono::high_resolution_clock::now()) {}
    inline double elapsed() {
        std::chrono::time_point<std::chrono::high_resolution_clock> thisTime=std::chrono::high_resolution_clock::now();
        double deltaTime = std::chrono::duration<double>(thisTime-lastTime).count();
        lastTime = thisTime;
        return deltaTime;
    }
};

int parseInputEdges(string &input) {
    try {

        char delim[] = " ,{}<>}";
        char *token;
        int count = 1;
        string param1, param2;
        int p1 = -1, p2 = -1;

        char cstr1[input.size() + 1];//as 1 char space for null is also required
        strcpy(cstr1, input.c_str());

        //In the first call to strtok, the first argument is the line to be tokenized
        token = strtok(cstr1, delim);

        if(token==NULL)
            return -1;

        param1 = token;
        p1 = stoi(param1);

        //In subsequent calls to strtok, the first argument is NULL
        while ((token = strtok(NULL, delim)) != NULL) {
            count++;
            if (count == 1) {
                param1 = token;
                p1 = stoi(param1);
            }
            if (count == 2) {
                param2 = token;
                p2 = stoi(param2);
                if(p1<0||p1>=nVerts)
                    return -1;
                if(p2<0||p2>=nVerts)
                    return -1;

                edges.push_back(p1);
                edges.push_back(p2);
                count = 0;
            }
            if (p1 == -1 || p2 == -1)
                return -1;
        }
    }
    catch(...)
    {
        return -1;
    }
}


void* MinVertexCover(void*)
{
    timer stopwatch;
    for(int k=1;k<=nVerts;k++)
    {
        Solver solver;

        Lit literal[nVerts][k];

        //initialize literal
        for(int i=0;i<nVerts;i++)
        {
            for(int j=0;j<k;j++)
            {
                literal[i][j]=mkLit(solver.newVar());
            }
        }

        //(1)∀i ∈ [1, k], a clause (x 1,i ∨ x 2,i ∨ · · · ∨ x n,i )
        for(int j=0;j<k;j++)
        {
            vec<Lit> c;
            for(int i=0;i<nVerts;i++)
            {
//                    cout<<var(literal[i][j])<<" ";
                c.push(literal[i][j]);
            }
//                cout<<endl;
            solver.addClause(c);
            c.clear();
        }
//            cout<<"k="<<k<<endl;


        //(2)∀m ∈ [1, n], ∀p, q ∈ [1, k] with p < q, a clause (¬x m,p ∨ ¬x m,q)
//                cout<<"k="<<k<<endl;
        for (int m=0;m<nVerts;m++)
        {
            for(int p=0;p<k-1;p++)
                for(int q=p+1;q<k;q++)
                {
                    solver.addClause(~literal[m][p],~literal[m][q]);
//                            cout<<"¬"<<var(literal[m][p])<<" ∨ "<<"¬"<<var(literal[m][q])<<" and ";
                }
        }

        //(3)∀m ∈ [1, k], ∀p, q ∈ [1, n] with p < q, a clause (¬x p,m ∨ ¬x q,m )
        for(int m=0;m<k;m++)
        {
            for(int p=0;p<nVerts-1;p++)
            {
                for (int q = p + 1; q < nVerts; q++) {
                    solver.addClause(~literal[p][m], ~literal[q][m]);
                }
            }
        }


        //(4)∀<i, j> ∈ E, a clause (x i,1 ∨ x i,2 ∨ · · · ∨ x i,k ∨ x j,1 ∨ x j,2 ∨ · · · ∨ x j,k )
        if(!edges.empty())
        {
            int i;
            int j;
            vec<Lit> c;
            for(int w=0;w<edges.size();w=w+2)
            {
                i=edges[w];
                j=edges[w+1];
                for(int h=0;h<k;h++)
                {
                    c.push(literal[i][h]);
                    c.push(literal[j][h]);
                }
                solver.addClause(c);
                c.clear();
            }
        }

        if (solver.solve()){
            vector<int> cnfresult;
            for (int i = 0; i < nVerts; ++i){
                for (int j = 0; j < k; ++j){
                    if (solver.modelValue(literal[i][j])== l_True)
                        cnfresult.push_back(i);
                }
            }


            //copy result to global vector
            satResult.clear();
            satResult.assign(cnfresult.begin(), cnfresult.end());

            timerResultVC=stopwatch.elapsed();
//            cout << "VC time " << timerResultVC << endl;
            return NULL;
        }

    }
}


void* approxVc1(void*)
{
    timer stopwatch;
    vector<int> vc;
    //duplicate edges
    vector<int> dupEdges(edges);


    //step3: Repeat till no edges remain. We will call this algorithm APPROX-VC-1.
    while(dupEdges.size()>0) {
        //step1:Pick a vertex of highest degree (most incident edges).
        vector<int> degree(nVerts);

        for (int i = 0; i < dupEdges.size(); i++) {
            degree[dupEdges[i]]++;
        }

//        cout<<"degree: ";
//        for(int i=0;i<nVerts;i++)
//            cout<<degree[i]<<", ";
//        cout<<endl;
        int maxE = *max_element(degree.begin(), degree.end());
        int maxVertex = 0;
        for (int i = 0; i < degree.size(); i++)
            if (degree[i] == maxE) {
                maxVertex = i;
                break;
            }

//        cout<<"Max="<<maxE<<endl;
//        cout<<"MaxVertex"<<maxIndex<<endl;
        //Step2:Add it to your vertex cover
        vc.push_back(maxVertex);
        //throw away all edges incident on that vertex.
        for (int i = 0; i < dupEdges.size();) {
            if (dupEdges[i] == maxVertex || dupEdges[i + 1] == maxVertex) {
                dupEdges.erase(dupEdges.begin() + i, dupEdges.begin() + i + 2);
                i = 0;
            } else {
                i = i + 2;
            }
        }
    }


    //copy result to global vector
    vc1Result.clear();
    vc1Result.assign(vc.begin(), vc.end());
    timerResultVC1=stopwatch.elapsed();
//    cout << "VC1 time " << timerResultVC1 << endl;
    return NULL;
}


void* approxVc2(void*)
{
    timer stopwatch;
    //Pick an edge ⟨u,v⟩, and add both u and v to your vertex cover.
    //Throw away all edges attached to u and v. Repeat till no edges remain.
    // We will call this algorithm APPROX- VC-2.
    vector<int> vc;
    //duplicate edges
    vector<int> dupEdges(edges);

    while(dupEdges.size()!=0) {
        int u, v;
        int oddIndex,evenIndex;

        //random pick an edge
        int random;
        // open /dev/urandom to read
        std::ifstream urandom("/dev/urandom");

        char ch = 'a';
        urandom.read(&ch, 1);
        random=ch%(dupEdges.size());
        urandom.close();

        //even or odd number
        if(random%2==0)
        {
            //even number index
            evenIndex=random;
            oddIndex=evenIndex+1;
        }
        else
        {
            //odd number index
            oddIndex=random;
            evenIndex=oddIndex-1;
        }
//            cout<<"random:"<<random<<endl;
//            cout<<"evenIndex:"<<evenIndex<<endl;
//            cout<<"oddIndex:"<<oddIndex<<endl;

        //pick an edge
        u = dupEdges[evenIndex];
        v = dupEdges[oddIndex];
        vc.push_back(dupEdges[evenIndex]);
        vc.push_back(dupEdges[oddIndex]);
        dupEdges.erase(dupEdges.begin() + evenIndex, dupEdges.begin() + oddIndex+1);
        for (int i = 0; i < dupEdges.size();) {
            if (dupEdges[i] == u || dupEdges[i+1] == u || dupEdges[i] == v || dupEdges[i+1] == v) {
//                    cout<<"delete:"<<dupEdges[i]<<"and "<<dupEdges[i+1]<<endl;
                dupEdges.erase(dupEdges.begin()+i, dupEdges.begin() + i+2);
                i=0;
            }
            else{
                i=i+2;
            }
        }
    }

//        for(int i=0;i<dupEdges.size();i++)
//        {
//            cout<<"DUPedges:"<<dupEdges[i]<<endl;
//        }
//        for(int i=0;i<vc.size();i++)
//        {
//            cout<<"vc:"<<vc[i]<<endl;
//        }



    //copy result to global vector
    vc2Result.clear();
    vc2Result.assign(vc.begin(), vc.end());
    timerResultVC2=stopwatch.elapsed();
//    cout << "VC2 time " << timerResultVC2 << endl;
    return NULL;
}



void* ioProcess(void*)
{
    enum status{iVertice,iEdge};
    status stat=iVertice;
    string inputStr;
    char read[100] = {0};
    string subStr;
    int vn;
    ofstream fout("out.txt");
    ifstream fin("in.txt");
//#define cin fin
    while(!cin.eof())
    {
        try {
            switch (stat) {
                case iVertice:
                    fin.getline(read,100);
                    inputStr = read;
                    vn=stoi(inputStr.substr(2,inputStr.size()));
                    if (inputStr[0] == 'V') {
                          cout<<inputStr<<endl;
//                        cout<<vn<<endl;
                        nVerts=vn;
                        stat = iEdge;
                        edges.clear();
                    }else {
                        cout << "Error: wrong vertice input, please input vertice again" << endl;
                        stat = iVertice;
//                        g.reset();
                    }
                    break;
                case iEdge:
                    //getline(cin,inputStr);
                    fin.getline(read,100);
                    inputStr = read;
                    if (inputStr[0] == 'E') {
                        subStr = inputStr.substr(2, inputStr.size());
//                        cout << inputStr << endl;
                        if (parseInputEdges(subStr) == -1) {
                            cout << "Error: wrong EDGEs input OR do not exist any Path, now reinput vertice !" << endl;
                            stat = iVertice;
                            edges.clear();
                        } else {
                            stat=iVertice;

                            //MAC OS
//                            sem_post(VC_ret);
//                            sem_wait(IO_ret);
                            //Linux
                            sem_post(&semaphore);
                            sem_wait(&semaphoreIO);


                            //print project format
                            if(satResult.size()>0)
                            {
                                sort(satResult.begin(),satResult.end());
                                cout<<"CNF-SAT-VC: ";
                                for(int i=0;i<satResult.size();i++)
                                {
                                    if(i!=satResult.size()-1)
                                    {
                                        cout<<satResult[i]<<",";
                                    }else
                                    {
                                        cout<<satResult[i]<<endl;
                                    }
                                }
                            }

                            //print ApproxVC1 format
                            if(vc1Result.size()>0)
                            {
                                sort(vc1Result.begin(),vc1Result.end());
                                cout<<"APPROX-VC-1: ";
                                for(int i=0;i<vc1Result.size();i++)
                                {
                                    if(i!=vc1Result.size()-1)
                                    {
                                        cout<<vc1Result[i]<<",";
                                    }else
                                    {
                                        cout<<vc1Result[i]<<endl;
                                    }
                                }
                            }

                            //print ApproxVC2 format
                            if(vc2Result.size()>0)
                            {
                                sort(vc2Result.begin(),vc2Result.end());
                                cout<<"APPROX-VC-2: ";
                                for(int i=0;i<vc2Result.size();i++)
                                {
                                    if(i!=vc2Result.size()-1)
                                    {
                                        cout<<vc2Result[i]<<",";
                                    }else
                                    {
                                        cout<<vc2Result[i]<<endl;
                                    }
                                }
                            }

                            //for report use data
                            double ratio_vc1 = (double(satResult.size())/double(vc1Result.size()));
                            double ratio_vc2 = (double(satResult.size())/double(vc2Result.size()));
                            cout << "VC1 ratio " << ratio_vc1 << endl;
                            cout << "VC2 ratio " << ratio_vc2 << endl;
                            cout << "CNFSAT time " << timerResultVC << endl;
                            cout << "VC1 time " << timerResultVC1 << endl;
                            cout << "VC2 time " << timerResultVC2 << endl;



                        }
                    }
                    break;
            }
        }
        catch(...)
        {
        }
    }
    IO_end_flag = 1;

    //MAC OS
//    sem_post(VC_ret);
    //Linux
    sem_post(&semaphore);
}

int main(void) {
    int ret;

    pthread_t thread_IO_id,thread_MiniSat_id,thread_VC1_id,thread_VC2_id;

    //MAC OS
//    sem_unlink("semIO");
//    IO_ret = sem_open("semIO", O_CREAT|O_EXCL, S_IRWXU, 0);
//    if (IO_ret == SEM_FAILED)
//        cout << "sem_open1 failed" << endl;
    //Linux
    ret = sem_init(&semaphoreIO, 0, 0);

    ret=pthread_create(&thread_IO_id,NULL,&ioProcess,NULL);
    if(ret!=0)
        cout<<"pthread_create error: error_code"<<ret<<endl;


    while(true)
    {
        //MAC OS
//        sem_unlink("semVC");
//        VC_ret = sem_open("semVC", O_CREAT|O_EXCL, S_IRWXU, 0);
//        if (VC_ret == SEM_FAILED)
//            cout << "sem_open2 failed" << endl;
//
//        sem_wait(VC_ret);
//
//        if(IO_end_flag == 1)
//            break;
        //Linux
        ret = sem_init(&semaphore, 0, 0);
        sem_wait(&semaphore);

        if(IO_end_flag == 1)
            break;


        ret=pthread_create(&thread_MiniSat_id,NULL,&MinVertexCover,NULL);
        if(ret!=0)
            cout<<"pthread_create error: error_code"<<ret<<endl;

        ret=pthread_create(&thread_VC1_id,NULL,&approxVc1,NULL);
        if(ret!=0)
            cout<<"pthread_create error: error_code"<<ret<<endl;

        ret=pthread_create(&thread_VC2_id,NULL,&approxVc2,NULL);
        if(ret!=0)
            cout<<"pthread_create error: error_code"<<ret<<endl;

        pthread_join (thread_MiniSat_id, NULL);
        pthread_join (thread_VC1_id, NULL);
        pthread_join (thread_VC2_id, NULL);

        //MAC OS
//        sem_post(IO_ret);
        //Linux
        sem_post(&semaphoreIO);
    }

    pthread_join (thread_IO_id, NULL);

    //MAC OS
//    sem_unlink("semIO");
//    sem_unlink("semVC");
    return 0;
}
