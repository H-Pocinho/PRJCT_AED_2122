#ifndef ROAP_H_INCLUDED
#define ROAP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h> 




#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdbool.h>

/*
*Primeira fase de submisões porjecto AED
*
*Ficheiros:
* -> Roap_main.c : contem o tronco principal do projecto
* -> RoaP_list.c : contem funções de tratamento e manipulação de funções
*/


typedef struct data{ //Struct que define um nó numa lista
    int c;          
    int l; 
    int dist;          

    struct data* next;
}data;

typedef struct Hdata{ //Struct que define um nó do acervo
    int c;          
    int l; 
    int dist;          
}Hdata;


//Funções do ficheiro RoaP_main.c

void FASE1(char str[]);
void FASE2(char str[]);
int A1(int L, int C, int l, int c, int *maze);
int A234(int L, int C, int l, int c, int *maze,int v);
int A5(int L, int C, int l, int c, int *maze);
int A6(int L,int C,int linit,int cinit,int lend,int cend,int *maze);

int magicRoapSolver(int L, int C, int lend, int cend, int *maze,FILE* FPOUT);


//Funções do ficheiro RoaP_list.c

data *cria_no(int C,int L,int dist);
data *push(data *head,data *nodulo);
data *read_pop(data *head,int *C,int *L);
void liberta_lista(data *head);



int HInsert(int c,int l, int dist, int size, int Idx, Hdata** acervo);
int HRemove(int* c,int* l, int size, int Idx, Hdata** acervo);
Hdata* novaData(int C,int L, int DIST);
void FixUp(Hdata** acervo, int Idx);
void FixDown(Hdata** acervo, int Idx, int N);
void libertem_a_heap(Hdata** acervo,int size);

#endif
