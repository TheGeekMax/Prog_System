//
// Created by Maxime Sanciaume on 14/10/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

#define MESSAGE_LENGTH 100


void exo111() {
    //setup de la file de message
    int msgid = msgget(IPC_PRIVATE, 0600);

    //creation du fils
    int pid = fork();
    if (pid == 0) {
        //fils
        char message[MESSAGE_LENGTH] = ".";
        int recieved = 0;

        while (message[0] != '\n'){
            msgrcv(msgid, message, MESSAGE_LENGTH, 0, 0);
            printf("Fils: %s", message);
            //compte le nombre d'octet recu
            int i = 0;
            while (message[i] != '\0'){
                i++;
            }
            recieved += i;
        }
        //stop le fils
        printf("nombre d'octet recu : %d", recieved);
        exit(0);
    }
    //pere
    char message[MESSAGE_LENGTH];
    while (message[0] != '\n'){
        fgets(message, MESSAGE_LENGTH, stdin);
        msgsnd(msgid, message, MESSAGE_LENGTH, 0);
    }
    //attente de la fin du fils
    wait(NULL);
    msgctl(msgid, IPC_RMID, NULL);
}