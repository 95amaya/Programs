/**********************************************************************
cs3723p8.c by Michael Amaya
Purpose:    
    This file will implement the concCmd and pipeCmd functions.  

Command Parameters:
    pell < commandFile
Input:
    Lines of text containing conc or pipe commands:
    conc cmd1 args1 , cmd2 args2 , ...
        conc causes PELL to execute the commands concurrently (i.e., parallel).  
        There is no communication between the commands, these simply happen
        concurrently (in parallel).  
    pipe cmd1 args1 , cmd2 args2 
        pipe causes PELL to create a pipe and fork a child for each cmdi.  
        The pipe is the output for step 1 and the input for step 2.  Also,
        cmd1 can have stdin redirected from a file.  cmd2 can have stdout 
        redirected to a file.  
Results:
    For each command read from stdin:
        - Prints the tokens
        - Prints the command information
        - Depending on the command:
          concCmd:
              - prints the parent PID, child PID, and the command
                Example:
                33009 33011: ls -l /bin > lsOne.txt
                33009 33012: ls -l /usr/bin > lsTwo.txt
                33009 33013: ls -l  /etc > lsThree.txt
          pipeCmd, for each child:
              - prints step, parent PID, child Pid, and the command
                Example:
                1 33043 33045: ls -l Data
                2 33043 33046: sort -k5 -n
Notes:
    We print the parent PID and child PID information to stderr to not
    interfere with stdout.
**********************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include "cs3423p8.h"

int concCmd (Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt) {
    int i, j;
    printf("Commands: %d, Tokens: %d\n", iCmdCnt, iTokenCnt);
    printf("Cmd: %s\n", cmdM[0].szCmdNm);
    
    // for (i = 1; i < iTokenCnt; i++)
    //     printf("  %3d '%s'\n", i, tokenM[i]);
    
    printf("Command  ArgBeg   ArgEnd  Redirect(in/out)  ->   Path\n");
    for (i = 0; i < iCmdCnt; i +=1)
    {
        printf("%5s %6s %11s %5d / %2d ->%20s\n"
            , cmdM[i].szCmdNm, tokenM[cmdM[i].iBeginIdx], tokenM[cmdM[i].iEndIdx]
            , cmdM[i].iStdinRedirectIdx, cmdM[i].iStdoutRedirectIdx, tokenM[cmdM[i].iStdoutRedirectIdx]);
    
        // start code
        long lForkPid;
        long lWaitPid;
        int iExitStatus = 0;
        char szInput[20];
        char *execArgv[20];
        char *redirPath = tokenM[cmdM[i].iStdoutRedirectIdx];
        // char cmd[500]; 
        // strcpy(cmd, cmdM[i].szCmdNm);
        // create a child process
        lForkPid = fork();  

        // Both the parent and child continue here
        switch(lForkPid)
        {
            case -1:
                errExit("fork failed: %s", strerror(errno));
                break;
            case 0:  ;// child process, empty statement
                // printf("Child Process: PID=%ld, PPID=%ld\n"
                //     , (long) getpid(), (long) getppid());
                // Redirect stdout to file
                int file = open(redirPath, O_CREAT | O_WRONLY, 0666); // output file
                if(file < 0)    
                {
                    printf("File open error\n");
                    return 1;
                }
                //Now we redirect standard output to the file using dup2
                if(dup2(file,1) < 0)
                {
                    printf("Dup error exit\n");   
                    return 1;
                }
                // invoke a different executable for the child
                execArgv[0] = cmdM[i].szCmdNm; // command
                // For loop begin index -> end index
                execArgv[1] = tokenM[cmdM[i].iBeginIdx]; // flag list
                execArgv[2] = tokenM[cmdM[i].iEndIdx]; // path
                execArgv[3] = NULL; // null
                execvp(cmdM[i].szCmdNm, execArgv); // command
                close(file);
                errExit("Child process failed to exec: %s", strerror(errno));
            default: // parent process
                lWaitPid = wait (&iExitStatus);
                if (lWaitPid == -1)
                    errExit("wait error: %s", strerror(errno));
                // printf("Parent Process: PID=%ld, PPID=%ld\n"
                //     , (long) getpid(), (long) getppid());
                // printf("Parent Process: my child's PID=%ld\n"
                //     , lForkPid);
                // printf("Parent Process: wait pid=%ld\n"
                //     , lWaitPid);
                // printf("Parent Process: exit status=%d\n"
                //     , iExitStatus);
                printf("%ld %ld", (long) getpid(), lForkPid); // parent PID, child PID, command
                
                for(j = cmdM[i].iBeginIdx-1; j < cmdM[i].iStdoutRedirectIdx+1; j++){
                    printf(" %s", tokenM[j]);
                }
                printf("\n");
        }
        // printf("My PID=%ld\n"
        //     , (long) getpid());    
    }
    return 0;
}


int pipeCmd (Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt) {
    return 0;
}
