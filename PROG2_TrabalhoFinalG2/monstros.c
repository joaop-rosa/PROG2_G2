//
// Created by jprag on 25/06/2022.
//
#include <stdio.h>
#include <string.h>
#include "bibliotecas/estruturasDados.h"
#include "stdlib.h"

MONSTRO selecionarInimigo() {
    FILE *arquivo;
    char textoLido[200];
    char atributoMonstro[50];
    char valorAtributo[50];
    int contaVirgula, contaMonstro = 0, ultimaPosicao, contador = 0, resp, repeat;
    arquivo = fopen("monstros.txt", "r");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir arquivo.");
    } else {
        //PASSA SOBRE O ARQUIVO CONTANDO QUANTAS LINHAS POSSUI
        while (fgets(textoLido, 200, arquivo) != NULL) {
            contador++;
        }
        //CRIA UMA STRUCT PARA ARMAZENAS OS MONSTROS CONFORME QUANTIDADE DE LINHAS
        struct monstro listaMonstro[contador];
        //RETORNA PONTEIRO PARA O INICIO DO ARQUIVO
        rewind(arquivo);
        //ZERA BUFFER
        memset(textoLido, 0, 200);
        //PERCORRE NOVAMENTE O ARQUIVO
        while (fgets(textoLido, 200, arquivo) != NULL) {
            //ZERA ITERADORES DA LINHA LIDA ANTERIORMENTE
            ultimaPosicao = 0;
            contaVirgula = 0;
            //PERCORRE LINHA LIDA
            for (int i = 0; i < strlen(textoLido); ++i) {
                //IF PARA CASO ENCONTRE SEPARADOR DE ATRIBUTOS
                if (textoLido[i] == ',') {
                    //CONTROLE DE ITERACAO PELOS ATRIBUTOS
                    contaVirgula++;
                    //ATRIBUI A UMA SUBSTRING O ATRIBUTO
                    for (int j = ultimaPosicao, x = 0; j < i; ++j, x++) {
                        atributoMonstro[x] = textoLido[j];
                    }
                    //printf("%s\n",atributoMonstro);
                    for (int index = 0; index < strlen(atributoMonstro); ++index) {
                        if (atributoMonstro[index] == ':') {
                            //ATRIBUI A UMA SUBSTRING O VALOR DO ATRIBUTO
                            for (int j = index + 1, x = 0; j < strlen(atributoMonstro); ++j, x++) {
                                valorAtributo[x] = atributoMonstro[j];
                            }
                            //ATRIBUI VALORES PARA STRUCT
                            switch (contaVirgula) {
                                case 1:
                                    listaMonstro[contaMonstro].id = atoi(valorAtributo);
                                    break;
                                case 2:
                                    strcpy(listaMonstro[contaMonstro].nome, valorAtributo);
                                    break;
                                case 3:
                                    listaMonstro[contaMonstro].forca = atoi(valorAtributo);
                                    break;
                                case 4:
                                    listaMonstro[contaMonstro].defesa = atoi(valorAtributo);
                                    break;
                                case 5:
                                    listaMonstro[contaMonstro].vida = atoi(valorAtributo);
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                    //printf("%s\n",valorAtributo);
                    //ATUALIZA ITERADOR LINHA
                    ultimaPosicao = i + 1;
                    //ZERA ATRIBUTOS
                    memset(valorAtributo, 0, 50);
                    memset(atributoMonstro, 0, 50);
                    //ATRIBUTO recompencaNivel
                    if (contaVirgula == 5) {
                        for (int j = ultimaPosicao, x = 0; j < strlen(textoLido); ++j, x++) {
                            atributoMonstro[x] = textoLido[j];
                        }
                        //printf("%s\n",atributoMonstro);
                        for (int index = 0; index < strlen(atributoMonstro); ++index) {
                            if (atributoMonstro[index] == ':') {
                                for (int j = index + 1, x = 0; j < strlen(atributoMonstro); ++j, x++) {
                                    valorAtributo[x] = atributoMonstro[j];
                                }
                            }
                        }
                        listaMonstro[contaMonstro].recompencaNivel = atoi(valorAtributo);
                        //printf("%s\n",valorAtributo);
                        memset(valorAtributo, 0, 50);
                        memset(atributoMonstro, 0, 50);
                    }
                }

            }
            contaMonstro++;
        }
        fclose(arquivo);
        //ORDENA ARRAY DE MONSTROS BASEADO NO NIVEL DE RECOMPENCA
        struct monstro temp;
        for (int i = 0; i < contaMonstro; ++i) {
            for (int j = 0; j < contaMonstro; ++j) {
                if(listaMonstro[i].recompencaNivel < listaMonstro[j].recompencaNivel){
                    temp = listaMonstro[i];
                    listaMonstro[i] = listaMonstro[j];
                    listaMonstro[j] = temp;
                }
            }
        }
        // TELA USUARIO
        printf("SELECIONE O INIMIGO QUE DESEJA ENFRENTAR\n");
        for (int i = 0; i < contaMonstro; ++i) {
            printf("%d - ", i);
            printf("%s | ", listaMonstro[i].nome);
            printf("RECOMPENCA: %d NIVEL \n", listaMonstro[i].recompencaNivel);
        }
        repeat = 0;
        do {
            repeat++;
            if (repeat > 1) {
                printf("Entrada invalida!\n");
            }
            scanf("%d", &resp);
            getchar();
        } while (resp >= contaMonstro || resp < 0);
        return listaMonstro[resp];
    }

}