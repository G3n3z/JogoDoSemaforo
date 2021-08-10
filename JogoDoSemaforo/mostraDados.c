// DEIS-ISEC 2020-2021
//TP - Programacao - Licenciatura em Engenharia Informatica Pos Laboral
//Daniel Fernandes - a2020116565
//Turma Pratica P2

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "jogo.h"
#include <stdlib.h>

void mostraInicio(){   //Fun��o que imprime as regras de funcionamento do Jogo

    printf("REGRAS DE FUNCIONAMENTO\n\n");

    printf("Objetivo:\n O jogador que coloque uma peca que permita formar uma linha, coluna ou diagonal completa com pecas da mesma cor ganha o jogo.\n");

    printf("\nJogadas Permitidas:\n");

    printf("Tecla V - Colocar uma peca Verde numa celula vazia\n");

    printf("Tecla A - Trocar uma peca Verde que esteja colocada no tabuleiro por uma peca Amarela\n");
    printf("Tecla R - Trocar uma peca Amarela que esteja colocada no tabuleiro por uma peca Vermelha\n");
    printf("Tecla P - Colocar uma pedra numa celula vazia (Cada jogador so pode adicionar 1 Pedra por jogo)\n");
    printf("Tecla C - Adicionar 1 coluna ao tabuleiro (Cada jogador so pode adicionar 1 Coluna por jogo)\n");
    printf("Tecla N - Adicionar 1 linha ao tabuleiro (Cada jogador so pode adicionar 1 Linha por jogo)\n");
    printf("Tecla J - Ver os estados antigos do tabuleiro");



}


//Função de mostrar o tabuleiro
void mostraJogo(int n_lin, int n_col,char *tab){

    int i, j,k;
    printf("\n");
    for(i=0;i<n_lin;i++){
        for(j=0;j<n_col;j++){
            printf(" %c ", *(tab+n_col*i+j));
            if(j<n_col-1)
                printf("|");


        }
        printf("   ( %d - %d) ", n_col*i+j+1-n_col,n_col*i+j);

        if(i<n_lin-1) {
            printf("\n");
            for (k = 0;k < n_col;k++){
                printf("----");
            }
            printf("\n");
        }
    }
    printf("\n\n");
}
//Funcao de mostrar as jogagas anteriores
void mostraJogadas(pjogada p,int pos, int njogadas, int dim, char addCol,char addLinha) {
    int rep, ncol, nlin;
    char *tabRep = NULL;
    rep = njogadas - pos;
    int i = 0;
    ncol=nlin=dim;
    tabRep = inicializaTabuleiro(dim);

    while (i < njogadas) {

        if(i>rep) {
            mostraJogo(nlin,ncol,tabRep);
        }
        if (tolower(p->jogada) == addLinha || tolower(p->jogada) == addCol) {

            tabRep = aumentaTabuleiro(&ncol, &nlin, p->jogada, addCol, addLinha, tabRep);
            i++;
        } else {
            atualizaTabuleiro(tabRep, &i, p->posicao, p->jogada);
        }
        p = p->prox;



    }

    free(tabRep);
}

//Função que imprime no ecra as jogadas permitidas no momento
void mostraJogadasDisponiveis(pPlayer p, pPlayer p2, int nlin,int ncol){

    if (p->verde+p2->verde<ncol*nlin) {
        printf("\nV - Jogar uma peca Verde\n");
    }
    if(p->amarelo+p2->amarelo < p->verde+p2->verde)
        printf("A - Trocar peca Verde por Amarela\n");
    if(p->red + p2->red < p->amarelo+p2->amarelo)
        printf("R - Trocar peca Amarela por Vermelha\n");

    if(p->maxPedraP<1)
        printf("P- Colocar uma pedra\n");
    if (p->maxLinhaP<1)
        printf("N - Adicionar uma Linha\n");
    if (p->maxColP<1)
        printf("C- Adicionar uma coluna\n");

    if (p->verde+p2->verde>0)
        printf("J - Ver os k estados anteriores do Tabuleiro\n");

    printf("S - Sair do jogo atual\n");


}



