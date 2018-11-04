//
//  a3-ece650.cpp
//  test
//
//  Created by Bu's love on 2018/10/29.
//  Copyright © 2018年 DanWang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int spawn (char* program, char** arg_list)
{
    pid_t child_pid;
    
    /* Duplicate this process.  */
    child_pid = fork ();
    if (child_pid != 0)
    /* This is the parent process.  */
        return child_pid;
    else {
        /* Now execute PROGRAM, searching for it in the path.  */
        execvp (program, arg_list);
        /* The execvp function returns only if an error occurs.  */
        fprintf (stderr, "an error occurred in execvp\n");
        abort ();
    }
}


int main(){
    int rgen_a1[2];
    int a1_a2[2];
    
    pipe(rgen_a1);
    pipe(a1_a2);
    
    dup2(rgen_a1[1], STDIN_FILENO);
    
}
