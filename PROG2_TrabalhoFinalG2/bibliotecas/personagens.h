//
// Created by jprag on 25/06/2022.
//
#ifndef PROG2_TRABALHOFINALG2_PERSONAGENS_H
#define PROG2_TRABALHOFINALG2_PERSONAGENS_H
#include "estruturasDados.h"
int calcularModificador(int atributo);
PERSONAGEM criarPersonagem();
void salvarNovoPersonagem(PERSONAGEM personagem);
PERSONAGEM carregarPersonagem(int numeroPersonagens);
int lerPersonagens();
PERSONAGEM subirNivelPersonagem(PERSONAGEM personagemAlterado, int nivel);

#endif //PROG2_TRABALHOFINALG2_PERSONAGENS_H
