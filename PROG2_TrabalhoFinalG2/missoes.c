//
// Created by jprag on 26/06/2022.
//
#include <stdio.h>
#include <string.h>
#include "bibliotecas/estruturasDados.h"
#include <stdlib.h>
int tamanhoVetor(int p[]){
    int nlen = 0;

    while(*(p++) || *p == 0 ) {
        nlen++;
    }
    return(nlen);
}
MISSAO selecionarMissao() {
    FILE *arquivo;
    char textoLido[200];
    char atributoMissao[50];
    char valorAtributo[50];
    char sequenciaInimigos[50];
    int contaVirgula, contaBarra, contaMissao = 0, ultimaPosicao, ulmimaPosicaoSequenciaInimigos, contador = 0, resp, repeat;
    arquivo = fopen("missoes.txt", "r");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir arquivo.");
    } else {
        //PASSA SOBRE O ARQUIVO CONTANDO QUANTAS LINHAS POSSUI
        while (fgets(textoLido, 200, arquivo) != NULL) {
            contador++;
        }
        //CRIA UMA STRUCT PARA ARMAZENAS OS MONSTROS CONFORME QUANTIDADE DE LINHAS
        struct missao listaMissao[contador];
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
                        atributoMissao[x] = textoLido[j];
                    }
                    //printf("%s\n",atributoMissao);
                    for (int index = 0; index < strlen(atributoMissao); ++index) {
                        if (atributoMissao[index] == ':') {
                            //ATRIBUI A UMA SUBSTRING O VALOR DO ATRIBUTO
                            for (int j = index + 1, x = 0; j < strlen(atributoMissao); ++j, x++) {
                                valorAtributo[x] = atributoMissao[j];
                            }
                            //ATRIBUI VALORES PARA STRUCT
                            switch (contaVirgula) {
                                case 1:
                                    listaMissao[contaMissao].id = atoi(valorAtributo);
                                    break;
                                case 2:
                                    strcpy(listaMissao[contaMissao].nome, valorAtributo);
                                    break;
                                case 3:
                                    contaBarra = 0;
                                    ulmimaPosicaoSequenciaInimigos = 0;
                                    int w = 0;
                                    for (int j = 0; j < strlen(valorAtributo); ++j) {
                                        if (valorAtributo[j] == '/') {
                                            contaBarra++;
                                            for (int k = ulmimaPosicaoSequenciaInimigos, k2=ulmimaPosicaoSequenciaInimigos+1, y = 0; k < j; ++k,k2++, y++) {
                                                if(ulmimaPosicaoSequenciaInimigos == 0){
                                                    sequenciaInimigos[y] = valorAtributo[ulmimaPosicaoSequenciaInimigos];
                                                }else{
                                                    sequenciaInimigos[y] = valorAtributo[k2];
                                                }
                                            }
                                            ulmimaPosicaoSequenciaInimigos = j;
                                            printf("%s\n",sequenciaInimigos);
                                            listaMissao[contaMissao].seqInimigos[w] = atoi(sequenciaInimigos);
                                            memset(sequenciaInimigos, 0, 50);
                                            w++;
                                            if(contaBarra == 3){
                                                for (int k = ulmimaPosicaoSequenciaInimigos, k2=ulmimaPosicaoSequenciaInimigos+1, y = 0; k < j; ++k,k2++, y++) {
                                                    if(ulmimaPosicaoSequenciaInimigos == 0){
                                                        sequenciaInimigos[y] = valorAtributo[ulmimaPosicaoSequenciaInimigos];
                                                    }else{
                                                        sequenciaInimigos[y] = valorAtributo[k2];
                                                    }
                                                }
                                                listaMissao[contaMissao].seqInimigos[w] = atoi(sequenciaInimigos);
                                                printf("%s\n",sequenciaInimigos);
                                                memset(sequenciaInimigos, 0, 50);
                                            }
                                        }
                                    }
                                    break;
                                default:
                                    break;
                            }
                        }
                        memset(sequenciaInimigos, 0, 50);
                    }
                    printf("%s\n",valorAtributo);
                    //ATUALIZA ITERADOR LINHA
                    ultimaPosicao = i + 1;
                    //ZERA ATRIBUTOS
                    memset(valorAtributo, 0, 50);
                    memset(atributoMissao, 0, 50);
                    //ATRIBUTO recompencaNivel
                    if (contaVirgula == 3) {
                        for (int j = ultimaPosicao, x = 0; j < strlen(textoLido); ++j, x++) {
                            atributoMissao[x] = textoLido[j];
                        }
                        //printf("%s\n",atributoMonstro);
                        for (int index = 0; index < strlen(atributoMissao); ++index) {
                            if (atributoMissao[index] == ':') {
                                for (int j = index + 1, x = 0; j < strlen(atributoMissao); ++j, x++) {
                                    valorAtributo[x] = atributoMissao[j];
                                }
                            }
                        }
                        listaMissao[contaMissao].recompencaNivel = atoi(valorAtributo);
                        //printf("%s\n",valorAtributo);
                        memset(valorAtributo, 0, 50);
                        memset(atributoMissao, 0, 50);
                        memset(sequenciaInimigos, 0, 50);
                    }

                }

            }
            contaMissao++;
        }
        fclose(arquivo);
        for (int i = 0; i < contaMissao; ++i) {
            printf("%d - ", i);
            printf("%s | ", listaMissao[i].nome);
            int tamanhoSeq = tamanhoVetor(listaMissao[i].seqInimigos);
            printf("Sequencia Inimigos: ");
            printf("%d",tamanhoSeq);
            for (int j = 0; j < tamanhoSeq; ++j) {
                printf("%d ",listaMissao[i].seqInimigos[j]);
            }
            printf("RECOMPENCA: %d NIVEL \n", listaMissao[i].recompencaNivel);
        }
        getchar();
        return listaMissao[0];
    }

}

