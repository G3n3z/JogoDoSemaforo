// DEIS-ISEC 2020-2021
//TP - Programacao - Licenciatura em Engenharia Informatica Pos Laboral
//Daniel Fernandes - a2020116565
//Turma Pratica P2
#include <stdio.h>
#include "jogo.h"
#include <string.h>
#include <ctype.h>
#define TAMOP 15
#include <stdlib.h>
#include "utils.h"

int verificaInicio(int x){  //Verificacao se pretende come�ar um jogo novo ou retomar o anterior
    char opcao[TAMOP], novoJogo[]="1",retomarJogo[]="3", sair[]="2";
    int i=1;

    mostraInicio();
    printf("\n\nPretende:\n");
    printf("%d. Novo Jogo?\n",i++);

    if (x==1){                   //Se existir ficheiro imprime a opcao continuar jogo e altera os valores
         printf("%d. Continuar ultimo Jogo\n",i++);
         retomarJogo[0]='2';
         sair[0]='3';

    }

    printf("%d. Sair\n", i);
    printf("\nOpcao: ");
    fgets(opcao,TAMOP,stdin);
    opcao[strlen(opcao)-1]='\0';
    while((strcmp(opcao,sair))!=0){     //Leitura da opcao e ciclo de verificação

        if((strcmp(opcao,novoJogo))==0){

            return 1;

        }
        if((strcmp(opcao,retomarJogo))==0 &&(retomarJogo[0]=='2'))
            return 2;

        printf("\nOpcao: ");
        fgets(opcao,TAMOP,stdin);
        opcao[strlen(opcao)-1]='\0';
  }


    return 0;

}

//Funcao que determina a dimensão inicial
int dimensaoInicial(){

    int c;
    do{
        c= intUniformRnd(3,5);
    }while(c<3||c>5);

    return c;
}

//Funcao do Segundo menu e que pede os nomes aos jogadores
int jogadorversus(char *str1,char *str2){
    int dim;
    char opcao[TAMOP], contraJogador[]="1", contraCPU[]="2", sair[]="3";
    dim=TAMPLAYER;

    printf("Pretende Jogar:");          //Impressao do menu na consola
    printf("\n1. Contra Outro Jogador");
    printf("\n2. Contra CPU");
    printf("\n3. Sair\n");
    printf("\nOpcao: ");
    fgets(opcao,TAMOP-1,stdin);
    opcao[strlen(opcao)-1]='\0';

    while((strcmp(opcao, sair))!=0){    //Ciclo de validacao do menu
        if((strcmp(opcao,contraJogador))==0)        //Se for a opcao 1
        {
            printf("\nNome do Jogador 1: ");
            fgets(str1, dim-1, stdin);
            str1[strlen(str1)-1]='\0';
            printf("\n\n Nome do Jogador 2:");
            fgets(str2, dim-1, stdin);
            str2[strlen(str2)-1]='\0';
            return 1;

        }

        if((strcmp(opcao,contraCPU))==0){   //Se for a opcao 2
            printf("\nNome do Jogador 1: ");
            fgets(str1, dim-1, stdin);
            str1[strlen(str1)-1]='\0';
            strcpy(str2, "CPU");
            str2[strlen(str2)]='\0';   //Copia para o nome do jogador 2 'CPU'
            return 2;
        }
        printf("\nOpcao: ");
        fgets(opcao,TAMOP-1,stdin);
        opcao[strlen(opcao)-1]='\0';
    }

    return 0;

}
//Funcao que verifica se no tabuleiro na posicao 'pos' existe o caracter pretendido
int verificaExistente(char cor,int pos, char *tab){

    int i;
    if(tolower(*(tab+pos))==cor) {  //Se existir o pretendido devolve 1
        return 1;
    }
    else {
        return 0;
    }

}
//Funcao que pede a jogada ao jogador
char pedeJogada(int nlin, int ncol,int* pos,int jog, char *p1, char* p2, char *tab, int njogadas, pPlayer player){

    char verde='v', amarelo='a', pedra='p', jogAnte='j', addLinha='n', addCol='c', vermelho='r',sair='s';
    char opcao;
    char str[TAMOP];
    int x=0;

    if(jog==1){
        printf("\nE a vez do jogador A:  %s\n", p1);
        mostraJogadasDisponiveis(player, player->prox, nlin, ncol);
    }
    else {
        printf("\nE a vez do Jogador B:  %s\n", p2);
        mostraJogadasDisponiveis(player->prox, player, nlin, ncol);
    }
    do{
        printf("\nJogada: ");
        ler_str(str, sizeof (str));

        if(strlen(str)==1)      //Ciclo de validação da jogada inserida
            opcao=str[0];
        else
            opcao='x';      //Caso seja introduzido mais que uma letra


    }while(tolower(opcao)!=verde && tolower(opcao)!=amarelo && tolower(opcao)!=vermelho && tolower(opcao)!=pedra && tolower(opcao)!=jogAnte && tolower(opcao)!=addLinha && tolower(opcao)!=addCol && tolower(opcao)!=sair);


    if(tolower(opcao)==addLinha || tolower(opcao)==addCol||tolower(opcao)==jogAnte||tolower(opcao)==sair){
        return opcao;   //Se não for necessario pedir posicao
    }

    else {

        do{
            printf("Posicao: ");
            ler_str(str, sizeof (str));
            x= atoi(str);

        }while(x<1 || x>(ncol*nlin));
        *pos=x;
        (*pos)--;
    }

    return opcao;

}

