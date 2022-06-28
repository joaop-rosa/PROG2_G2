//
// Created by jprag on 25/06/2022.
//
#include "stdio.h"
#include "bibliotecas/personagens.h"
#include "bibliotecas/estruturasDados.h"
#include "string.h"
#include "stdlib.h"


int validaNome(char nome[50]){

    FILE *arquivo;
    struct personagem personagemCarregado;
    int endFileControl;
    arquivo = fopen("personagens.bin", "rb");
    if (arquivo == NULL) {
        printf("Nao foi possivel carregar os personagens\n");
    } else {
        while (!feof(arquivo)) {
            endFileControl = fread(&personagemCarregado, sizeof(PERSONAGEM), 1, arquivo);
            if (endFileControl != 0) {
                if(strcmp(nome,personagemCarregado.nome) == 0){
                    fclose(arquivo);
                    return 1;
                }
            }
        }
    }
    fclose(arquivo);
    return 0;
}

PERSONAGEM criarPersonagem() {
    int resp;
    int entradaValida = 0;
    printf("FUNCAO CRIAR PERSONAGEM\n");
    struct personagem novoPersonagem;
    novoPersonagem.vida = 0;
    novoPersonagem.forca = 0;
    novoPersonagem.defesa = 0;
    int retornoValidacao = 1;
    int repeat;
    //NOME
    repeat = 0;
    do {
        repeat++;
        if(repeat > 1){
            printf("Nome de personagem ja existe\n");
        }
        printf("Informe o nome do seu personagem:\n");
        fgets(novoPersonagem.nome, 50, stdin);
        novoPersonagem.nome[strlen(novoPersonagem.nome) - 1] = '\0';
        retornoValidacao = validaNome(novoPersonagem.nome);
    } while (retornoValidacao == 1);


    //NIVEL
    novoPersonagem.nivel = 1;

    //RACA
    do {
        printf("SELECIONE A RACA DO SEU PERSONAGEM\n");
        printf("---------------------------------\n\n");
        printf("1- HUMANO\n");
        printf("2- ORC\n");
        printf("3- ANAO\n");
        printf("4- ELFO\n");
        scanf("%d", &resp);
        getchar();
        switch (resp) {
            case 1:
                strcpy(novoPersonagem.raca, "humano");
                novoPersonagem.forca += 1;
                novoPersonagem.defesa += 1;
                entradaValida = 1;
                break;
            case 2:
                strcpy(novoPersonagem.raca, "orc");
                novoPersonagem.forca += 1;
                novoPersonagem.defesa += 1;
                entradaValida = 1;
                break;
            case 3:
                strcpy(novoPersonagem.raca, "anao");
                novoPersonagem.defesa += 1;
                novoPersonagem.vida += 2;
                entradaValida = 1;
                break;
            case 4:
                strcpy(novoPersonagem.raca, "elfo");
                novoPersonagem.vida += 4;
                entradaValida = 1;
                break;
            default:
                printf("Entrada Invalida!\n");
                break;
        }

    } while (entradaValida == 0);

    //CLASSE

    do {
        printf("SELECIONE A CLASSE DO SEU PERSONAGEM\n");
        printf("---------------------------------\n\n");
        printf("1- GUERREIRO\n");
        printf("2- MAGO\n");
        printf("3- LADINO\n");
        printf("4- PALADINO\n");
        printf("5- CACADOR\n");
        scanf("%d", &resp);
        getchar();
        switch (resp) {
            case 1:
                strcpy(novoPersonagem.classe, "guerreiro");
                novoPersonagem.forca += 10;
                novoPersonagem.defesa += 18;
                novoPersonagem.vida += (rand() % 10) + 1;
                entradaValida = 1;
                break;
            case 2:
                strcpy(novoPersonagem.classe, "mago");
                novoPersonagem.forca += 25;
                novoPersonagem.defesa += 12;
                novoPersonagem.vida += (rand() % 6) + 1;
                entradaValida = 1;
                break;
            case 3:
                strcpy(novoPersonagem.classe, "ladino");
                novoPersonagem.forca += 20;
                novoPersonagem.defesa += 14;
                novoPersonagem.vida += (rand() % 8) + 1;
                entradaValida = 1;
                break;
            case 4:
                strcpy(novoPersonagem.classe, "paladino");
                novoPersonagem.forca += 13;
                novoPersonagem.defesa += 16;
                novoPersonagem.vida += (rand() % 10) + 1;
                entradaValida = 1;
                break;
            case 5:
                strcpy(novoPersonagem.classe, "cacador");
                novoPersonagem.forca += 15;
                novoPersonagem.defesa += 15;
                novoPersonagem.vida += (rand() % 10) + 1;
                entradaValida = 1;
                break;
            default:
                printf("Entrada Invalida!\n");
                entradaValida = 0;
                break;
        }
    } while (entradaValida == 0);
    salvarNovoPersonagem(novoPersonagem);
    return novoPersonagem;
}

