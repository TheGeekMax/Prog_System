//
// Created by Maxime Sanciaume on 07/10/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUFFER 1024

void copier(int fdsrc,int fddst) {
    char* buffer = malloc(sizeof(char)*MAX_BUFFER);
    int len = read(fddst,buffer,MAX_BUFFER);
    write(fddst,buffer,len);
}

void exo81() {
    int tube[2];
    pipe(tube);

    int pid = fork();

    if(pid == 0) {
        //je suis dans le processus enfant
        copier(tube[0],STDOUT_FILENO);
        exit(0);
    }else {
        //je suis dans le processus parrent
        copier(STDIN_FILENO,tube[1]);
        wait(NULL);
    }
}

void exo82(int n) {
    int** tubes = malloc(sizeof(int*)*(n-1));

    //init des tubes
    for(int i = 0; i < n-1; i ++) {
        tubes[i] = malloc(sizeof(int)*2);
        pipe(tubes[i]);
    }

    //init des forks
    int index = -1;
    for(int i = 0; i < n-1; i ++) {
        int pid = fork();
        if(pid == 0) {
            //c'est un enfant
            index = i;
            i = n;
        }
    }

    if(index == -1) {
        //proc parrent
        for(int q = 0; q < n-1; q++) {
            wait(NULL);
            copier(tubes[n-2][0],STDOUT_FILENO);
        }
    }else if(index == 0){
        copier(STDIN_FILENO,tubes[0][1]);
    }else {
        copier(tubes[index-1][0],tubes[index][1]);
    }

}