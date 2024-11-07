//
// Created by Maxime Sanciaume on 09/10/2024.
//
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void raler(char * value) {
    printf("Z! ");
    printf(value);
    printf("\n");
}

//EXO 9.1

int current = 0;
int next = 1;

void exoCallback() {
    if(current < 5) current ++;
}

void exo91() {
    struct sigaction call = {
        &exoCallback,
        0,
        0
    };

    sigaction(SIGINT,&call,NULL);
    while(next < 5) {
        if(current != next){
            next = current;
            printf("%d\n",current);
        }
    }
}

//exo 9.2
int *tab;

void b92() {
    for(int i = 0 ;1;i++) {
        tab[i] = 1;
    }
}

void a92() {
    b92();
}

void exo92() {
    execl("unlimit","-c","unlimited");

    //programme de generation de segfault
    tab = malloc(sizeof(int)*10);
    a92();
}

//exo 9.3
void exo93Callback() {
    psignal(0,NULL);
    exit(0);
}

void exo93() {
    for(int i = 0; i <= 255; i ++) {
        struct sigaction call = {
            (&exo93Callback),
            0,
            0
        };

        sigaction(i,&call,NULL);
    }
    while(1){}
}
//exo 9.4

int globalPid = 0;

void traite() {
    printf("Hello World !\n");
}
void killCallback() {
    exit(0);
}

void child() {
    traite();
    alarm(1);
}

void parent() {
    if(kill(globalPid,SIGUSR1) != 0) {
        raler("KILL problème");
    }
    exit(0);
}



void exo94() {
    //creer le proc fils
    globalPid = fork();

    if(globalPid == 0) {
        //enfant
        struct sigaction killC = {
            (&killCallback),
            0,
            0
        };

        if( sigaction(SIGUSR1,&killC,NULL) == -1) {
            raler("SIGACTION problème");
        }


        struct sigaction childC = {
            (&child),
            0,
            0
        };

        if( sigaction(SIGALRM,&childC,NULL) == -1) {
            raler("SIGACTION problème");
        }


        alarm(1);
        while(1){}
        exit(0);
    }else {
        //parent
        struct sigaction parentC = {
            (&parent),
            0,
            0
        };

        if( sigaction(SIGALRM,&parentC,NULL) == -1) {
            raler("SIGACTION problème");
        }
        alarm(60);

        while(1){}
    }
}

//exo 9.5
