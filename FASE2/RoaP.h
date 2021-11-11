#ifndef ROAP_H_INCLUDED
#define ROAP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>



/*
 *Segunda fase de submisões projecto AED
 *
 *Ficheiros:
 *
 * RoaP_main.c -> onde se encontra o main
 * 
 * RoaP_fase1.c -> todas as funções relativas a funcionalidades da primeira fase
 * 
 * RoaP_fase2.c -> todas as funções relativas a funcionalidades da segunda fase
 * 
 * RoaP_grafo.c -> todas as funções relativas a gestão de um grafo implementado usando uma lista de adjacencisa utilizado na segunda fase
 * 
 * RoaP_heap.c -> todas as funções relativas a gestão de um acervo utilizado na segunda fase
 * 
 * RoaP_DFS_tabela_fase2.c -> todas as funções relativas a gestão de uma stack explicita implementada usando uma tabela utilizada na segunda fase
 * 
 * RoaP_DFS_lista_fase1.c -> todas as funções relativas a gestão de uma stack explicita implementada usando uma lista utilizada na primeira fase
 */

typedef struct data
{ // Struct que define um nó numa lista para ser usada no DFS
    int c;
    int l;

    struct data *next;
} data;

typedef struct edge
{ // Struct que define um nó do grafo utilizado num lista de adj
    int peso;
    int noLigado;
    int c;
    int l;
    struct edge* next;
} edge;


typedef struct stack 
{ //Struct que define uma stack explicitamente para ser usada no DFS da segunda fase
    int top;
    unsigned capacity;
    int* array;
} stack;


// Funções relativas á fase 1
void FASE1(char str[]);
int A1(int L, int C, int l, int c, int *maze);
int A234(int L, int C, int l, int c, int *maze, int v);
int A5(int L, int C, int l, int c, int *maze);
int A6(int L, int C, int linit, int cinit, int lend, int cend, int *maze);

//funções relativas á fase 2
void FASE2(char str[]);
int encontraSalas(int L, int C, int lend, int cend, int *maze,int* Sala);
int magicRoapSolver(int objectivo,int nV,edge** adj,FILE *FPOUT);


//Funções relativas á gestão de uma pilha explicita utilizada no DFS na fase 1
data *cria_no(int C, int L);
data *push(data *head, data *nodulo);
data *read_pop(data *head, int *C, int *L);
void liberta_lista(data *head);

//Funções relativas á gestão de um grafo na fase 2
edge **GRAPHinit(int V);
void GRAPHfill(int *maze,int C,int L,edge** LADJ);
edge* addNODE(edge* ADJ,int weight,int no,int c,int l);
void GRAPHfree(edge** LADJ,int nV);

//Funções relativas á gestão de um acervo na fase 2
void FixUp(int *acervo, int Idx, int *distancia);
void FixDown(int *acervo, int Idx, int *distancia,int Vn);
int removeFromHeap(int* vertex,int *acervo,int *distancia,int nV,int ocup);
int addToHeap(int vertex,int *acervo,int *distancia,int nV,int ocup);
int inHeap(int *acervo,int nV,int vertex);


//Funções relativas á gestão de uma stack explicita usada no DFS na fase 2
stack* createStack(unsigned capacity);
int isFullStack(stack*);
int isEmptyStack(stack*);
void pushStack(stack*, int);
int popStack(stack*);
void freeStack(stack*);


#endif
