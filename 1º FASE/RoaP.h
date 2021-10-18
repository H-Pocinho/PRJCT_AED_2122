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


typedef struct data{ //Struct que define um nó numa lista
    int c;
    int l;

    struct data* next;
}data;


//Funções do ficheiro RoaP_main.c

void FASE1(char str[]);
int A1(int L, int C, int l, int c, int *maze);
int A234(int L, int C, int l, int c, int *maze,int v);
int A5(int L, int C, int l, int c, int *maze);
int A6(int L,int C,int linit,int cinit,int lend,int cend,int *maze);


//Funções do ficheiro RoaP_list.c

data *cria_no(int C,int L);
data *push(data *head,data *nodulo);
data *read_pop(data *head,int *C,int *L);
void liberta_lista(data *head);



#endif
