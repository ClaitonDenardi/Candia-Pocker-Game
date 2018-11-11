/*
********************************************************************************
* Header para o problema das maos de poquer.
* Este codigo tem fins educacionais e pode conter erros. Nao ha garantias de que
* o mesmo funcione sempre como esperado.
* Versao: 0.2 candia@inf.ufsm.br
********************************************************************************
*/
#ifndef MAOSPOQUER_H

#define TAM_DEQUE	52
#define SEMENTE		1
#define VALOR		0
#define	NAIPE		1
#define N           50


typedef enum {OUROS, ESPADAS, COPAS, BASTOS} NAIPES_T;

/* tipo a ser usado para a fila correspondente a mão do usuário */
typedef struct n {
	int valor;
	int naipe;
	struct n *prox;
} MAO_T;

void imprimeBaralhoVetor(int cartas[][2]);
void criaBaralho(int cartas[][2]);
void embaralha(int cartas[][2], unsigned int semente);
int contaPontos(MAO_T *mao);
MAO_T* pegaCarta(MAO_T* cartas, int valor, int naipe);
MAO_T* criaMao();
MAO_T* criaFila();
MAO_T* preencheFila(MAO_T* cartas, int baralho[][2], int carta_atual);
void imprimeFila(MAO_T* cartas);
MAO_T* criaCarta(int baralho[][2],int carta_atual,MAO_T* cartas);
int cartasRestantes(MAO_T* cartas);
void imprimeCartaTopo(MAO_T* cartas, MAO_T* pilha_cartas);
void tela(int baralho[][2]);
MAO_T* pilha_push(int baralho[][2],int carta_atual, MAO_T* pilha_cartas);
MAO_T* pilha_pop(MAO_T** pilha_cartas);
void incrementoCartaAtual(int* carta_atual);
void imprimePilha(MAO_T* pilha_cartas);
int restantesPilha(MAO_T* pilha_cartas);
void adcCartaMao(MAO_T** fila1, MAO_T** fila2, MAO_T** fila3, MAO_T** fila4, MAO_T** fila5, MAO_T** fila6, MAO_T** fila7, MAO_T** maoCartas, MAO_T** pilha_cartas);
void imprimeFileiras(MAO_T* fila1,MAO_T* fila2,MAO_T* fila3,MAO_T* fila4,MAO_T* fila5,MAO_T* fila6,MAO_T* fila7);
void retiraMonte(MAO_T** maoCartas, MAO_T** pilha_cartas);
void colocaCartaMao(MAO_T** maoCartas, MAO_T** fila);
MAO_T* descartaCartas(MAO_T* maoCartas);
MAO_T* pushCarta(MAO_T* monte, int valor, int naipe);

void colocaCartaMonte(MAO_T** monte, MAO_T** fila);

void adcCartaMonte(MAO_T** fila1,MAO_T** fila2,MAO_T** fila3,MAO_T** fila4,MAO_T** fila5,MAO_T** fila6,MAO_T** fila7, MAO_T** monte);

#define MAOSPOQUER_H
#endif
