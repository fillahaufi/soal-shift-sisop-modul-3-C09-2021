#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int pid;
int pipe_[2][2];

void showPrc() {
    dup2(pipe_[0][1], 1);

    // close fds
    close(pipe_[0][0]);
    close(pipe_[0][1]);
    execlp("ps", "ps", "-aux", NULL);
    exit(EXIT_SUCCESS);
}

void sortPrc() {
    dup2(pipe_[0][0], 0);
    dup2(pipe_[1][1], 1); 

    // close fds
    close(pipe_[0][0]);
    close(pipe_[0][1]);
    close(pipe_[1][0]);
    close(pipe_[1][1]);

    execlp("sort", "sort", "-nrk", "3,3", NULL);
    exit(EXIT_SUCCESS);
}

void fivePrc() {
    dup2(pipe_[1][0], 0);

    // close fds
    close(pipe_[1][0]);
    close(pipe_[1][1]);
    
    execlp("head", "head", "-5", NULL);
    exit(EXIT_SUCCESS);
}

int main() {
    if(pipe(pipe_[0]) == -1){
        perror("ERROR gaes");
        exit(EXIT_FAILURE);
    }

    if(fork() == 0) showPrc();

    if(pipe(pipe_[1]) == -1){
        perror("ERROR gaes");
        exit(EXIT_FAILURE);
    }
    if(fork() == 0) sortPrc();

    close(pipe_[0][0]);
    close(pipe_[0][1]);

    if(fork() == 0) fivePrc();
}
