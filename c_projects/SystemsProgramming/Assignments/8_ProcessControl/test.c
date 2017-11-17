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

/* Standard file descriptors.  */
#define STDIN_FILENO    0       /* Standard input.  */
#define STDOUT_FILENO   1       /* Standard output.  */
#define STDERR_FILENO   2       /* Standard error output.  */

/**********************************************************************
int concCmd (Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt)
Purpose:    
    To run up to 5 set of commands concurrently that are not data dependent.

Command Parameters:
    Cmd cmM[]       - Arrary of structures holding relevant command information
    int iCmdCnt     - Holds the number of commands
    Token tokeM[]   - Arrary of structures holding parsed token information inputted by user
    iTokenCnt       - Number of tokens 
Input:
    Lines of text containing conc commands:
    conc cmd1 args1 , cmd2 args2 , ...
        conc causes PELL to execute the commands concurrently (i.e., parallel).  
        There is no communication between the commands, these simply happen
        concurrently (in parallel).  
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
        - Returns 0 if commands were completed successfully to completion
Notes:
    We print the parent PID and child PID information to stderr to not
    interfere with stdout.
**********************************************************************/
int concCmd (Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt) {
    int i;
    // printf("Commands: %d, Tokens: %d\n", iCmdCnt, iTokenCnt);
    // printf("Command  ArgBeg   ArgEnd  Redirect(in/out)  ->   Path\n");
    
    for (i = 0; i < iCmdCnt; i +=1)
    {
        // Declare variables for each child process
        long lForkPid, lWaitPid;
        int iExitStatus = 0;
        char szInput[20];
        char *execArgv[20];
        char *redirPathIN, *redirPathOUT; //tokenM[cmdM[i].iStdoutRedirectIdx] : tokenM[cmdM[i].iStdinRedirectIdx];
        int iRedirIN = cmdM[i].iStdinRedirectIdx;
        int iRedirOUT = cmdM[i].iStdoutRedirectIdx;
        
        // printf("%5s %6s %11s %5d / %2d ->%20s\n"
        //     , cmdM[i].szCmdNm, tokenM[cmdM[i].iBeginIdx], tokenM[cmdM[i].iEndIdx]
        //     , cmdM[i].iStdinRedirectIdx, cmdM[i].iStdoutRedirectIdx, tokenM[cmdM[i].iStdoutRedirectIdx]);
    
        // create a child process
        lForkPid = fork();  
        // Both the parent and child continue here
        switch(lForkPid)
        {
            case -1:
                errExit("fork failed: %s", strerror(errno));
                break;
            case 0:  ;// child process, empty statement               
                int ifileIN, ifileOUT, k, iCnt = 1;
                // Check for redirected input or output
                if(iRedirOUT) {
                    // Redirect stdout to file
                    redirPathOUT = tokenM[cmdM[i].iStdoutRedirectIdx];
                    ifileOUT = open(redirPathOUT, O_CREAT | O_WRONLY | O_EXCL, 0666); // output file
                    if(ifileOUT < 0) {
                        errExit("file open failed: %s", strerror(errno));
                    }
                    //Now we redirect standard output to the file using dup2
                    if(dup2(ifileOUT, STDOUT_FILENO) < 0) {
                        errExit("redirecting stdout failed: %s", strerror(errno));
                    }
                }
                if(iRedirIN) {
                    // Redirect stdin to file
                    redirPathIN = tokenM[cmdM[i].iStdinRedirectIdx];
                    ifileIN = open(redirPathIN, O_RDONLY, 0666); // output/input file
                    if(ifileIN < 0) {
                        errExit("file open failed: %s", strerror(errno));
                    }
                    //Now we redirect standard input to the file using dup2
                    if(dup2(ifileIN, STDIN_FILENO) < 0) {
                        errExit("redirecting stdin failed: %s", strerror(errno));
                    }
                }

                execArgv[0] = cmdM[i].szCmdNm; // command
                // For loop begin arg index -> last arg index
                for(k = cmdM[i].iBeginIdx; k <= cmdM[i].iEndIdx; k++) {
                    execArgv[iCnt] = tokenM[k]; // arg list
                    // printf("iCnt: %d, token: %s\n", iCnt, tokenM[k]);
                    iCnt++;
                }
                execArgv[iCnt] = NULL; // null
                execvp(cmdM[i].szCmdNm, execArgv); // command
                if(iRedirOUT) {
                    close(ifileOUT);
                }
                if(iRedirOUT) {
                    close(ifileIN);
                }
                errExit("Child process failed to exec: %s", strerror(errno));
            default: // parent process
                lWaitPid = wait (&iExitStatus);
                if (lWaitPid == -1)
                    errExit("wait error: %s", strerror(errno));
                
                int j;
                if(cmdM[i].iBeginIdx > 0){
                    printf("%ld %ld", (long) getpid(), lForkPid); // parent PID, child PID, command
                    for(j = cmdM[i].iBeginIdx-1; j < cmdM[i].iStdoutRedirectIdx+1; j++){
                        printf(" %s", tokenM[j]);
                    }
                    printf("\n");
                }
                else{
                    printf("%ld %ld %s\n", (long) getpid(), lForkPid, cmdM[i].szCmdNm);
                }
                
        }  
    }
    // Exit out of child concurrent executions successfully
    return 0;
}

