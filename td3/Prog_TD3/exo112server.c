//
// Created by Maxime Sanciaume on 14/10/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

#define TAILLE 100

void traite(char* message){
    printf("Message recu: %s\n", message);
}

int main(){
    //creer une file de message IPC
    int fid = ftok("/etc/passwd", (int)'E');
    int msgid = msgget(fid, IPC_CREAT | 0666);

    char message[TAILLE] = ".";
    while(message[0] != '\0'){
        //recevoir un message de la file de message
        msgrcv(msgid, message, TAILLE, 0, 0);
        traite(message);
    }
    //detruire la file de message
    msgctl(msgid, IPC_RMID, NULL);
}