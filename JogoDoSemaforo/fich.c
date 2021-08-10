// DEIS-ISEC 2020-2021
//TP - Programacao - Licenciatura em Engenharia Informatica Pos Laboral
//Daniel Fernandes - a2020116565
//Turma Pratica P2
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"
#include <ctype.h>

//Processa os dados para escrita num ficheiro txt

void guardaficheiro(char *fname, pjogada p,char *str1, char *str2,int dimInicial) {
    int fich;


    int  ncol, nlin;
    char *tabRep = NULL;
    char addLinha = 'n', addCol = 'c', pedra = 'p';
    int i = 0, totalJogadas;
    fich= verificaFicheiro(fname);
    if(fich==1)             //Se existir um ficheiro com o nome, elimina o ficheiro
        remove(fname);


    pjogada aux;
    ncol = nlin = dimInicial;
    tabRep = inicializaTabuleiro(dimInicial);  //Inicializacao de um tabuleiro novo
    aux = p;
    while (aux->prox != NULL)       //percorre a estrutura para saber o total de jogadas
        aux = aux->prox;

    totalJogadas = aux->total;

    p->jogador->maxColP=p->jogador->maxLinhaP=p->jogador->maxPedraP=0; //inicializa os contadores a 0
    p->jogador->prox->maxPedraP=p->jogador->prox->maxLinhaP=p->jogador->prox->maxColP=0;//para impressao

    while (i < totalJogadas) { //Ciclo de recompor um tabuleiro para escrita em ficheiro


        if (tolower(p->jogada) == addLinha || tolower(p->jogada) == addCol) { //Se a jogada for add linha ou coluna

            tabRep = aumentaTabuleiro(&ncol, &nlin, p->jogada, addCol, addLinha, tabRep);
            if (p->jogada==addLinha)
                p->jogador->maxLinhaP++;        //Atualização da lista jogador para escrita
            else if (p->jogada==addCol)
                p->jogador->maxColP++;

            i++;
        }

        else {
            if (p->jogada==pedra)
                p->jogador->maxPedraP++;     //Atualização da lista para escrita

            atualizaTabuleiro(tabRep, &i, p->posicao, p->jogada);   //Atualização do tabuleiro para escrita
        }
        escreveJogo(nlin,ncol,tabRep, fname,p,str1,str2); //Escrita do tabuleiro

        p = p->prox; //Atualizacao do no da lista de jogadas
    }

    free(tabRep);
}

//Recuperacao dos dados de um ficheiro binario
pjogada recuperaDados(int *njogadas,int *dimInicial,char *str1, char *str2, char *fname, pPlayer j){
    pjogada p=NULL, novo;
    pPlayer aux;
    FILE *f = fopen(fname, "rb");
    int total,i;

    if(f==NULL){
        printf("\nErro ao abrir o ficheiro\n %s", fname);
        return NULL;
    }

    fread(str1,sizeof (str1),1,f); //Leitura do nome do jogador1

    fread(str2, sizeof (str2), 1 ,f);//Leitura do nome do jogador1


    fread(&i,sizeof (int), 1,f);  //Leitura da dimensao inicial
    (*dimInicial)=i;

    fread(&total,sizeof (int), 1,f); //Leitura do totla de jogadas
    *njogadas=total;


    for(i=0;i<2;i++) {       //leitura dos nos da lista dos jogador
        aux = malloc(sizeof(pl));
        if (aux == NULL) {
            fclose(f);
            printf("Nao foi possivel alocar memoria");
            return NULL;
        }
        fread(aux, sizeof(pl), 1, f);
        if(i==0){
            j=aux;
        }

    }
    j->prox=aux;    //Atribuição do segundo no da lista
    j->prox->prox=NULL;

    for (i=0;i<total;i++){   //Leitura da lista de jogadas
        novo = malloc(sizeof (jogada));

        if(novo==NULL){
            fclose(f);
            printf("Nao foi possivel alocar memoria");
            return NULL;
        }
        fread(novo,sizeof (jogada),1,f);

        p=atualizaEstrutura(p,novo->jogada, novo->posicao, novo->iJogador, novo->total, j); //Atualização da lista
        free(novo);  // Libertacao de memoria


    }
    fclose(f);
    return p;

}

//Armazenamento dos dados essenciais para retomar o jogo mais tarde
void guardaDados(pjogada p, int dimInicio,char *str1,char *str2,char *fname, pPlayer j) {
    FILE *f= fopen(fname,"wb");
    pjogada aux;
    pPlayer aux2;
    int totalJogadas;
    if(f==NULL){
        printf("\nErro ao abrir o ficheiro\n %s", fname);
        return;
    }
    aux=p;
    if(p==NULL)
        return;

    while (aux->prox!=NULL)
        aux=aux->prox;

    totalJogadas=aux->total;      //percorre a estrutura para saber o total de jogadas
    aux=p;
    fwrite(str1,sizeof (str1),1,f);  //Armazenamento do nome do jogador1
    fwrite(str2,sizeof (str2),1,f);     //Armazenamento do nome do jogador2
    fwrite(&dimInicio,sizeof (int),1,f);   //Armazenamento da dimensao inicial
    fwrite(&totalJogadas,sizeof (int),1,f); //Armazenamento do total de jogadas
    fwrite(j,sizeof (pl),1,f);          //Armazenamento do 1 no da lista de jogador
    aux2=j->prox;

    fwrite(aux2,sizeof (pl),1,f); //Armazenamento do 2 no da lista de jogador

    while (aux!=NULL){      //Armazenamento do nos da lista de jogadas
        fwrite(aux,sizeof (jogada),1,f);
        aux=aux->prox;
    }
    fclose(f);

}


//Funcao que escreve no ficheiro txt
void escreveJogo(int n_lin, int n_col,char *tab, char *fname, pjogada p,char *str1, char *str2){

    FILE *f;
     int i, j,k;
    f= fopen(fname, "a");
    if(f==NULL) {
        printf("Nao foi possivel escrever no ficheiro");
        return;
    }

    fprintf(f,"\n\n");

    fprintf(f,"JOGADA:  %d\n\n", p->total);



    if(p->iJogador==1) {
          fprintf(f,"Jogada Realizada por %s\n", str1);

    }

    else {
          fprintf(f,"Jogada Realizada por %s\n", str2);

    }
    fprintf(f,"Cor: %c || Posicao: %d\n\n",p->jogada,p->posicao+1);
    fprintf(f,"Numero de pedras adicionadas pelo jogador: %d\n", p->jogador->maxPedraP);
    fprintf(f,"Numero de linhas adicionadas pelo jogador: %d\n", p->jogador->maxLinhaP);
    fprintf(f,"Numero de colunas adicionadas pelo jogador: %d\n", p->jogador->maxColP);

    for(i=0;i<n_lin;i++){    //Impressao em ficheiro do tabuleiro
        for(j=0;j<n_col;j++){
            fprintf(f," %c ", *(tab+n_col*i+j));
            if(j<n_col-1)
                fprintf(f,"|");


        }
        fprintf(f,"   ( %d - %d) ", n_col*i+j+1-n_col,n_col*i+j); //Impressao dos indices de jogada
        if(i<n_lin-1) {              //Impressao das divisoes entre caracteres
            fprintf(f, "\n");
            for (k = 0; k < n_col; k++) {
                fprintf(f,"----");
            }
            fprintf(f,"\n");
        }
    }
    fprintf(f,"\n\n\n\n\n");

    fclose(f);
}
