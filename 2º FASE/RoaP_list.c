#include "RoaP.h"


/*
*Nome da funcao: cria_no
*
*Objetivo da funcao: cria um nó para ser inserido numa lista
*
*Argumentos de entrada: 
*           C : Coluna, informação que o nó vai conter 
*           L : Linha, informação que o nó vai conter 
*
*Argumentos de saida: 
*           novoNo : nó já inicializado mas não ligado
* 
*/

data *cria_no(int C,int L,int dist){
    data *novoNo;
    
    if((novoNo = (data*) malloc(sizeof(data)))==NULL){          //Aloca espaço para o nó
        exit(0);
    }

    novoNo->c=C;
    novoNo->l=L;
    novoNo->dist=dist;
    novoNo->next=NULL;


    return novoNo;
}


/*
*Nome da funcao: push
*
*Objetivo da funcao: insere um nó na cabeça da lista
*
*Argumentos de entrada:
*       *head : ponteiro para a cabeça da lista
*       *nodulo  ponteiro para o nó que se quer inserir
*
*Argumentos de saida:
*       *head: ponteiro para cabeça da lista com o nó já inserido
*/

data *push(data *head,data *nodulo){
    if (head==NULL)
    {
        head = nodulo;
    }else{
        nodulo->next=head;
        head=nodulo;
    }
    return head;
}


/*
*Nome da funcao: read_pop
*
*Objetivo da funcao: Ler e remover o nó da cabeça da lista (POP)
*
*Argumentos de entrada:
*       *head : ponteiro para a cabeça da lista
*       *C :  referencia para a variavel para onde se vai ler o conteudo do nó
*       *L :  referencia para a variavel para onde se vai ler o conteudo do nó
*
*Argumentos de saida:
*       *head: ponteiro para cabeça da lista com o nó já removido
*/

data *read_pop(data *head,int *C,int *L){
    data *tmp = head;                   //guarda a head


    *C=head->c;                         //Leitura do dados do nó
    *L=head->l;

    head = tmp->next;                   //Colocação da nova head
    free(tmp);                          //Remoção da antiga head

    return head;
}


/*
*Nome da funcao: liberta_lista
*
*Objetivo da funcao: tira a lista de memória
*
*Argumentos de entrada:
*       *head : ponteiro para a cabeça da lista
*
*Argumentos de saida:
* 
*/

void liberta_lista(data *head){
    data* aux;

    while (head != NULL)                //percorre a lista
    {
        aux = head;
        head = head->next;
        free(aux);                      //dá free ao nó 
    }
}


int HInsert(int c,int l, int dist, int size, int Idx, Hdata** acervo){
    if ((Idx+1) < size) {
        acervo[Idx] = novaData(c,l,dist);
        FixUp(acervo, Idx);
        Idx++;
    }
    return Idx;
}

int HRemove(int* c,int* l, int size, int Idx, Hdata** acervo){  //podemos eventualmente dar free do noó aqui
    Hdata* aux;
    *c=acervo[0]->c;
    *l=acervo[0]->l;

    aux = acervo[0];
    acervo[0] = acervo[Idx-1];
    acervo[Idx-1] = aux;
    free(acervo[Idx-1]);
    acervo[Idx-1]=NULL;

    FixDown(acervo,0,Idx-1);
    Idx--;
    return Idx;
}


Hdata* novaData(int C,int L, int DIST){
    Hdata* aux = (Hdata *)malloc(sizeof(Hdata));
    if (aux==NULL){
        exit(0);
    }
    aux->c=C;
    aux->l=L;
    aux->dist=DIST;
    return aux;
}

void FixUp(Hdata** acervo, int Idx){
    while (Idx > 0 && (acervo[(Idx-1)/2]->dist > acervo[Idx]->dist)) {
        Hdata* aux;

        aux = acervo[Idx];
        acervo[Idx] = acervo[(Idx-1)/2];
        acervo[(Idx-1)/2] = aux;

        Idx = (Idx-1)/2;
    }
}


void FixDown(Hdata** acervo, int Idx, int N) {

    int next; 
    Hdata* aux;

    while(2*Idx < N-1) { 
        next = 2*Idx+1;
 
        if (next < (N-1) && (acervo[next]->dist > acervo[next+1]->dist)){
            next++;
        } 

        if (acervo[Idx]->dist <= acervo[next]->dist){
            break; 
        } 
        
        aux = acervo[Idx];
        acervo[Idx] = acervo[next];
        acervo[next] = aux;

        Idx = next;
    }
}



void libertem_a_heap(Hdata** acervo,int size){
    int i;
    for (i = 0; i < size; i++)
    {
        if (acervo[i]!=NULL)
        {
        free(acervo[i]); 
        }    
    }    
    free(acervo);
}