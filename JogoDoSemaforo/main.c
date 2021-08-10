// DEIS-ISEC 2020-2021
//TP - Programacao - Licenciatura em Engenharia Informatica Pos Laboral
//Daniel Fernandes - a2020116565
//Turma Pratica P2
#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include <string.h>
#include <ctype.h>


// Daniel Fernandes LEI-PL N� de Aluno: 2020116565
// Jogo do Semaforo


int main()
{
    int menu=1, versus=0, ncol, nlin, nJogadas=0, fich,i, dim;

    pjogada jog;
    pPlayer player;

    char* tab;

    char str1[TAMPLAYER];   //Nomes dos jogadores
    char str2[TAMPLAYER];
    initRandom();



    while(menu!=0){        //Ciclo do menu principal
        jog=NULL;
        player=NULL;
        tab=NULL;
        fich=verificaFicheiro(FILENAMEBIN);     //verificação se existe o ficheiro
        menu=verificaInicio(fich);
        if(menu==0)
            break;




        /*if(fich==1 && menu==1) {
            remove(FILENAMEBIN);
            fich=0;
        }*/

        if(menu==1) {      //Se não existir ficheiro e for selecionado Novo jogo
            nlin = dimensaoInicial();// Pedido da dimens�o inicial
            dim = ncol = nlin;
            tab = inicializaTabuleiro(nlin);  //Inicializa��o da tabela
            versus = jogadorversus(str1, str2);     //Função do Segundo menu e que pede os nomes aos jogadores

            for (i = 0; i < 2; i++) {       //Inicialização de 2 jogadores
                player=inicializaPlayer(player);
            }

            if (versus==0) {        //Caso pretenda Sair do jogo no menu 2
                libertaEstrutura1(player);
                break; 
            }
        }
        else if(fich==1&&menu==2){ //Se existir ficheiro e for selecionado continuar Jogo
            jog = recuperaDados(&nJogadas, &nlin,str1,str2,FILENAMEBIN, player);

            if(strcmp(str2,"CPU")==0)
                versus=2;
            else
                versus=1;

            dim=ncol=nlin; //Guardar em dim, a dimensao inicial
            tab=recompoeTAB(jog,nJogadas,&nlin, &ncol,'c','n',player); //Reconstrução do tabuleiro
            player=jog->jogador;  //Como a função recupera dados não atualiza o ponteiro player
            player->prox=jog->jogador->prox; //Assim atualiza-se o ponteiro
            remove(FILENAMEBIN);
        }
        if(menu==1|| menu==2) { //Caso pretenda um novo jogo ou continuar um antigo

            menu = menu1(jog, tab, nlin, ncol,dim, str1, str2, versus, nJogadas, player);

        }

    }

    return 0;
}
