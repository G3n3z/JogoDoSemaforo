// DEIS-ISEC 2020-2021
//TP - Programacao - Licenciatura em Engenharia Informatica Pos Laboral
//Daniel Fernandes - a2020116565
//Turma Pratica P2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "jogo.h"

//Menu 1


int menu1(pjogada p,char* tab,int nlin,int ncol,int dimInicial, char *str1, char *str2, int versus, int nJogadas,pPlayer player){
    int  vencedor=0, jogador;
    char letra,verde='v', amarelo='a', pedra='p', addLinha='n', addCol='c', jogAnte='j', vermelho='r', sair='s';
    int pos, v=1, fich;
    char guarda[TAML], fname[TAMPLAYER];
    FILE *f;
    if(p!=NULL)     //Recuperação do id do jogador a ser o primeiro a jogar
        jogador = recuperaJogador(p);
    else
        jogador=1;

        while(vencedor==0) {

            do {
                if(!(versus==2  && jogador==2))
                    mostraJogo(nlin, ncol, tab);

                printf("Jogador 1 \nPedra: %d   Coluna: %d Linha:%d \n", player->maxPedraP, player->maxColP, player->maxLinhaP);
                printf("Jogador 2 \nPedra: %d   Coluna: %d Linha:%d \n", player->prox->maxPedraP, player->prox->maxColP, player->prox->maxLinhaP);
                if(versus==1 || (versus==2&&jogador==1)) // Pede jogada todas as vezes menos quando é o CPu a jogar
                    letra = pedeJogada(nlin, ncol, &pos, jogador, str1, str2, tab, nJogadas, player);
                else {
                    pos=0;
                    pos = posicaoAutomatica(&letra, nlin, ncol, nJogadas);
                }
                if (tolower(letra) == amarelo) {  //Verificacoes se no tabuleiro existe as peças pretendidas
                    v = verificaExistente(verde, pos, tab);
                    if (v == 0 && !(versus==2  && jogador==2))
                        printf("Jogada nao permitida. So e permitido colocar a peca amarela numa celula com uma peca verde");
                }
                if (tolower(letra) == vermelho) {
                    v = verificaExistente(amarelo, pos, tab);
                    if (v == 0 && !(versus==2  && jogador==2))
                        printf("Jogada nao permitida. So e permitido colocar a peca vermelha numa celula com uma peca amarela");
                }
                if (tolower(letra) == verde) {
                    v = verificaExistente(' ', pos, tab);
                    if (v == 0 && !(versus==2  && jogador==2))
                        printf("Espaço ocupado");
                }
                if (tolower(letra) == pedra) {  //Verificação da quantidade de pedras jogadas e se a jogada é válida
                    v = verificaPedra(&player->maxPedraP, &player->prox->maxPedraP, jogador);
                    if (v == 1) {
                        v = verificaExistente(' ', pos, tab);
                        if (v == 0 && !(versus==2  && jogador==2))
                            printf("Espaço ocupado");
                    } else
                        printf("Já adicionou uma pedra neste Jogo");
                }
                if (tolower(letra) == addCol) { //Verificação das colunas adicionadas
                    v = verificaPedra(&player->maxColP, &player->prox->maxColP, jogador);
                    if (v == 0)
                        printf("Já adicionou uma coluna neste Jogo");
                } else if (tolower(letra) == addLinha) { //Verificação das linhas adicionadas
                    v = verificaPedra(&player->maxLinhaP, &player->prox->maxLinhaP, jogador);
                    if (v == 0)
                        printf("Já adicionou uma linha neste Jogo");
                }



            } while (v == 0);   //Ciclo de validação


            if (tolower(letra) == addLinha || tolower(letra) == addCol) { //Adicionar uma coluna ou linha
                printf("AtualizaDimensao");
                nJogadas++;
                tab = aumentaTabuleiro(&ncol, &nlin, letra, addCol, addLinha, tab);
            }
            else if (tolower(letra) == jogAnte) { //Jogadas anteriores

                do {
                    printf("Quantas Jogadas para tras? : ");
                    scanf("%d", &pos);
                } while (pos < 1 || pos > nJogadas);
                printf("\n%d\n", dimInicial);
                mostraJogadas(p, pos, nJogadas, dimInicial, addCol, addLinha);
                continue;

            }

            else if (tolower(letra) == sair) { //Interrupção do jogo
                do {
                    printf("Pretende guardar o Jogo? \n S-Sim   N-Nao\nOpcao: ");
                    fgets(guarda, TAML, stdin);
                    guarda[strlen(guarda) - 1] = '\0';
                } while (tolower(guarda[0]) != 's' && tolower(guarda[0]) != 'n');

                if (tolower(guarda[0]) == 's') {
                    fich = verificaFicheiro(FILENAMEBIN);
                    if (fich == 1)
                        remove(FILENAMEBIN);
                    if(p==NULL){  //Não permite guardar um tabuleiro vazio
                        printf("Nao e possivel guardar um tabuleiro vazio\n");
                        break;
                    }
                    guardaDados(p, dimInicial, str1, str2, FILENAMEBIN, player);//Função de guardar dados em ficheiro

                }

                break;
            }


            else {
                atualizaTabuleiro(tab, &nJogadas, pos, letra); //Atualização do tabuleiro
            }

            p = atualizaEstrutura(p, letra, pos, jogador, nJogadas, player); //Atualização das listas ligadas
            atualizaEstruraJogador( player,jogador,letra, verde, amarelo,vermelho);


            if (ncol == nlin) { //Verificacoes de termino por vitória
                if (verificaColuna(nlin, ncol, tab, verde, amarelo, pedra, vermelho) ||verificaLinha(nlin, ncol, tab, verde, amarelo, pedra, vermelho) ||verificaDiagonal(nlin, ncol, tab, verde, amarelo, pedra, vermelho)) {
                    vencedor = 1;

                }
            } else {
                if (verificaColuna(nlin, ncol, tab, verde, amarelo, pedra, vermelho) ||verificaLinha(nlin, ncol, tab, verde, amarelo, pedra, vermelho)) {
                    vencedor = 1;

                }

            }

            printf("\n Jogadas:  %d\n", nJogadas);
            if(vencedor==0)
                jogador = jogador % 2 + 1;
        }


            if(vencedor==1) {       //Declaracao do vencedor
                if (jogador == 1) {
                    printf("\nVencedor(a): %s\n", str1);
                } else if (jogador == 2)
                    printf("\nVencedor(a): %s\n", str2);
                mostraJogo(nlin,ncol,tab);

                pede_nome_ficheiro(fname);  //Pede um ficheiro TXT

                guardaficheiro(fname,p, str1, str2,dimInicial); //Guarda os dados num ficheiro txt
                f= fopen(fname, "a");  //Escrever no ficheiro txt o vencedor
                if(f==NULL) {
                    printf("Nao foi possivel escrever no ficheiro");

                }
                else {
                    if (jogador == 1) {
                        fprintf(f, "\nVencedor(a): %s\n", str1);
                    } else if (jogador == 2)
                        fprintf(f, "\nVencedor(a): %s\n", str2);
                    fclose(f);
                }
            }


        libertaEstrutura(p);   //libertação de listas ligadas
        libertaEstrutura1(player);
        free(tab);
        return 1;



}
