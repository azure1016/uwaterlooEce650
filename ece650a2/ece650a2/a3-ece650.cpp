
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
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

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
        //redirect rgen's output to write-end; in other words, rgen wanna write
        dup2(rgen_a1[1], STDOUT_FILENO);
        close(rgen_a1[0]);
        close(rgen_a1[1]);
        //char* arg_list[2] = {(char*)"rgen", nullptr};
        execvp("./rgen", argv);
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
       
        char* arg_list[4] = {(char*)"python",
            (char*)"-u",
            (char*)"a1ece650.py",
            nullptr
        };
        execvp("python", arg_list);
        std::cerr << "Error: an error occurred in execv" << std::endl;
    }
    
    kids.push_back(child_pid);
    
    
    child_pid = fork();
    
    if (child_pid == 0){
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
    
    
    
    dup2(a1_a2[1], STDOUT_FILENO);
    close(a1_a2[0]);
    close(a1_a2[1]);
    while (!std::cin.eof()){
        std::string line;
        std::getline(std::cin, line);
        if (line.size () > 0)
           std::cout << line << std::endl;
    }
    
    
    
    for (pid_t k : kids) {
        int status;
        kill(k, SIGTERM);

        waitpid(k, &status, 0);
    }
    return 0;
}
