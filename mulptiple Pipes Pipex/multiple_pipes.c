#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROCESS_NUM 10

int main(int argc, char* argv[]) 
{
    int pids[PROCESS_NUM];
    int pipes[PROCESS_NUM + 1][2];
    int i;
    //creating pipes
    for (i = 0; i < PROCESS_NUM + 1; i++) 
    {
        if (pipe(pipes[i]) == -1) 
        {
            printf("Error with creating pipe\n");
            return 1;
        }
    }
    //creating forks
    for (i = 0; i < PROCESS_NUM; i++) 
    {
        pids[i] = fork();
        if (pids[i] == -1) 
        {
            printf("Error with creating process\n");
            return 2;
        }
        if (pids[i] == 0) 
        {
            // Child process closing unused pipes before start
            int j;
            for (j = 0; j < PROCESS_NUM + 1; j++) 
            {
                if (i != j) 
                {
                    close(pipes[j][0]);
                }
                if (i + 1 != j) 
                {
                    close(pipes[j][1]);
                }
            }
            //Child process creating a variable to store read from main process
            int x;
            if (read(pipes[i][0], &x, sizeof(int)) == -1) 
            {
                printf("Error at reading\n");
                return 3;
            }
            printf("(%d) Got %d\n", i, x);
            //Child process increments the variable and writes it into the pipe
            x++;
            if (write(pipes[i + 1][1], &x, sizeof(int)) == -1) 
            {
                printf("Error at writing\n");
                return 4;
            }
            printf("(%d) Sent %d\n", i, x);
            //closes pipe end after use so next process child can continue
            close(pipes[i][0]);
            close(pipes[i + 1][1]);
            return 0;
        }
    }

    // Main process closes pipe not in use
    int j;
    for (j = 0; j < PROCESS_NUM + 1; j++) 
    {
        if (j != PROCESS_NUM) 
        {
            close(pipes[j][0]);
        }
        if (j != 0) {
            close(pipes[j][1]);
        }
    }
    // Main populates declares && initalizes variable and writes into pipe
    int y = 5;
    printf("Main process sent %d\n", y);
    if (write(pipes[0][1], &y, sizeof(int)) == -1) 
    {
        printf("Error at writing\n");
        return 4;
    }
    // Main reads variable from pipe
    if (read(pipes[PROCESS_NUM][0], &y, sizeof(int)) == -1) 
    {
        printf("Error at reading\n");
        return 3;
    }
    // Main prints final result
    printf("The final result is %d\n", y);
    // Main closes pupe after use
    close(pipes[0][1]);
    close(pipes[PROCESS_NUM][0]);
    // Main waits for all its children
    for (i = 0; i < PROCESS_NUM; i++) 
    {
        wait(NULL);
    }
    return 0;
}

