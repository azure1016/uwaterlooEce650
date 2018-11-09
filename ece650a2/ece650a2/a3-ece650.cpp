
//
//  a3-ece650.cpp
//  test
//
//  Created by Bu's love on 2018/10/29.
//  Copyright © 2018年 DanWang. All rights reserved.
//
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include "rgen.h"


void test(){
    //while(true){
    std::cout<<"a \"weberstreet\" (-1,-1) (1,0.5) (1,2) (0,3)"<<std::endl;
        //sleep(1);
    std::cout<<"a \"king\" (2,-2) (1,0) (1,3) (4,5)"<< std::endl;
    //sleep(1);
    std::cout<<"g"<< std::endl;
    //sleep(1);
    //}
}


int main(int argc, char **argv){
    int rgen_a1[2];
    int a1_a2[2];
    
    int ret1 = pipe(rgen_a1);
    int ret2 = pipe(a1_a2);
    if (ret1 == -1 | ret2 == -1){
        perror("pipe creation failed!");
        exit(1);
    }
    std::vector<pid_t> kids;
    pid_t child_pid;
    
    child_pid = fork();
    
    if (child_pid == 0){
        //std::cout << "rgen process" << std::endl;
        //redirect rgen's output to write-end; in other words, rgen wanna write
        dup2(rgen_a1[1], STDOUT_FILENO);
        close(rgen_a1[0]);
        close(rgen_a1[1]);
        test();
        //return res;
        //RGen r;
        //r.rgen(argc, argv);
    }
    
    kids.push_back(child_pid);
    
    child_pid = fork();
    
    if(child_pid == 0){
        //redirect stdin from the rgen_a1 pipe's read-end; in other words, a1 wanna read from the rgen
        dup2(rgen_a1[0], STDIN_FILENO);
        close(rgen_a1[0]);
        close(rgen_a1[1]);

        //redirect stout to the a1_a2 pipe's write-end; a1 wanna write to a2
        dup2(a1_a2[1], STDOUT_FILENO);
        close(a1_a2[0]);
        close(a1_a2[1]);
        //std::cout << "a1 process" << std::endl;
        char* arg_list[4] = {(char*)"/usr/bin/python",
            (char*)"-u",
            (char*)"./a1ece650.py",
            nullptr
        };
        execvp("/usr/bin/python", arg_list);
        std::cerr << "Error: an error occurred in execv" << std::endl;
    }
    
    kids.push_back(child_pid);
    
   
   
    
    //kids.push_back(child_pid);
    
    child_pid = fork();
    
    if (child_pid == 0){
        //std::cout << "a2 process" << std::endl;
        //redirect stdin from the pipe's read-end; in other words, a2 wanna read from the pipe
//        dup2(a1_a2[0], STDIN_FILENO);
//        close(a1_a2[0]);
//        close(a1_a2[1]);
        dup2(a1_a2[0], STDIN_FILENO);
        close(a1_a2[0]);
        close(a1_a2[1]);
        char* arg_list[2] = {(char*)"./a2-ece650",
            nullptr
        };
        execvp("./a2-ece650", arg_list);
    }
    
    kids.push_back(child_pid);
    
    
//    child_pid = fork();
//    
//    if (child_pid == 0){
        //std::cout << "a3 process" << std::endl;
        //redirect stdin to the pipe's read-end; in other words, a3 wanna read from the standin, and
        //send them to a2
//        dup2(a1_a2[1], STDOUT_FILENO);
//        close(a1_a2[0]);
//        close(a1_a2[1]);
//        while (!std::cin.eof()){
//            std::string line;
//            std::getline(std::cin, line);
//            if (line.size () > 0)
//                std::cout << line << std::endl;
//        }
    //}
    
//    dup2(rgen_a1[0], STDIN_FILENO);
//    close(rgen_a1[0]);
//    close(rgen_a1[1]);
    
//    dup2(a1_a2[0], STDIN_FILENO);
//    close(a1_a2[0]);
//    close(a1_a2[1]);
//    while(!std::cin.eof()){
//        std::string line;
//        std::getline(std::cin, line);
//        std::cout<< line << std::endl;
//    }

    
    for (pid_t k : kids) {
        int status;
        //kill(k, SIGTERM);

        waitpid(k, &status, 0);
    }
    return 0;
}
