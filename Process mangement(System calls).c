#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
int main() {
    int pid;
    int status;
    printf("Parent Process: PID = %d\n", getpid());
    pid = fork();
    if (pid < 0)
    {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) 
    {
        printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);
        perror("Execvp failed");
        exit(1);
    }
    else 
    {
        printf("Parent Process: Created child with PID = %d\n", pid);
        wait(&status);
        if (WIFEXITED(status)) 
        {
            printf("Parent Process: Child process exited with status %d\n", WEXITSTATUS(status));
        } else 
        {
            printf("Parent Process: Child process terminated abnormally.\n");
        }
        kill(pid, SIGKILL);
        printf("Parent Process: Killed child process with PID = %d\n", pid);
        printf("Parent Process: Terminating...\n");
        exit(0);
    }
    return 0;
}

