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

*/

typedef struct data{
    int c;
    int l;

    struct data* next;
}data;


void FASE1(char str[]);
int A1(int L, int C, int l, int c, int *maze);
int A234(int L, int C, int l, int c, int *maze,int v);
int A5(int L, int C, int l, int c, int *maze);
int A6(int L,int C,int linit,int cinit,int lend,int cend,int *maze);

data *cria_no(int C,int L);
data *insere_head(data *head,data *nodulo);
data *read_remove_head(data *head,int *C,int *L);
void liberta_lista(data *head);
int search(data* head, int C, int L);



#endif
