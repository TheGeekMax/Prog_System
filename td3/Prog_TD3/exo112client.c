//
// Created by Maxime Sanciaume on 14/10/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>

#define TAILLE 100

int main(int argc, char* argv[]){
    //ouvre la file de message IPC avec un nom de fichier "/etc/passwd" et une cle 'E'
    int fid = ftok("/etc/passwd", (int)'E');
    int msgid = msgget(fid, IPC_CREAT | 0666);

    if (argc == 1){
        msgsnd(msgid, "", TAILLE, 0);
        exit(0);
    }

    if (argc == 3){
       //concat les deux arguments
        char message[TAILLE];
        strcpy(message, argv[1]);
        strcat(message, argv[2]);
        msgsnd(msgid, message, TAILLE, 0);
        exit(0);
    }
}