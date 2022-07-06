//
// Created by jprag on 26/06/2022.
//
#include <stdio.h>
#include "bibliotecas/estruturasDados.h"
#include "bibliotecas/personagens.h"
#include "stdlib.h"

int calculoBatalha(PERSONAGEM personagem, MONSTRO monstro, int monstroAtacante) {
    //ROLAR O D20
    int d20 = (rand() % 20) + 1;
    int danoAtaque, primeiroD6,segundoD6;
    printf("Valor D20 rolado: %d\n", d20);
    //IF MONSTRO ATACANTE
    if (monstroAtacante == 1) {
        if (d20 + calcularModificador(monstro.forca) > personagem.defesa) {
            //dano de ataque é igual a 2d6 + modificador de ataque
            primeiroD6 = (rand() % 6) + 1;
            printf("Primeiro d6 rolado: %d\n",primeiroD6);
            segundoD6 = (rand() % 6) + 1;
            printf("Segundo d6 rolado: %d\n",segundoD6);
            danoAtaque = (primeiroD6+segundoD6);
            danoAtaque += calcularModificador(monstro.forca);
            if(d20 == 20){
                danoAtaque *= 2;
            }
            return danoAtaque;
        } else {
            printf("ATAQUE DE %s FOI BLOQUEADO POR %s\n", monstro.nome,
                   personagem.nome);
            return 0;
        }
    } else {
        if (d20 + calcularModificador(personagem.forca) > monstro.defesa) {
            //dano de ataque é igual a 2d6 + modificador de ataque
            primeiroD6 = (rand() % 6) + 1;
            printf("Primeiro d6 rolado: %d\n",primeiroD6);
            segundoD6 = (rand() % 6) + 1;
            printf("Segundo d6 rolado: %d\n",segundoD6);
            danoAtaque = (primeiroD6+segundoD6);
            danoAtaque += calcularModificador(personagem.forca);
            return danoAtaque;
        } else {
            printf("ATAQUE DE %s FOI BLOQUEADO POR %s\n", personagem.nome,
                   monstro.nome);
            return 0;
        }
    }


}

PERSONAGEM batalha(PERSONAGEM personagem, MONSTRO monstro,int ifMissao) {
    int vidaPersonagem = personagem.vida;
    int rodada = 1, calculo;
    while (personagem.vida > 0 && monstro.vida > 0) {
        system("cls");
        printf("=================================\n");
        printf("%s - VIDA: %d - MOD. DE FORCA: %d - DEFESA: %d\n", personagem.nome, personagem.vida,
               calcularModificador(personagem.forca), personagem.defesa);
        printf("=================================\n");
        printf("%s - VIDA: %d - MOD. DE FORCA: %d - DEFESA: %d\n", monstro.nome, monstro.vida, calcularModificador(monstro.forca),
               monstro.defesa);
        printf("=================================\n");
        printf("RODADA: %d\n\n", rodada);
        if (rodada % 2 == 0) {
            //RODADA MONSTRO
            calculo = calculoBatalha(personagem, monstro, 1);
            personagem.vida -= calculo;
            printf("%s CAUSOU %d de dano ao %s\n", monstro.nome, calculo, personagem.nome);
        } else {
            //RODADA PERSONAGEM
            calculo = calculoBatalha(personagem, monstro, 0);
            monstro.vida -= calculo;
            printf("%s CAUSOU %d de dano ao %s\n", personagem.nome, calculo, monstro.nome);
        }
        rodada++;
        printf("Precione qualquer tecla para continuar\n");
        getchar();
    }
    system("cls");
    if (personagem.vida > 0) {
        printf("%s VENCEU :)\n", personagem.nome);
        personagem.vida = vidaPersonagem;
        printf("%s subiu %d nivel! Parabens!\n",personagem.nome,monstro.recompencaNivel);
        printf("Precione qualquer tecla para continuar\n");
        getchar();
        return subirNivelPersonagem(personagem, monstro.recompencaNivel);
    } else {
        printf("%s FOI DERROTADO :(\n", personagem.nome);
        if (ifMissao == 1){
            return personagem;
        }
        personagem.vida = vidaPersonagem;
        printf("Precione qualquer tecla para continuar\n");
        getchar();
        return personagem;
    }
}

