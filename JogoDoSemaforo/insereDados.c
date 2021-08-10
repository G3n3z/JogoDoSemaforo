// DEIS-ISEC 2020-2021
//TP - Programacao - Licenciatura em Engenharia Informatica Pos Laboral
//Daniel Fernandes - a2020116565
//Turma Pratica P2

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "jogo.h"
#include <stdlib.h>

//Incializacao de um tabuleiro alocado dinamicamente
char *inicializaTabuleiro(int dim){

    char *tabuleiro=NULL;
    int i, j;



    tabuleiro=realloc(tabuleiro,sizeof(char)*(dim*dim)); //Alocacao de memoria

    if(tabuleiro==NULL){
        printf("Nao foi possivel");
        return NULL;
    }
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){    //Inicializacao do tabuleiro com caracteres em branco
            *(tabuleiro+dim*i+j)=' ';

        }
    }



    return tabuleiro;
}

//Insercao da jogada no tabuleiro
void atualizaTabuleiro(char* tab,int *njogadas,int pos,char letra){

    *(tab+pos)= letra;  //Atualizacao do tabuleiro
    (*njogadas)++;
}

//Realocacao e manutencao do Tabuleiro
char *aumentaTabuleiro(int* ncol, int* nlin, char letra, char addCol, char addLin, char *tab){
    int i,j,col,lin;
    char *tabuleiro =tab;
    if(letra==addCol)
        (*ncol)++;
    else
        (*nlin)++;
    col=*ncol;
    lin=*nlin;
    tabuleiro=realloc(tab,sizeof(char)*(lin*col)); //Realocacao

    if(tabuleiro==NULL){
        printf("Nao foi possivel");
        return NULL;
    }

    tab=tabuleiro;
    if(letra==addCol) { //Se tiver sido inserido uma coluna tem que atualizar os indices
        for (i = lin - 1; i >= 0; i--) {

            for (j = col-2; j >= 0; j--) {
                    *(tab + col * i + j) = *(tab + col * i + j-i);
            }
        }
        for(i=col-1;i<col*lin;i+=col)
            *(tab + i)=' ';
    }
    else{   //Se tiver sido inserida uma linha, inicializacao da linha com caracteres em branco
        for(i=(col*lin)-col;i<col*lin;i++)
            *(tab + i)=' ';
    }


    return tab;
}

//Recomposicao de um tabuleiro a partir da estrutura de dados
char* recompoeTAB(pjogada p, int njogadas, int *nlin,int *ncol, char addCol,char addLinha,pPlayer player) {
    int dim;
    char *tabRep = NULL;
    int i = 0;
    dim=(*nlin);
    tabRep = inicializaTabuleiro(dim); //Inicializacao de um tabuleiro

    while (i < njogadas) {  //Percorre a lista ligada ate ao fim

        if (tolower(p->jogada) == addLinha || tolower(p->jogada) == addCol) {

            tabRep = aumentaTabuleiro(ncol, nlin, p->jogada, addCol, addLinha, tabRep);
            i++;

        }

        else {

            atualizaTabuleiro(tabRep, &i, p->posicao, p->jogada);
        }
        p = p->prox;



    }
    //Retorna o tabuleiro no estado em que tinha sido guardado
    return tabRep;

}

//Pede o nome do ficheiro ao utilizador
void pede_nome_ficheiro(char *fname){
    char nome[5]="jogo";
    char extensao[5]=".txt";
    printf("Qual o nome do ficheiro com os estados do tabuleiro?  (Extensao predefinida - .txt)\n");
    printf("Para sair insira s\n");
    ler_str(fname,sizeof(fname));


    if(tolower(fname[0])=='s'|| fname[0]==' ') // Se for inserido um espaço em branco ou enter, o ficheiro fica com
        strcpy(fname, nome);           //o nome jogo.txt

    strcat(fname,extensao);
    fname[strlen(fname)]='\0';
}

