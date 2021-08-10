// DEIS-ISEC 2020-2021
//TP - Programacao - Licenciatura em Engenharia Informatica Pos Laboral
//Daniel Fernandes - a2020116565
//Turma Pratica P2
#ifndef JOGO_H
#define JOGO_H
#define TAMPLAYER 256
#define TAML 3
#define FILENAMEBIN "jogo.bin"


typedef struct dados jogada, *pjogada;
typedef struct nome pl, *pPlayer;

struct dados{

    pPlayer jogador; //Numero do jogador que efetuou a Jogada
    int iJogador;
    char jogada; // Letra da Jogada
    int total;  //Total de Jogadas
    int posicao;    //posi��o da Jogada
    pjogada prox; //Ponteiro para a proxima jogada
};

struct nome{
    int jog; //Indice do jogador
    int maxLinhaP; //Linhas adicionadas
    int maxColP;   //Colunas adicionadas
    int maxPedraP; //Pedras adicionas
    int verde;     //Pecas verdes adicionadas
    int amarelo;    //Pecas amarelas adicionadas
    int red;        //Pecas vermelhas adicionadas
    pPlayer prox;   //Ponteiro para o proximo jogador
};
void initRandom();   // Função fornecida pelos professores
int verificaFicheiro(char *fname);  //Verifica se existe um ficheiro com o nome fname

int recuperaJogador(pjogada p);     //No caso de continuar um jogo anterior, recupera a vez do ultimo jogador

void mostraInicio();    //Mostra no ecra as regras inicias

int verificaInicio(int fich);   // Mostra e obtém do utlizador a opção de Novo Jogo/Retomar/Sair

int dimensaoInicial();      //Função que determina a dimensão Inicial

char *inicializaTabuleiro(int dim);  //Aloca memória para um tabuleiro e coloca os seus caracteres a vazio

void mostraJogo(int n_lin, int n_col,char *tab);   //Mostra o estado do tabuleiro

int jogadorversus(char *str1,char *str2);   //Pede ao utilizador os nomes

int menu1(pjogada p,char* tab,int nlin,int ncol,int dimInicial,char *str1, char *str2, int versus,int nJogadas, pPlayer player);
//  Função que faz a festão do decorrer do jogo

char pedeJogada(int nlin, int ncol,int* pos,int jog, char *p1, char* p2, char *tab, int njogadas, pPlayer player);
//Função que pede jogada ao utilizador e faz algumas validações da jogada

void atualizaTabuleiro(char* tab,int *njogadas,int pos,char letra); //Função atualiza o tabuleiro com a cor inserida

int verificaLinha(int nlin,int ncol,char* tab,char verde,char amarelo,char pedra, char vermelho); // Verificação do termino do jogo por linha

int verificaDiagonal(int nlin,int ncol,char* tab,char verde,char amarelo,char pedra, char vermelho);// Verificação do termino do jogo por coluna

int verificaColuna(int nlin,int ncol,char* tab,char verde,char amarelo,char pedra, char vermelho);// Verificação do termino do jogo pelas diagonais

int verificaExistente(char cor,int pos, char *tab); //Verifica se na posição enviada existe o caracter enviado

char *aumentaTabuleiro(int* ncol, int* nlin, char letra, char addCol, char addLin, char *tab);
//Função que aumenta a dimensão do tabuleiro

int verificaPedra(int *add1,int * add2, int jog); //Verifica se o jogador já jogou uma pedra

pjogada atualizaEstrutura(pjogada p,char letra,int pos,int jogador,int nJogadas, pPlayer j); //Atualiza a estrutura das jogadas

void mostraJogadas(pjogada p,int pos, int njogadas, int dim, char addCol,char addlinha);
//Função que mostra as jogadas anteriores pretendidas

void guardaDados(pjogada p, int dimInicio,char *str1,char *str2, char *fname, pPlayer j);
//Guarda os dados essenciais no ficheiro jogo.bin

pjogada recuperaDados(int *njogadas,int *dimInicial,char *str1, char *str2, char *fname, pPlayer j);
//leitura do ficheiro binário da informação guardada

char* recompoeTAB(pjogada p, int njogadas,  int *nlin,int *ncol, char addCol,char addLinha, pPlayer player);
//Função que a partir da estrutura recupera um tabuleiro

pPlayer inicializaPlayer(pPlayer player);
//Função que inicializa uma estrutura com 2 jogadores

int posicaoAutomatica(char *letra, int nlin, int ncol, int nJogadas);
//Calcula uma cor e uma jogada automática

void escreveJogo(int n_lin, int n_col,char *tab, char *fname, pjogada p, char *str1, char *str2);
//Escreve num ficheiro txt um estado do tabuleiro
void guardaficheiro(char *fname, pjogada p,char *str1, char *str2,int dimInicial);
//Percorre a estrutura recompondo um tabuleiro jogada a jogada e chamando a função escreveJogo para escrever num ficheiro
//todos os estados do tabuleiro

void pede_nome_ficheiro(char *fname);//Pede ao utilizador o nome do ficheiro no qual quer gravar os estados do jogo

void libertaEstrutura(pjogada p);  //Funções de libertar as estruturas
void libertaEstrutura1(pPlayer player);

int ler_str(char *s,int max);  //Função de leitura de uma string

void mostraJogadasDisponiveis(pPlayer p, pPlayer p2, int nlin,int ncol); //Função que mostra as jogadas que podem ser jogadas

void atualizaEstruraJogador(pPlayer p, int jogador, char letra, char verde, char amarelo, char red);
// Atualização da estrutura dos Jogadores
#endif


