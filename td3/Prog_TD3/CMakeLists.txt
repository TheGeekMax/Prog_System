cmake_minimum_required(VERSION 3.29)
project(Prog_TD3 C)

set(CMAKE_C_STANDARD 11)

#add_executable(Prog_TD3 main.c
#        exo11.h
#        exo11.c)

add_executable(Prog_TD3_exo112Serveur
        exo112server.c)

add_executable(Prog_TD3_exo112Client
        exo112client.c)