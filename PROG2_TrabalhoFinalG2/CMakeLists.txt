cmake_minimum_required(VERSION 3.21)
project(PROG2_TrabalhoFinalG2 C)

set(CMAKE_C_STANDARD 99)

add_executable(PROG2_TrabalhoFinalG2 main.c bibliotecas/personagens.h personagens.c bibliotecas/estruturasDados.h bibliotecas/monstros.h monstros.c bibliotecas/batalha.h batalha.c bibliotecas/missoes.h missoes.c)
