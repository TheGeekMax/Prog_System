//
// Created by Maxime Sanciaume on 07/10/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

void exo61() {
    int pid = fork();
    if(pid == 0) {
        printf("pid du child : %d\n",getpid());
        printf("ppid du child : %d\n", getppid());
        exit(getpid()%10);
    }
    // ici c'est le papa

    printf("pid du child (venant du papa) : %d\n",pid);
    int r_value = 0;
    wait(&r_value);
    printf("valeur de retour : %d\n",WEXITSTATUS (r_value));
}

void exo62(int n) {
    int finished = 0;
    for(int i = 0; i < n; i ++) {
        int pid = fork();
        if(pid == 0) {
            exit(0);
        }
    }

    while(finished < n) {
        int end_pid = wait(NULL);
        printf("procesus terminé : %d\n",end_pid);
        finished ++;
    }
}

void exo63(int n, int m) {
    for(int prof = 0; prof < m; prof ++) {
        for(int i = 0; i < n; i ++) {
            fork();
        }
    }
    printf("proc ended\n");

}

void exo64(char* filename) {
    int f = open(filename,O_RDONLY);
    fork();
    char* buffer = malloc(sizeof(char));
    while(read(f,buffer,1) > 0) {
        printf("%c",buffer[0]);
    }
    free(buffer);
}

void exo65(char* path) {

}

void exo66() {

}

void exo67() {

}

void exo68() {

}

void exo69() {

}

void exo610() {

}

void exo611() {

}

void exo612() {

}