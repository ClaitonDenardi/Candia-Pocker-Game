/*
********************************************************************************
* Algumas funcoes uteis para o problema das maos de poquer.
* Este codigo tem fins educacionais e pode conter erros. Nao ha garantias de que
* o mesmo funcione sempre como esperado.
* Versao: 0.2 candia@inf.ufsm.br
********************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "maosPoquer.h"

void imprimeBaralhoVetor(int cartas[][2]){
	int i;
	for(i=0; i<TAM_DEQUE; i++)
		printf("[%i %i]", cartas[i][0], cartas[i][1]);
	return;
}

/* Cria um baralho padrao de 52 cartas em um vetor passado por referencia */
void criaBaralho(int cartas[][2]){
	long int i, j=0;
	NAIPES_T n;
	/* geração do baralho ordenado */
	for(n=OUROS; n<=BASTOS; n++){
		for(i=1; i<=13; i++){
			cartas[j][VALOR] = i;
			cartas[j][NAIPE] = n;
			j++;
		}
	}
	return;
}

/* Embaralha as 52 cartas constantes em um vetor passado por referencia */
void embaralha(int cartas[][2], unsigned int semente){
	int i, j, aux_v, aux_n;
	/* EMBARALHAMENTO */
	srand(semente);
	for(i=0; i<TAM_DEQUE; i++){
		j = (unsigned long int) rand() % TAM_DEQUE;
		aux_v = cartas[i][VALOR];
		aux_n = cartas[i][NAIPE];
		cartas[i][VALOR] = cartas[j][VALOR];
		cartas[i][NAIPE] = cartas[j][NAIPE];
		cartas[j][VALOR] = aux_v;
		cartas[j][NAIPE] = aux_n;
	}
	return;
}

/* Conta os pontos de uma mao de 5 cartas, de acordo com as regras de pontuacao. */
/* A mao deve vir ordenada, por valor da carta, em ordem ascendente. */
/* (IMPORTANTE: para fins desta ordenacao, o As vale 1) */
int contaPontos(MAO_T *mao){
	MAO_T *ptrAux;
	int cont=0, flush=0, straight=0, royalStraight=0;
	int cont2=0;

	/* verifica Flush */
	for(ptrAux = mao->prox; ptrAux != NULL; ptrAux = ptrAux->prox){
		if(ptrAux->naipe == mao->naipe)
			cont ++;
	}
	if(cont == 4)
		flush = 1; /* é um flush */

	/* verifica Royal Straight */
	ptrAux = mao;
	if(ptrAux->valor == 1 && ptrAux->prox->valor == 10){
		/* somente pode ser royal se a 1a carta é ás e 2a é 10 */
		for(ptrAux = mao->prox, cont=0; ptrAux->prox != NULL; ptrAux = ptrAux->prox){
			if(ptrAux->valor == (ptrAux->prox->valor - 1))
				cont ++;
		}
		if(cont == 3)
			royalStraight = 1; /* é um royal straight */
	}

	if(flush && royalStraight) /* mão é um royal straight flush */
		return 1000;

	/* verifica Straight simples */
	for(ptrAux = mao, cont=0; ptrAux->prox != NULL; ptrAux = ptrAux->prox){
		if(ptrAux->valor == (ptrAux->prox->valor - 1))
			cont ++;
	}
	if(cont == 4)
		straight = 1; /* é um straight simples */

	if(flush && straight) /* mão é um straight flush */
		return 750;

	if(royalStraight || straight) /* mão é um straight */
		return 150;

	if(flush) /* mão é flush */
		return 200;

	/* verifica pares, trincas e quadras */
	cont = cont2 = 0;
	ptrAux = mao;
	while((ptrAux->prox != NULL) && (ptrAux->valor != ptrAux->prox->valor))
		ptrAux = ptrAux->prox;
	while((ptrAux->prox != NULL) && (ptrAux->valor == ptrAux->prox->valor)){
		cont++;
		ptrAux = ptrAux->prox;
	}
	while((ptrAux->prox != NULL) && (ptrAux->valor != ptrAux->prox->valor))
		ptrAux = ptrAux->prox;
	while((ptrAux->prox != NULL) && (ptrAux->valor == ptrAux->prox->valor)){
		cont2++;
		ptrAux = ptrAux->prox;
	}
	/* se foi encontrado algum par, trinca, four ou full house, é necessário */
	/* fazer cont e cont2 conter numero correto de cartas iguais encontradas */
	if(cont > 0) /* normalizando valor do primeiro contador */
		cont++;
	if(cont2 > 0) /* normalizando valor do segundo contador */
		cont2++;
	/* após normalizaçao, cont e cont2 podem ser usados para verificacao */
	switch(cont+cont2){
		case 5: /* mão é um full house */
			return 300;
		case 4: /* four ou dois pares */
			if(cont == 4 || cont2 == 4)
				return 500;
			else
				return 50;
		case 3: /* trinca */
			return 100;
		case 2: /* par simples */
			return 25;
	}
	return 0;
}

