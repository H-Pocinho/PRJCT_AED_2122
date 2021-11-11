#include "RoaP.h"

/*
 *Nome da funcao: GRAPHfree
 *
 * Objetivo da funcao: limpar a memoria alocada para a estrutura de dados do grafo
 * 
 * Argumentos de entrada:
 *          **LADJ: ponteiro para a estrutura de dados
 *          nV: numero de vertices do grafo
 * 
 * Argumentos de saida: void
 * 
 */

void GRAPHfree(edge** LADJ,int nV){
    int i;
    edge* aux;
    edge* freeable;
    for ( i = 0; i < nV; i++)
    {
        aux=LADJ[i];
        while (aux!=NULL)
        {
            freeable=aux;
            aux=aux->next;
            free(freeable);
        }
    }
    free(LADJ);
}


/* 
 *Nome da funcao: GRAPHinit
 *
 * Objetivo da funcao: Alocacao de um grafo com recurso a uma lista de adjacencias e inicializacao das listas como ponteiros para NULL
 * 
 * Argumentos de entrada:
 *          V: numero de vertices
 * 
 * 
 * Argumentos de saida: ponteiro para o grafo
 * 
 */ 

edge **GRAPHinit(int V){
    int v;
    edge **LADJ = (edge**) malloc(V*sizeof(struct edge*));
    if (LADJ==NULL)
    {
        exit(0);
    }
    
    for (v = 0; v < V; v++)
        LADJ[v] = NULL;
    return LADJ;
}


/*
 *Nome da funcao: GRAPHfill
 *
 * Objetivo da funcao: preencher a lista de adjacencias com as arestas
 * 
 * Argumentos de entrada:
 *          *maze: ponteiro para o labirinto
 *          C: numero maximo de colunas do labirinto
 *          L: numero maximo de linhas do labirinto
 *          LADJ: ponteiro para a estrutura de dados que define o grafo
 * 
 * Argumentos de saida: void
 */ 

void GRAPHfill(int *maze,int C,int L,edge** LADJ){
    int c,l;
    int Va,Vb,Vc,Vd;

    for ( c = 1; c <= C; c++)
    {
        for ( l = 1; l <= L; l++)
        {
            if(maze[(l - 1) * C + c - 1]>0){  // esta condicao descarta as paredes com custo associado

                Va = A1(L, C, l - 1, c, maze);//acima
                Vb = A1(L, C, l + 1, c, maze);//abaixo
                Vc = A1(L, C, l, c - 1, maze);//esquerda
                Vd = A1(L, C, l, c + 1, maze);//direita

                if (Va!=Vb && Va<-2 && Vb<-2) // se Va e Vb nao forem iguais e forem ambos menor do que -2, entao estam em salas diferentes
                {
                    Va=abs(Va)-3;
                    Vb=abs(Vb)-3;
                    LADJ[Va]=addNODE(LADJ[Va],maze[(l - 1) * C + c - 1],Vb,c,l);
                    LADJ[Vb]=addNODE(LADJ[Vb],maze[(l - 1) * C + c - 1],Va,c,l);
                }
                if (Vc!=Vd && Vc<-2 && Vd<-2) // condicao semelhante a anterior mas agora numa direcao diferente
                {
                    Vc=abs(Vc)-3;
                    Vd=abs(Vd)-3;
                    LADJ[Vc]=addNODE(LADJ[Vc],maze[(l - 1) * C + c - 1],Vd,c,l);
                    LADJ[Vd]=addNODE(LADJ[Vd],maze[(l - 1) * C + c - 1],Vc,c,l);
                }
            }
        }
    }
}


/*
 *Nome da funcao: addNODE
 *
 * Objetivo da funcao: adiciona/atualiza um nó/aresta à lista de adjacências
 * 
 * 
 * Argumentos de entrada:
 *          *ADJ: ponteiro para a lista referente a um certo vértice do grafo que se quer atualizar    
 *          weight: peso da aresta
 *          no: vertice ao qual a aresta liga
 *          c: coordenada das colunas da aresta, aka parede com custo
 *          l: coordenada das linhas da aresta, aka parede com custo 
 * 
 * Argumentos de saida: ponteiro para a lista
 * 
 */

edge* addNODE(edge* ADJ,int weight,int no,int c,int l){
    edge* newNode=NULL;
    
    edge *aux = ADJ;

    //caso a lista do no nao possua nenhum nó associado
    if (ADJ == NULL)
    {
        newNode=(edge *)malloc(sizeof(edge));
        if (newNode==NULL)
        {
            exit(0);
        }

        newNode->noLigado = no;
        newNode->peso = weight;
        newNode->c = c;
        newNode->l = l;
        newNode->next = NULL;

        ADJ = newNode;
        return ADJ;
    } 
      
    //verifica se a aresta que liga os vertices em questão ja existe e atualiza
    while (aux->next != NULL){
        if (aux->noLigado==no)
        {
            if (aux->peso > weight)
            {
                aux->peso= weight;
                aux->c = c;
                aux->l = l;
            }
            return ADJ;
        }
        aux = aux->next;
    }

    //verifica o ultimo no existente na lista
    if (aux->noLigado==no)
    {
        if (aux->peso > weight)
        {
            aux->peso= weight;
            aux->c = c;
            aux->l = l;
        }
        return ADJ;
    }

    //cria um novo no
    newNode=(edge *)malloc(sizeof(edge));
    if (newNode==NULL)
    {
        exit(0);
    }

    newNode->noLigado = no;
    newNode->peso = weight;
    newNode->c = c;
    newNode->l = l;
    newNode->next = NULL;

    aux->next = newNode;

    return ADJ;   
}
