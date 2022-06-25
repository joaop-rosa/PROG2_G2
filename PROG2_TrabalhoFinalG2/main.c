#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

PERSONAGEM criarPersonagem();

PERSONAGEM carregarPersonagem(int numeroPersonagens);

int lerPersonagens();

void salvarNovoPersonagem(PERSONAGEM personagem);

MONSTRO selecionarInimigo();

void selecionarMissão();

PERSONAGEM batalha(PERSONAGEM personagemSelecionado, MONSTRO monstroSelecionado);

PERSONAGEM subirNivelPersonagem(PERSONAGEM personagemAlterado, int nivel);

int main() {
    int resp, resp2;
    int entradaValida = 0;
    struct personagem personagemSelecionado;
    struct monstro monstroSelecionado;

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
                        personagemSelecionado = batalha(personagemSelecionado, monstroSelecionado);
                        break;
                    case 3:
                        selecionarMissão();
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






    //enfrentar inimigo

    //realizar missao
    //-1 explorar castelo abandonado
    //-2 explorar caverna
    //-3 limpar a taverna

    //sair


    return 0;
}


PERSONAGEM batalha(PERSONAGEM personagem, MONSTRO monstro) {
    int vidaPersonagem = personagem.vida;
    int rodada = 1, calculoBatalha;
    if ((personagem.defesa > monstro.forca) && (monstro.defesa > personagem.forca)) {
        printf("Empate\n");
        return personagem;
    } else {
        while (personagem.vida > 0 && monstro.vida > 0) {
            system("cls");
            printf("=================================\n");
            printf("%s - VIDA: %d\n", personagem.nome, personagem.vida);
            printf("=================================\n");
            printf("%s - VIDA: %d\n", monstro.nome, monstro.vida);
            printf("=================================\n");
            printf("rodada: %d\n", rodada);
            if (rodada % 2 == 0) {
                calculoBatalha = monstro.forca - personagem.defesa;
                if (calculoBatalha < 0) {
                    calculoBatalha = 0;
                }
                personagem.vida -= calculoBatalha;
                printf("%s CAUSOU %d de dano ao %s\n", monstro.nome, calculoBatalha, personagem.nome);
            } else {
                calculoBatalha = personagem.forca - monstro.defesa;
                if (calculoBatalha < 0) {
                    calculoBatalha = 0;
                }
                monstro.vida -= calculoBatalha;
                printf("%s CAUSOU %d de dano ao %s\n", personagem.nome, calculoBatalha, monstro.nome);
            }
            rodada++;
            printf("Precione qualquer tecla para continuar");
            getchar();
        }
        if (personagem.vida > 0) {
            printf("%s VENCEU :)\n", personagem.nome);
            personagem.vida = vidaPersonagem;
            printf("Precione qualquer tecla para continuar");
            getchar();
            return subirNivelPersonagem(personagem, monstro.recompencaNivel);
        } else {
            printf("%s PERDEU :(\n", personagem.nome);
            personagem.vida = vidaPersonagem;
            printf("Precione qualquer tecla para continuar");
            getchar();
            return personagem;
        }
    }
}

PERSONAGEM subirNivelPersonagem(PERSONAGEM personagemAlterado, int nivel) {
    struct personagem personagemCarregado;
    FILE *arquivo;
    int contador = 0;
    arquivo = fopen("personagens.bin", "rb+");
    personagemAlterado.nivel += nivel;
    personagemAlterado.forca += nivel;
    personagemAlterado.defesa += nivel;
    personagemAlterado.vida += nivel * 2;
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

void selecionarMissão() {

}

PERSONAGEM criarPersonagem() {
    int resp;
    int entradaValida = 0;
    printf("FUNCAO CRIAR PERSONAGEM\n");
    struct personagem novoPersonagem;

    //NOME
    printf("Informe o nome do seu personagem:\n");
    fgets(novoPersonagem.nome, 50, stdin);
    getchar();
    novoPersonagem.nome[strlen(novoPersonagem.nome) - 1] = '\0';

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
                novoPersonagem.forca = 7;
                novoPersonagem.defesa = 7;
                novoPersonagem.vida = 7;
                entradaValida = 1;
                break;
            case 2:
                strcpy(novoPersonagem.raca, "orc");
                novoPersonagem.forca = 10;
                novoPersonagem.defesa = 5;
                novoPersonagem.vida = 10;
                entradaValida = 1;
                break;
            case 3:
                strcpy(novoPersonagem.raca, "anao");
                novoPersonagem.forca = 7;
                novoPersonagem.defesa = 10;
                novoPersonagem.vida = 10;
                entradaValida = 1;
                break;
            case 4:
                strcpy(novoPersonagem.raca, "elfo");
                novoPersonagem.forca = 5;
                novoPersonagem.defesa = 7;
                novoPersonagem.vida = 12;
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
                novoPersonagem.forca += 2;
                entradaValida = 1;
                break;
            case 2:
                strcpy(novoPersonagem.classe, "mago");
                novoPersonagem.defesa += 2;
                entradaValida = 1;
                break;
            case 3:
                strcpy(novoPersonagem.classe, "ladino");
                novoPersonagem.forca += 3;
                novoPersonagem.vida -= 1;
                entradaValida = 1;
                break;
            case 4:
                strcpy(novoPersonagem.classe, "paladino");
                novoPersonagem.vida += 5;
                entradaValida = 1;
                break;
            case 5:
                strcpy(novoPersonagem.classe, "cacador");
                novoPersonagem.forca += 2;
                novoPersonagem.defesa += 1;
                novoPersonagem.vida -= 1;
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