PERSONAGEM carregarPersonagem(int numeroPersonagens) {
    //printf("FUNCAO CARREGAR PERSONAGEM\n");
    struct personagem listapersonagem[numeroPersonagens];
    int resp = 0, repeat, cont = 0, endFileControl;
    FILE *arquivo;
    struct personagem personagemCarregado, personagemSelecionado;
    arquivo = fopen("personagens.bin", "rb");
    if (arquivo == NULL) {
        printf("Nao foi possivel carregar os personagens\n");
    } else {
        while (!feof(arquivo)) {
            endFileControl = fread(&personagemCarregado, sizeof(PERSONAGEM), 1, arquivo);
            if (endFileControl != 0) {
                listapersonagem[cont] = personagemCarregado;
                cont++;
            }
        }
    }
    fclose(arquivo);
    printf("SELECIONE O PERSONAGEM\n");
    printf("----------------------\n");
    for (int i = 0; i < numeroPersonagens; i++) {
        printf("%d - ", i);
        printf(" %s |", listapersonagem[i].nome);
        printf(" %s |", listapersonagem[i].raca);
        printf(" %s |", listapersonagem[i].classe);
        printf(" %d \n", listapersonagem[i].nivel);
    }
    repeat = 0;
    do {
        repeat++;
        if (repeat > 1) {
            printf("Entrada invalida!\n");
        }
        scanf("%d", &resp);
        getchar();
    } while (resp >= numeroPersonagens || resp < 0);
    //printf("%s\n", listapersonagem[resp].nome);
    return listapersonagem[resp];
}

int lerPersonagens() {
    int contador = 0;
    FILE *arquivo;
    struct personagem personagemCarregado;
    int endFileControl;
    arquivo = fopen("personagens.bin", "rb");
    if (arquivo == NULL) {
        printf("Nao foi possivel carregar os personagens\n");
    } else {
        while (!feof(arquivo)) {
            endFileControl = fread(&personagemCarregado, sizeof(PERSONAGEM), 1, arquivo);
            if (endFileControl != 0) {
                contador++;
            }
        }
    }
    fclose(arquivo);
    return contador;
}

void salvarNovoPersonagem(PERSONAGEM personagem) {
    //SALVA NO ARQUIVO AS INFORMACOES
    FILE *arquivo;
    arquivo = fopen("personagens.bin", "ab+");
    if (arquivo == NULL) {
        //return 0;
    } else {
        fwrite(&personagem, sizeof(PERSONAGEM), 1, arquivo);
        fclose(arquivo);
        //return 1;
    }

}
PERSONAGEM subirNivelPersonagem(PERSONAGEM personagemAlterado, int nivel) {
    struct personagem personagemCarregado;
    FILE *arquivo;
    int contador = 0;
    arquivo = fopen("personagens.bin", "rb+");
    personagemAlterado.nivel += nivel;
    personagemAlterado.forca += nivel;
    personagemAlterado.vida += 6*nivel;
    if (arquivo == NULL) {
        printf("Nao foi possivel carregar os personagens\n");
    } else {
        while (fread(&personagemCarregado, sizeof(PERSONAGEM), 1, arquivo)) {
            if (strcmp(personagemAlterado.nome, personagemCarregado.nome) == 0) {
                if (contador == 0) {
                    fseek(arquivo, 0, SEEK_SET);
                } else {
                    fseek(arquivo, -sizeof(PERSONAGEM), SEEK_CUR);
                }
                fwrite(&personagemAlterado, sizeof(PERSONAGEM), 1, arquivo);
                fclose(arquivo);
            }
            contador++;
        }
    }

    return personagemAlterado;
}

int calcularModificador(int valorAtributo){
    int calculoModificador = valorAtributo - 10;
    int valorModificador = 0;
    if(calculoModificador < 0){
        while(calculoModificador < 0){
            calculoModificador += 2;
            valorModificador--;
        }
    } else{
        while(calculoModificador > 0){
            calculoModificador -= 2;
            valorModificador++;
        }
    }
    return valorModificador;
}

