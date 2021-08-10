// DEIS-ISEC 2020-2021
//TP - Programacao - Licenciatura em Engenharia Informatica Pos Laboral
//Daniel Fernandes - a2020116565
//Turma Pratica P2
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"
#include <ctype.h>

//Atualização da estrutura a cada jogada
pjogada atualizaEstrutura(pjogada p,char letra,int pos,int jogador,int nJogadas, pPlayer j){
    pjogada novo, aux;

    novo= malloc(sizeof (jogada));

    if(novo==NULL){
        printf("Não foi possivel alocar memoria para a estrutura");
        return NULL;
    }

    novo->total=nJogadas;
    novo->iJogador=jogador;
    novo->jogada=letra;
    novo->posicao=pos;
    novo->prox=NULL;
    if(jogador==1)
        novo->jogador=j;
    else
        novo->jogador=j->prox;

    if(p==NULL)
        p=novo;

    else{
        aux=p;
        while(aux->prox!=NULL)
            aux=aux->prox;

        aux->prox=novo;
    }

    return p;

}
//Inicialização da lista ligada dos jogadores
pPlayer inicializaPlayer(pPlayer player){
    pPlayer novoP;
    novoP = malloc(sizeof (pl));

    if(novoP==NULL){
        printf("Não foi possivel alocar memoria para a estrutura");
        return NULL;
    }

    novoP->maxLinhaP=0;
    novoP->maxColP=0;
    novoP->maxPedraP=0;
    novoP->prox=NULL;
    novoP->verde=0;
    novoP->amarelo=0;
    novoP->red=0;

    if(player==NULL) {
        player = novoP;
        player->jog=1;
    }
    else{
        novoP->jog=2;
        player->prox = novoP;

    }
    return player;
}
//Atualização da lista ligada dos jogadores
void atualizaEstruraJogador(pPlayer p, int jogador, char letra, char verde, char amarelo, char red){

    while (p->jog!=jogador && p!=NULL)
    {
        p=p->prox;
    }
    if(p->jog==jogador){
        if(tolower(letra)== tolower(verde))
            p->verde++;

        else if (tolower(letra)== tolower(amarelo))
            p->amarelo++;

        else if (tolower(letra)== tolower(red))
            p->red++;
    }

}
//Libertação das listas ligadas
void libertaEstrutura(pjogada p){
    pjogada aux;

    while(p!=NULL){
        aux=p;
        p=p->prox;
        free(aux);
    }
}
//Libertação das listas ligadas
void libertaEstrutura1(pPlayer p){
    pPlayer aux;

    aux=p->prox;
    free(aux);
    free(p);

}

//Recuperação do indice do jogador
int recuperaJogador(pjogada p){
    int jogador;

    while (p->prox!=NULL)
        p=p->prox;
    jogador=p->iJogador;

    jogador=jogador %2 + 1;
    return jogador;
}