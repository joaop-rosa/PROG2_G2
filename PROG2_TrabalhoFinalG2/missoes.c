//
// Created by jprag on 26/06/2022.
//
#include <stdio.h>
#include <string.h>
#include "bibliotecas/estruturasDados.h"
#include "bibliotecas/monstros.h"
#include "bibliotecas/batalha.h"
#include "bibliotecas/personagens.h"
#include <stdlib.h>
int tamanhoVetor(int p[]){
    int nlen = 0;
    while(p[nlen] != 0 ) {
        nlen++;
    }
    return nlen;
}
MISSAO selecionarMissao() {
    FILE *arquivo;
    char textoLido[200];
    char atributoMissao[50];
    char valorAtributo[50];
    char sequenciaInimigos[50];
    int contaVirgula, contaBarra, contaMissao = 0, ultimaPosicao, ulmimaPosicaoSequenciaInimigos, contador = 0, resp, repeat, tamanhoSeq;
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
                                    ulmimaPosicaoSequenciaInimigos = 0;
                                    int w = 0;
                                    for (int j = 0; j < strlen(valorAtributo); ++j) {
                                        if (valorAtributo[j] == '/' || j == strlen(valorAtributo)-1) {
                                            for (int k = ulmimaPosicaoSequenciaInimigos, k2=ulmimaPosicaoSequenciaInimigos+1, y = 0; k < j; ++k,k2++, y++) {
                                                if(ulmimaPosicaoSequenciaInimigos == 0){
                                                    sequenciaInimigos[y] = valorAtributo[ulmimaPosicaoSequenciaInimigos];
                                                }else{
                                                    sequenciaInimigos[y] = valorAtributo[k2];
                                                }
                                            }
                                            ulmimaPosicaoSequenciaInimigos = j;
                                            listaMissao[contaMissao].seqInimigos[w] = atoi(sequenciaInimigos);
                                            listaMissao[contaMissao].seqInimigos[w+1] = 0;
                                            memset(sequenciaInimigos, 0, 50);
                                            w++;
                                        }
                                    }
                                    break;
                                default:
                                    break;
                            }
                        }
                        memset(sequenciaInimigos, 0, 50);
                    }
                    //printf("%s\n",valorAtributo);
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
        //ORDENA ARRAY DE MONSTROS BASEADO NO NIVEL DE RECOMPENCA
        struct missao temp;
        for (int i = 0; i < contaMissao; ++i) {
            for (int j = 0; j < contaMissao; ++j) {
                if(listaMissao[i].recompencaNivel < listaMissao[j].recompencaNivel){
                    temp = listaMissao[i];
                    listaMissao[i] = listaMissao[j];
                    listaMissao[j] = temp;
                }
            }
        }
        // TELA USUARIO
        struct monstro monstroId;
        printf("SELECIONE A MISSAO QUE DESEJA ENFRENTAR\n");
        printf("--------------------------------------------------------\n");
        for (int i = 0; i < contaMissao; ++i) {
            printf("%d - ", i);
            printf("%s | ", listaMissao[i].nome);
            tamanhoSeq = tamanhoVetor(listaMissao[i].seqInimigos);
            printf("\nSequencia Missao: \n\n");
            for (int j = 0; j < tamanhoSeq; ++j) {
                monstroId = consultarNomeMonstroPorID(listaMissao[i].seqInimigos[j]);
                printf(" -%s \n",monstroId.nome);
            }
            printf("\nRECOMPENCA: %d NIVEL \n", listaMissao[i].recompencaNivel);
            printf("--------------------------------------------------------\n");
        }
        repeat = 0;
        do {
            repeat++;
            if (repeat > 1) {
                printf("Entrada invalida!\n");
            }
            scanf("%d", &resp);
            getchar();
        } while (resp >= contaMissao || resp < 0);
        return listaMissao[resp];
    }

}

PERSONAGEM realizarMissao(MISSAO missao, PERSONAGEM personagem){
    struct monstro monstroSequencia;
    int vidaPersonagem = personagem.vida;
    system("cls");
    printf("MISSAO: %s INICIADA\n",missao.nome);
    for (int i = 0; i < tamanhoVetor(missao.seqInimigos); ++i) {
        monstroSequencia = consultarNomeMonstroPorID(missao.seqInimigos[i]);
        printf("%d Inimigo: %s\n",i+1, monstroSequencia.nome);
        printf("Precione qualquer tecla para iniciar o combate...\n");
        getchar();
        personagem = batalha(personagem,monstroSequencia, 1);
        if(personagem.vida <= 0){
            printf("VOCE NAO CONSEGUIU COMPLETAR A MISSAO!\n");
            personagem.vida = vidaPersonagem;
            return personagem;
        }
        system("cls");
    }
    printf("PARABENS! VOCE CONCLUIU A MISSAO\n");
    printf("COMO RECOMPENCA GANHOU %d NIVEIS\n",missao.recompencaNivel);
    personagem.vida = vidaPersonagem;
    personagem = subirNivelPersonagem(personagem,missao.recompencaNivel);
    return personagem;
}

