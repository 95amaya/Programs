#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main ()
{
    long lForkPid;
    long lWaitPid;
    int iExitStatus = 0;
    char szInput[20];
    char *execArgv[20];
    // create a child process
    lForkPid = fork();  

    // Both the parent and child continue here
    switch(lForkPid)
    {
        case -1:
            errExit("fork failed: %s", strerror(errno));
            break;
        case 0:  // child process
            printf("Child Process: PID=%ld, PPID=%ld\n"
                 , (long) getpid(), (long) getppid());
            // Redirect stdout to file
            int file = open("myfile.txt", O_CREAT | O_WRONLY, 0666); //O_APPEND
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
            execArgv[0] = "ls";
            execArgv[1] = "-l";
            execArgv[2] = "/bin";
            execArgv[3] = NULL;
            execvp("ls", execArgv);
            close(file);
            errExit("Child process failed to exec: %s", strerror(errno));
        default: // parent process
            lWaitPid = wait (&iExitStatus);
            if (lWaitPid == -1)
                errExit("wait error: %s", strerror(errno));
            printf("Parent Process: PID=%ld, PPID=%ld\n"
                 , (long) getpid(), (long) getppid());
            printf("Parent Process: my child's PID=%ld\n"
                 , lForkPid);
            printf("Parent Process: wait pid=%ld\n"
                 , lWaitPid);
            printf("Parent Process: exit status=%d\n"
                 , iExitStatus);
    }
    printf("My PID=%ld\n"
         , (long) getpid());
    return 0;
}