/*Pega a carta e poe ordenadamente na mão*/
MAO_T* pegaCarta(MAO_T* cartas, int valor, int naipe){
    MAO_T* aux;
    MAO_T* ant = NULL;
    MAO_T* nova_carta = (MAO_T*) malloc(sizeof(MAO_T));
    nova_carta->valor = valor;
    nova_carta->naipe = naipe;
    if (cartas == NULL){
        nova_carta->prox = cartas;
    } else {
        for(aux = cartas; aux != NULL; aux = aux->prox){
            if (aux->naipe > naipe || aux->valor > valor){
                break;
            }
            ant = aux;
        }
        if(ant == NULL){
            cartas = nova_carta;
            nova_carta->prox = aux;
        }else{
            ant->prox = nova_carta;
            nova_carta->prox = aux;
            return cartas;
        }
    }
    return nova_carta;
}

/*Funcao que administra o POP na pilha*/
void retiraMonte(MAO_T** maoCartas, MAO_T** pilha_cartas){
    MAO_T* cartaTopo = NULL;
    if (restantesPilha(*maoCartas) < 5) {
        cartaTopo = pilha_pop(&(*pilha_cartas));
        *maoCartas = pegaCarta(*maoCartas, cartaTopo->valor, cartaTopo->naipe);
        free(cartaTopo);
    }
    else
        printf("\n\n\t***MAO CHEIA! NAO E POSSIVEL PEGAR MAIS CARTAS!***\n");
}

MAO_T* criaFila(){
    return NULL;
}

/*Função para dar push na pilha/monte */
MAO_T* pilha_push(int baralho[][2], int carta_atual, MAO_T* pilha_cartas){
    MAO_T* nova_carta= (MAO_T*)malloc(sizeof(MAO_T));
    nova_carta->valor= baralho[carta_atual][0];
    nova_carta->naipe= baralho[carta_atual][1];
    nova_carta->prox= pilha_cartas;
    return nova_carta;
}

/*Função para dar pop na pilha=monte */
MAO_T* pilha_pop(MAO_T** pilha_cartas){
    MAO_T* cartaRetorno = *pilha_cartas;
    *pilha_cartas = (*pilha_cartas)->prox;
    return cartaRetorno;
}

/*Função para incremento de um índice artificial*/
void incrementoCartaAtual(int* carta_atual){
    *carta_atual+=7;
}

/*Função para preencher uma fila com 7 cartas*/
MAO_T* preencheFila(MAO_T* cartas, int baralho[][2], int carta_atual){
    for(int i=0;i<7;i++){
        cartas= criaCarta(baralho, carta_atual, cartas);
        carta_atual++;
    }
    return cartas;
}

/*Cria carta*/
MAO_T* criaCarta(int baralho[][2],int carta_atual,MAO_T* cartas){
    MAO_T* nova_carta= (MAO_T*) malloc(sizeof(MAO_T));
    nova_carta->valor= baralho[carta_atual][0];
    nova_carta->naipe= baralho[carta_atual][1];
    nova_carta->prox= cartas;
    return nova_carta;
}

/*Função para imprimir uma fila*/
void imprimeFila(MAO_T* cartas){
    MAO_T* aux;
    if (cartas != NULL) {
        for(aux = cartas;aux != NULL; aux = aux->prox){
            printf("[%i %i]\t", aux->valor, aux->naipe);
        }
        printf("\n");
    }
    else
        printf("Vazio!\n");
}

/*Conta cartas restantes em uma fila*/
int cartasRestantes(MAO_T* cartas){
    MAO_T* aux;
    int numCartas=0;
    for(aux = cartas;aux != NULL; aux = aux->prox){
        numCartas++;
    }
    return numCartas;
}