//Verifica a quantidade de pedras jogadas
int verificaPedra(int *add1,int * add2, int jog){
    if(jog==1){
        (*add1)++;
        if(*add1>1){ //Verificacao da existencia das pedras jogadas. Tambem e usada para linhas e colunas

            return 0;
        }
        else
            return 1;
    }
    else {
        (*add2)++;
        if (*add2 > 1) {

            return 0;
        }
        else
            return 1;
    }
}

//Verificação do termino do jogo por completar uma coluna
int verificaColuna(int nlin,int ncol,char* tab,char verde,char amarelo,char pedra, char vermelho){
    int i, j, winV, winA, p, winR;

    for(i=0;i<ncol;i++){
        winV=0;   //Contadores de verificacao de ganho, sao limpos a cada coluna percorrida
        winR=0;
        winA=0;
        for(j=0;j<nlin;j++){
            if(tolower(*(tab+ncol*j+i))==verde)
                winV++;
            else if(tolower(*(tab+ncol*j+i))==amarelo)
                winA++;
            else if(tolower(*(tab+ncol*j+i))==pedra)
                continue;
            else if(tolower(*(tab+ncol*j+i))==vermelho)
                winR++;

        }
        if(winV==nlin || winA==nlin || winR==nlin){ //Se entrar significa que ganhou

            return 1;
        }

    }
    return 0;
}
//Verificação do termino do jogo por completar uma linha
int verificaLinha(int nlin,int ncol,char* tab,char verde,char amarelo,char pedra, char vermelho){
    int i, j, winV, winA, p, winR;

       for(i=0;i<nlin;i++){
        winV=0;//Contadores de verificacao de ganho, sao limpos a cada linha percorrida
        winR=0;
        winA=0;
            for(j=0;j<ncol;j++){
                if(tolower(*(tab+ncol*i+j))==verde)
                    winV++;
                else if(tolower(*(tab+ncol*i+j))==amarelo)
                    winA++;
                else if(tolower(*(tab+ncol*i+j))==pedra)
                    continue;
                else if(tolower(*(tab+ncol*i+j))==vermelho)
                    winR++;

            }
        if(winV==ncol || winA==ncol || winR==ncol){//Se entrar significa que ganhou

            return 1;
            }
        }
    return 0;

}
//Verificação do termino do jogo por completar uma diagonal
int verificaDiagonal(int nlin,int ncol,char* tab,char verde,char amarelo,char pedra, char vermelho){
    int i, winV, winA, winR;
       winV=0;
       winR=0;
       winA=0;

       for(i=0;i<nlin*ncol;i+=(ncol+1)){ //Verificacao da diagonal principal
            if(tolower(*(tab+i))==verde)
                winV++;
            else if(tolower(*(tab+i))==amarelo)
                winA++;
            else if(tolower(*(tab+i))==pedra)
                continue;
            else if(tolower(*(tab+i))==vermelho)
                winR++;

       }

       if(winV==ncol || winA==ncol || winR==ncol){ // Se entrar acabou o jogo

            return 1;
       }
    winV=0; //Limpeza dos contadores para verificar a outra diagonal
    winR=0;
    winA=0;


    for(i=ncol-1;i<nlin*ncol-(ncol-1);i+=(ncol-1)){//Verificacao da outra diagonal
        if(tolower(*(tab+i))==verde)
            winV++;
        else if(tolower(*(tab+i))==amarelo)
            winA++;
        else if(tolower(*(tab+i))==pedra)
            continue;
        else if(tolower(*(tab+i))==vermelho)
            winR++;

    }

    if(winV==ncol || winA==ncol || winR==ncol){

        return 1;
    }
    return 0;
}

//Cerebro do jogador automatico
int posicaoAutomatica(char *letra,int nlin, int ncol, int nJogadas){
    int i=0,k, pos;

    pos=intUniformRnd(0, (nlin*ncol)-1); //Calculo de um valor random
    if(nJogadas<3) {   //Probabilidade maior de jogar verde até chegar à 3 jogada
        while (i<10) {
            k += probEvento(0.75);
            i++;
        }
        if (k >= 5)
            *letra = 'v';
        else
            *letra ='p';

    }
    else if(nJogadas<7){  //Probabilidade das jogadas até à 7 jogada
        while (i < 10) {
            k += probEvento(0.33);
            i++;
        }
        if (k == 3) {
            *letra = 'v';

        } else if (k == 2 || k==4) {
            *letra = 'a';

        } else if (k == 1 || k==5 ) {
            *letra = 'r';

        } else if (k == 0) {
            *letra = 'c';

        } else {
            *letra = 'n';

        }
    }
    else {           //Probabilidade das jogadas apartir da 7 jogada
        while (i < 10) {
            k += probEvento(0.33);
            i++;
        }
        if (k == 3) {
            *letra = 'v';

        } else if (k == 2 || k == 4) {
            *letra = 'a';

        } else if (k == 1 || k == 5) {
            *letra = 'r';

        } else if (k == 0) {
            *letra = 'c';

        } else {
            *letra = 'n';

        }

    }


    return (pos);
}
//Função de leitura do teclado e limpeza do buffer
int ler_str(char *s,int max){
    int i=1;

    if(max<2) return 0; // String não tem comprimento suficiente para armazenar dados

    while( (s[0]=getchar()) =='\n' );  // Ignorar "lixo"

    while( ((s[i++]=getchar())!='\n')); // Ler caracteres até ao enter

    s[i-1]='\0'; // Marcar fim da string
    return 1;
}
//Verificação da existencia de ficheiro
int verificaFicheiro(char *fname){
    FILE *f= fopen(fname,"rb");
    if(f==NULL){

        return 0;
    }
    else {
        fclose(f);
        return 1;
    }

}