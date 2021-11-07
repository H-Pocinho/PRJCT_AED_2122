#ifndef ROAP_H_INCLUDED
#define ROAP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>


/*
 *Primeira fase de submisões porjecto AED
 *
 *Ficheiros:
 * -> Roap_main.c : contem o tronco principal do projecto
 * -> RoaP_list.c : contem funções de tratamento e manipulação de funções
 */

typedef struct data
{ // Struct que define um nó numa lista
    int c;
    int l;

    struct data *next;
} data;

/*struct para a função de encontrar salas*/
typedef struct info{
    unsigned int casa;

    struct info *next;
} info;



typedef struct edge
{ // Struct que define um nó do grafo
    int peso;
    int noLigado;
    int c;
    int l;
    struct edge* next;
} edge;

// Funções do ficheiro RoaP_main.c

void FASE1(char str[]);
void FASE2(char str[]);
int A1(int L, int C, int l, int c, int *maze);
int A234(int L, int C, int l, int c, int *maze, int v);
int A5(int L, int C, int l, int c, int *maze);
int A6(int L, int C, int linit, int cinit, int lend, int cend, int *maze);

int encontraSalas(int L, int C, int lend, int cend, int *maze,int* Sala);

int magicRoapSolver(int objectivo,int nV,edge** adj,FILE *FPOUT);

// Funções do ficheiro RoaP_list.c

data *cria_no(int C, int L);
data *push(data *head, data *nodulo);
data *read_pop(data *head, int *C, int *L);
void liberta_lista(data *head);

/*funçôes de manipulaçao de stack para a função de encontrar salas*/
info *cria_no_info(int c, int l, int C);
info *push_info(info *head, info *nodulo);
info *read_pop_info(info *head, int *casa);
void liberta_info(info *head);



edge **GRAPHinit(int V);
void GRAPHfill(int *maze,int C,int L,edge** LADJ);
edge* addNODE(edge* ADJ,int weight,int no,int c,int l);
void GRAPHfree(edge** LADJ,int nV);

void FixUp(int *acervo, int Idx, int *distancia);
void FixDown(int *acervo, int Idx, int *distancia,int Vn);
int removeFromHeap(int* vertex,int *acervo,int *distancia,int nV,int ocup);
int addToHeap(int vertex,int *acervo,int *distancia,int nV,int ocup);
int inHeap(int *acervo,int nV,int vertex);


#endif