/*Função para contar quantas cartas há na pilha, fora a do topo*/
int restantesPilha(MAO_T* pilha_cartas){
    MAO_T* aux;
    int numCartasP=0;
    for(aux=pilha_cartas;aux!=NULL; aux=aux->prox){
        numCartasP++;
    }
    return numCartasP;
}

/*Coloca carta na mão e emite aviso caso a mão esteja cheia*/
void colocaCartaMao(MAO_T** maoCartas, MAO_T** fila){
    MAO_T* primeiraCarta = *fila;
    if (restantesPilha(*maoCartas) < 5){
        *fila = (*fila)->prox;
        *maoCartas = pegaCarta(*maoCartas, primeiraCarta->valor, primeiraCarta->naipe);
        free(primeiraCarta);
    }
    else{
        printf("\n\n\t***MAO CHEIA! NAO EH POSSIVEL PEGAR MAIS CARTAS!***\n");
    }
}

/*Funcao PUSH no monte*/
MAO_T* pushCarta(MAO_T* monte, int valor, int naipe) {
    MAO_T* nova_carta= (MAO_T*) malloc(sizeof(MAO_T));
    nova_carta->valor= valor;
    nova_carta->naipe= naipe;
    nova_carta->prox= monte;
    return nova_carta;
}

/*Coloca carta no monte*/
void colocaCartaMonte(MAO_T** monte, MAO_T** fila) {
    MAO_T* primeiraCarta = *fila;
    *fila = (*fila)->prox;
    *monte = pushCarta(*monte, primeiraCarta->valor, primeiraCarta->naipe);
    free(primeiraCarta);
}

/*Verifica qual carta o usuário deseja colocar no monte e chama função responsvel*/
void adcCartaMonte(MAO_T** fila1,MAO_T** fila2,MAO_T** fila3,MAO_T** fila4,MAO_T** fila5,MAO_T** fila6,MAO_T** fila7, MAO_T** monte) {
    int filaEscolhida;
    printf("Selecione uma opcao (1 a 7):  ");
    scanf("%d", &filaEscolhida);
    switch(filaEscolhida){
        case 1:
            colocaCartaMonte(monte, fila1);
            break;
        case 2:
            colocaCartaMonte(monte, fila2);
            break;
        case 3:
            colocaCartaMonte(monte, fila3);
            break;
        case 4:
            colocaCartaMonte(monte, fila4);
            break;
        case 5:
            colocaCartaMonte(monte, fila5);
            break;
        case 6:
            colocaCartaMonte(monte, fila6);
            break;
        case 7:
            colocaCartaMonte(monte, fila7);
            break;
        default: printf("ENTRADA INVALIDA!\n");
    }
}

/*Verifica qual carta o jogador quer adicionar a mao e chama função responsável*/
void adcCartaMao(MAO_T** fila1,MAO_T** fila2,MAO_T** fila3,MAO_T** fila4,MAO_T** fila5,MAO_T** fila6,MAO_T** fila7, MAO_T** maoCartas, MAO_T** pilha_cartas){
    int filaEscolhida;
    printf("Selecione uma opcao (1 a 8):  ");
    scanf("%d", &filaEscolhida);
    switch(filaEscolhida){
        case 1:
            colocaCartaMao(maoCartas, fila1);
            break;
        case 2:
            colocaCartaMao(maoCartas, fila2);
            break;
        case 3:
            colocaCartaMao(maoCartas, fila3);
            break;
        case 4:
            colocaCartaMao(maoCartas, fila4);
            break;
        case 5:
            colocaCartaMao(maoCartas, fila5);
            break;
        case 6:
            colocaCartaMao(maoCartas, fila6);
            break;
        case 7:
            colocaCartaMao(maoCartas, fila7);
            break;
        case 8:
            retiraMonte(maoCartas, pilha_cartas);
            break;
        default: printf("ENTRADA INVALIDA!\n");
    }
    printf("\n---MAO---\n");
    imprimeFila(*maoCartas);
}

/*Imprimir o monte*/
void imprimePilha(MAO_T* pilha_cartas){
    if (pilha_cartas != NULL)
        printf("[%i %i] ", pilha_cartas->valor, pilha_cartas->naipe);
    else
        printf("Vazio!\n");
}

