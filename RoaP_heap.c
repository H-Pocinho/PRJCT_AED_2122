#include "RoaP.h"

/*
 *Nome da funcao: inHeap
 *
 *Objetivo da funcao: procura um vértice na heap
 *
 *Argumentos de entrada:
 *       *acervo: ponteiro para o acervo
 *       nV: numero de vertices do grafo
 *       vertex : vertice do grafo a ser procurado
 *
 *Argumentos de saida: index do vértice na heap
 *
 */
    
int inHeap(int *acervo,int nV,int vertex){
    int i;

    for (i = 0; i < nV; i++)
    {
        if (acervo[i] == vertex)
        {
            return i;
        }
    }
    return -1;
}


/*
 *Nome da funcao: addToHeap
 *
 *Objetivo da funcao: adicionar um novo vertice ao acervo recebido como parametro
 *
 *Argumentos de entrada:
 *       *acervo: ponteiro para o acervo
 *       nV: numero de vertices do grafo
 *       vertex : 
 *       ocup: ocupacao da heap
 *       *distancia: vetor que guarda o peso de cada vertice
 *
 *Argumentos de saida: ocupacao da heap atualizada com o novo vertice
 *
 */

int addToHeap(int vertex,int *acervo,int *distancia,int nV,int ocup){

    if ((ocup + 1) < nV)
    {
        acervo[ocup] = vertex;
        FixUp(acervo, ocup, distancia);
        ocup++;
    }
    return ocup;
}

/*
 *Nome da funcao: removeFromHeap
 *
 *Objetivo da funcao: remover um vertice do acervo recebido como parametro
 *
 *Argumentos de entrada:
 *       *acervo: ponteiro para o acervo
 *       nV: numero de vertices do grafo
 *       vertex : vertice a remover dp grafo
 *       ocup: ocupacao da heap
 *       *distancia: vetor que guarda o peso de cada vertice
 *
 *Argumentos de saida: ocupacao da heap atualizada com o novo vertice
 *
 */

int removeFromHeap(int* vertex,int *acervo,int *distancia,int nV,int ocup){

    *vertex=acervo[0];
    ocup--;
    

    acervo[0] = acervo[ocup];
    acervo[ocup] = -1;

    FixDown(acervo,0,distancia,ocup);

    return ocup;
}


/*
 *Nome da função: FixUp
 *
 * Objetivo da funcao: atualiza a ordenacao da heap de acordo quando um dos vertices filho é mais prioritario que o seu pai
 * 
 * Argumentos de entrada: 
 *          *acervo: ponteiro para o acervo
 *          Idx: indice do vertice a ser ordenado no acervo
 *          *distancia: vetor que tem a distancia associada a cada vertice do grafo
 * 
 * Argumentos de saida: void
 */

void FixUp(int *acervo, int Idx, int *distancia){
    
    int aux;

    while (Idx > 0 && distancia[acervo[(Idx - 1) / 2]]>distancia[acervo[Idx]]) 
    {
        aux = acervo[Idx];
        acervo[Idx] = acervo[(Idx - 1) / 2];
        acervo[(Idx - 1) / 2] = aux;

        Idx = (Idx - 1) / 2;
    }
}

/*
 *Nome da função: FixDown
 *
 * Objetivo da funcao: atualiza a ordenacao da heap de acordo quando um vertice pai e menos prioritario do que um dos seus filhos
 * 
 * Argumentos de entrada: 
 *          *acervo: ponteiro para o acervo
 *          Idx: indice do vertice a ser ordenado no acervo
 *          *distancia: vetor que guarda a distancia associada a cada vertice do grafo
 *          N: ocupacao da heap
 * 
 * Argumentos de saida: void
 */


void FixDown(int *acervo, int Idx, int *distancia,int N){

    int next;
    int aux;

    while (2 * Idx < N - 1)
    {
        next = 2 * Idx + 1;
        if (next < (N - 1) && (distancia[acervo[next]] > distancia[acervo[next+1]]))
        {
            next++;
        }

        if (distancia[acervo[Idx]] <= distancia[acervo[next]])
        {
            break;
        }

        aux = acervo[Idx];
        acervo[Idx] = acervo[next];
        acervo[next] = aux;

        Idx = next;
    }
}