/**********************************************************************
int pipeCmd (Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt)
Purpose:    
    Uses pipes to execute commands in parallel that are data dependent. 

Command Parameters:
    Command Parameters:
    Cmd cmM[]       - Arrary of structures holding relevant command information
    int iCmdCnt     - Holds the number of commands
    Token tokeM[]   - Arrary of structures holding parsed token information inputted by user
    iTokenCnt       - Number of tokens 
Input:
    Lines of text containing pipe commands: 
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
          pipeCmd, for each child:
              - prints step, parent PID, child Pid, and the command
                Example:
                1 33043 33045: ls -l Data
                2 33043 33046: sort -k5 -n
        - Returns 0 if commands were completed successfully to completion
Notes:
    We print the parent PID and child PID information to stderr to not
    interfere with stdout.
**********************************************************************/

int pipeCmd (Cmd cmdM[], int iCmdCnt, Token tokenM[], int iTokenCnt) {
    long lForkPidLs, lForkPidSort;
    int iExitStatus = 0;    // Used by parent to get status of child
    long lWaitPid;          // PID of child that terminated
    int iReadFd, iWriteFd;  // File Descriptors for reader and writer
    int fdM[2];             // contains file descriptors for the pipe
    char *execArgv[20];
    char *redirPath1,*redirPath2;
    int iFileRead, iFileWrite; // to read and write files

    // check if too many commands entered
    if (iCmdCnt > 2)
        errExit("Too many commands to pipe");
    // create the pipe
    if (pipe(fdM) == -1)
        errExit("pipe not created: %s", strerror(errno));
    lForkPidLs = fork();    // create a child process 
    iReadFd = fdM[0];       // reader file descriptor
    iWriteFd = fdM[1];      // writer file descriptor
    // Both the parent and first child continue here
    switch(lForkPidLs) {
        case -1:
            errExit("fork failed: %s", strerror(errno));
        case 0:  ;// child process1
            int iCnt = 1, k;
            // Redirect stdin to file
            if(cmdM[0].iStdinRedirectIdx > 0) {
                redirPath1 = tokenM[cmdM[0].iStdinRedirectIdx];
                iFileRead = open(redirPath1, O_RDONLY, 0666); // output/input file
                if(iFileRead < 0) {
                    errExit("file open failed: %s", strerror(errno));
                }
                //Now we redirect standard input to the file using dup2
                if(dup2(iFileRead, STDIN_FILENO) < 0) {
                    errExit("redirecting stdin failed: %s", strerror(errno));
                }
            }
            // Redirect stdout to pipe
            if ( dup2(iWriteFd, STDOUT_FILENO) == -1)
                errExit("Failed to rediect stdout: %s", strerror(errno));
            close(iReadFd); close(iWriteFd); // Close read and write file descriptors for pipe
            execArgv[0] = cmdM[0].szCmdNm; // Get command
            // For loop begin arg index -> last arg index
            for(k = cmdM[0].iBeginIdx; k <= cmdM[0].iEndIdx; k++) {
                execArgv[iCnt] = tokenM[k]; // arg list
                // printf("iCnt: %d, token: %s\n", iCnt, tokenM[k]);
                iCnt++;
            }
            execArgv[iCnt] = NULL; // End of command args
            execvp(cmdM[0].szCmdNm, execArgv); // execute command with args
            errExit("Failed to exec: %s", strerror(errno));
        default: // parent process
            // create the other child
            lForkPidSort = fork(); 
            // Both the parent and second child continue here
            switch(lForkPidSort) {
                case -1:
                    errExit("fork of second child failed: %s"
                        , strerror(errno));
                case 0:  ;// child process2
                    int iCnt = 1, k;
                    char *execArgv[20];
                    // Redirect stdout to file
                    if(cmdM[1].iStdoutRedirectIdx) {
                        redirPath2 = tokenM[cmdM[1].iStdoutRedirectIdx];
                        iFileWrite = open(redirPath2, O_CREAT | O_WRONLY | O_EXCL, 0666); // output file
                        if(iFileWrite < 0) {
                            errExit("file open failed: %s", strerror(errno));
                        }
                        //Now we redirect standard output to the file using dup2
                        if(dup2(iFileWrite, STDOUT_FILENO) < 0) {
                            errExit("redirecting stdout failed: %s", strerror(errno));
                        }
                    }
                    // redirect stdin to pipe so command can read from pipe
                    if ( dup2(fdM[0], STDIN_FILENO) == -1)
                        errExit("Failed to rediect stdin: %s", strerror(errno));
                    close(fdM[0]); close(fdM[1]);
                    execArgv[0] = cmdM[1].szCmdNm; // 2nd command
                    // For loop begin arg index -> last arg index
                    for(k = cmdM[1].iBeginIdx; k <= cmdM[1].iEndIdx; k++) {
                        execArgv[iCnt] = tokenM[k]; // arg list
                        // printf("iCnt: %d, token: %s\n", iCnt, tokenM[k]);
                        iCnt++;
                    }
                    execArgv[iCnt] = NULL; // null
                    execvp(cmdM[1].szCmdNm, execArgv); // execute command
                    errExit("Failed to exec: %s", strerror(errno));
                default:  // parent process
                    close(fdM[0]); close(fdM[1]); // close pipe file descriptors
                    // fprintf(stderr, "PID: %ld, Parent: %ld, Child: %ld\n"
                    //     , (long) getpid(), lForkPidLs, lForkPidSort);   
                    // Print PIDs and associated commands 
                    printf("1 %ld %ld %s\n", (long) getpid(), lForkPidLs, cmdM[0].szCmdNm);
                    printf("2 %ld %ld %s\n", (long) getpid(), lForkPidSort, cmdM[1].szCmdNm);
                    
                    fflush(stderr);
                    int i;
                    for (i = 0; i < 2; i+=1) { // Wait for children to finish executing
                        iExitStatus = 0;
                        lWaitPid = wait(&iExitStatus); 
                        if (lWaitPid == -1)
                            errExit("wait failed: %s\n"
                                , strerror(errno));
                        // if (lWaitPid == lForkPidLs)
                        //     fprintf(stderr,"First child terminated\n");
                        // else
                        //     fprintf(stderr,"Second child terminated\n");
                        fflush(stderr);
                    } 
                    if(cmdM[0].iStdinRedirectIdx > 0) close(iFileRead);
                    if(cmdM[1].iStdoutRedirectIdx > 0) close(iFileWrite);
                    fprintf(stderr,"complete\n");
            }
    }
    // Pipe execution completed successfully
    return 0;
}