/*Função para imprimir as 7 fileiras de cartas */
void imprimeFileiras(MAO_T* fila1,MAO_T* fila2,MAO_T* fila3,MAO_T* fila4,MAO_T* fila5,MAO_T* fila6,MAO_T* fila7){
    printf("Fila 1-\t");
    imprimeFila(fila1);
    printf("\n");
    printf("Fila 2-\t");
    imprimeFila(fila2);
    printf("\n");
    printf("Fila 3-\t");
    imprimeFila(fila3);
    printf("\n");
    printf("Fila 4-\t");
    imprimeFila(fila4);
    printf("\n");
    printf("Fila 5-\t");
    imprimeFila(fila5);
    printf("\n");
    printf("Fila 6-\t");
    imprimeFila(fila6);
    printf("\n");
    printf("Fila 7-\t");
    imprimeFila(fila7);
}

/*Descarta uma carta da mão e libera a memória*/
MAO_T* descartaCartas(MAO_T* maoCartas) {
    MAO_T* aux;
    printf("MAO DESCARTADA: \n");
    for (aux = maoCartas; aux != NULL; aux = aux->prox) {
        printf("[%i %i] ", aux->valor, aux->naipe);
        free(aux);
    }
    return aux;
}


void tela(int baralho[][2]){
    int acao=0;
    int carta_atual = 0;
    int pontos = 0;
    bool sair = false;

    MAO_T* pilha_cartas = NULL;
    MAO_T* fila1= criaFila();
    MAO_T* fila2= criaFila();
    MAO_T* fila3= criaFila();
    MAO_T* fila4= criaFila();
    MAO_T* fila5= criaFila();
    MAO_T* fila6= criaFila();
    MAO_T* fila7= criaFila();
    MAO_T* maoCartas= criaFila();

    fila1 = preencheFila(fila1, baralho, 0);
    incrementoCartaAtual(&carta_atual);

    fila2 = preencheFila(fila2, baralho, 7);
    incrementoCartaAtual(&carta_atual);

    fila3 = preencheFila(fila3, baralho, 14);
    incrementoCartaAtual(&carta_atual);

    fila4 = preencheFila(fila4, baralho, 21);
    incrementoCartaAtual(&carta_atual);

    fila5 = preencheFila(fila5, baralho, 28);
    incrementoCartaAtual(&carta_atual);

    fila6 = preencheFila(fila6, baralho, 35);
    incrementoCartaAtual(&carta_atual);

    fila7 = preencheFila(fila7, baralho, 42);
    incrementoCartaAtual(&carta_atual);

    pilha_cartas = pilha_push(baralho, carta_atual, pilha_cartas);
    carta_atual++;
    pilha_cartas = pilha_push(baralho, carta_atual, pilha_cartas);
    carta_atual++;
    pilha_cartas = pilha_push(baralho, carta_atual, pilha_cartas);

    while(!sair){
        printf("\n");
        imprimeFileiras(fila1, fila2, fila3, fila4, fila5, fila6, fila7);
        printf("\n\nSELECIONE UMA OPCAO\n");
        printf("[1] - Colocar carta na mão\n");
        printf("[2] - Colocar carta no monte\n");
        printf("[3] - Mostrar mao\n");
        printf("[4] - Contabilizar pontos (DESCARTA A MAO)\n");
        printf("[5] - Sair do jogo\n");
        scanf("%d", &acao);
        switch(acao) {
            case 1: /*pega carta na mao*/
                printf("\n");
                imprimeFileiras(fila1, fila2, fila3, fila4, fila5, fila6, fila7);
                printf("\nMonte 8- ");
                imprimePilha(pilha_cartas);
                printf("+%i",restantesPilha(pilha_cartas) - 1);
                printf("\n\n");
                adcCartaMao(&fila1, &fila2, &fila3, &fila4, &fila5, &fila6, &fila7, &maoCartas, &pilha_cartas);
                break;
            case 2: /*coloca carta no monte*/
                adcCartaMonte(&fila1, &fila2, &fila3, &fila4, &fila5, &fila6, &fila7, &pilha_cartas);
                break;
            case 3: /*mostrar mao*/
                imprimePilha(maoCartas);
                break;
            case 4: /*contabilizar pontos*/
                pontos += contaPontos(maoCartas);
                maoCartas = descartaCartas(maoCartas);
                printf("TOTAL PONTOS = %d\n", pontos);
                break;
            case 5: /*sair do jogo*/
                sair = !sair;
                break;
            default: printf("ENTRADA INVALIDA!\n");
        }
    }
}
