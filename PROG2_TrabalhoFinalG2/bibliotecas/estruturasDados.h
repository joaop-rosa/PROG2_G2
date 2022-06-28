//
// Created by jprag on 25/06/2022.
//
#ifndef PROG2_TRABALHOFINALG2_ESTRUTURASDADOS_H
#define PROG2_TRABALHOFINALG2_ESTRUTURASDADOS_H
typedef struct personagem PERSONAGEM;
struct personagem {
    char nome[50];
    char raca[50];
    char classe[50];
    int forca;
    int defesa;
    int vida;
    int nivel;
};
typedef struct monstro MONSTRO;
struct monstro {
    int id;
    char nome[50];
    int forca;
    int defesa;
    int vida;
    int recompencaNivel;
};
typedef struct missao MISSAO;
struct missao {
    int id;
    char nome[50];
    int seqInimigos[50];
    int recompencaNivel;
};
#endif //PROG2_TRABALHOFINALG2_ESTRUTURASDADOS_H
