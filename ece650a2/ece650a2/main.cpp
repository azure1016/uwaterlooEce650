#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string>
#include <signal.h>
#include <vector>
using namespace std;

void test(){
    std::cout<<"a \"weberstreet\" (-1,-1) (1,0.5) (1,2) (0,3)"<<std::endl;
    std::cout<<"a \"king\" (2,-2) (1,0) (1,3) (4,5)"<< std::endl;
    std::cout<<"g"<< std::endl;
}

int rgen(int argc, char **argv) {
    test();
    return 0;
}

int a1(void) {
    char* arg_list[] = {
            "python",
            "-u",
            "a1ece650.py",
            nullptr
    };
    int mes=execvp("python",arg_list);
    if(mes==-1)
        perror("Error:from a1");
    return 0;
}

int a2(void) {
    char* arg_list[] = {
            "a2-ece650",
            nullptr
    };
    int mes=execv("a2-ece650",arg_list);
    if(mes==-1)
        perror("Error:from a2");
    return 0;
}



int main(int argc, char **argv)
{
    std::vector<pid_t> kids;
    int RGenToA1[2];
    pipe(RGenToA1);
    int A1toA2[2];
    pipe(A1toA2);

    pid_t child_pid;
    int status;

    //fork process and launch RGEN
    child_pid = fork ();
    if (child_pid == 0)
    {
        dup2(RGenToA1[1],STDOUT_FILENO);
        close(RGenToA1[0]);
        close(RGenToA1[1]);
        return rgen(argc,argv);
    }

    kids.push_back(child_pid);
//    waitpid(child_pid, &status, 0);

    //fork process and launch A1
    child_pid = fork ();
    if (child_pid == 0)
    {
        dup2(RGenToA1[0],STDIN_FILENO);
        close(RGenToA1[0]);
        close(RGenToA1[1]);

        dup2(A1toA2[1],STDOUT_FILENO);
        close(A1toA2[0]);
        close(A1toA2[1]);
//        cout<<"v 15"<<endl;
//        cout<<"E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}"<<endl;
        return a1();
    }
//    waitpid(child_pid, &status, 0);
    kids.push_back(child_pid);

    //fork process and launch A2
    child_pid = fork ();
    if (child_pid == 0)
    {
        dup2(A1toA2[0],STDIN_FILENO);
        close(A1toA2[0]);
        close(A1toA2[1]);
        return a2();
    }
    kids.push_back(child_pid);


    dup2(A1toA2[1],STDOUT_FILENO);
    close(A1toA2[0]);
    close(A1toA2[1]);
    while (!cin.eof())
    {
        string line;
        getline(cin, line);
        if (line.size () > 0)
            cout<<line<<endl;
    }


    for (pid_t k : kids)
    {
        waitpid(k, &status, 0);
        kill (k, SIGTERM);
    }
    return 0;
}
