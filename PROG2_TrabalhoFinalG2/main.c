#include <stdio.h>
#include <stdlib.h>
#include "bibliotecas/personagens.h"
#include "bibliotecas/estruturasDados.h"
#include "bibliotecas/monstros.h"
#include "bibliotecas/batalha.h"
#include "bibliotecas/missoes.h"


int main() {
    int resp, resp2;
    int entradaValida;
    struct personagem personagemSelecionado;
    struct monstro monstroSelecionado;
    struct missao missaoSelecionada;

    //tela inicial//
    do {
        int retornoCarregamentoPersonagens = lerPersonagens();
        printf("BEM-VINDO AO RPG\n");
        printf("---------------------------------\n\n");
        printf("SELECIONE A OPCAO DESEJADA\n\n");
        printf("1- CRIAR PERSONAGEM\n");
        printf("2- CARREGAR PERSONAGEM\n");
        printf("3- SAIR\n");
        scanf("%d", &resp);
        getchar();
        switch (resp) {
            case 1:
                personagemSelecionado = criarPersonagem();
                entradaValida = 1;
                break;
            case 2:
                if (retornoCarregamentoPersonagens == 0) {
                    printf("VOCE NAO POSSUI NENHUM PERSONAGEM\n");
                    getchar();
                    entradaValida = 0;
                } else {
                    personagemSelecionado = carregarPersonagem(retornoCarregamentoPersonagens);
                    entradaValida = 1;
                }
                break;
            case 3:
                entradaValida = 1;
                break;
            default:
                printf("Entrada Invalida!\n");
                entradaValida = 0;
                break;
        }
        system("cls");
        //segunda tela
        if (entradaValida == 1 && resp != 3) {
            printf("BEM-VINDO %s\n", personagemSelecionado.nome);
            do {
                printf("---------------------------------\n\n");
                printf("SELECIONE A OPCAO DESEJADA\n\n");
                printf("1- STATUS DO PERSONAGEM\n");
                printf("2- ENFRENTAR INIMIGO\n");
                printf("3- REALIZAR MISSAO\n");
                printf("4- SAIR\n");
                scanf("%d", &resp2);
                getchar();
                switch (resp2) {
                    case 1:
                        system("cls");
                        //status do personagem
                        printf("NOME: %s\n", personagemSelecionado.nome);
                        printf("RACA: %s\n", personagemSelecionado.raca);
                        printf("CLASSE %s\n", personagemSelecionado.classe);
                        printf("FORCA %d\n", personagemSelecionado.forca);
                        printf("DEFESA %d\n", personagemSelecionado.defesa);
                        printf("VIDA %d\n", personagemSelecionado.vida);
                        printf("NIVEL %d\n", personagemSelecionado.nivel);
                        printf("Precione qualquer tecla para continuar");
                        getchar();
                        break;
                    case 2:
                        system("cls");
                        monstroSelecionado = selecionarInimigo();
                        personagemSelecionado = batalha(personagemSelecionado, monstroSelecionado, 0);
                        break;
                    case 3:
                        missaoSelecionada = selecionarMissao();
                        personagemSelecionado = realizarMissao(missaoSelecionada,personagemSelecionado);
                        getchar();
                        break;
                    case 4:
                        entradaValida = 0;
                        break;
                    default:
                        printf("Entrada Invalida!\n");
                        break;
                }
                system("cls");
            } while (resp2 != 4);
        }
    } while (resp != 3 && entradaValida == 0);

}


