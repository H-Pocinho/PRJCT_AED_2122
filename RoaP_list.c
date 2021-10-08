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

data *cria_no(int C,int L){
    data *novoNo;
    
    if((novoNo = (data*) malloc(sizeof(data)))==NULL){          //Aloca espaço para o nó
        printf("Calloc falhou\n");
        exit(EXIT_FAILURE);
    }

    novoNo->c=C;
    novoNo->l=L;
    novoNo->next=NULL;

    return novoNo;
}


/*
*Nome da funcao: insere_head
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

data *insere_head(data *head,data *nodulo){
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
*Nome da funcao: read_remove_head
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

data *read_remove_head(data *head,int *C,int *L){
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

/*
*Nome da funcao: search
*
*Objetivo da funcao: procura um nó com um certo conteudo numa lista
*
*Argumentos de entrada:
*       *head : ponteiro para a cabeça da lista
*       C : parametro que se quer ter no nó
*       L : parametro que se quer ter no nó
*
*Argumentos de saida:
*       0 : o nó existe
*       1 : o nó não existe
* 
*/


int search(data* head, int C, int L){
    data* current = head;  // Initialize current
    while (current != NULL)
    {
        if (current->c == C && current->l == L )
            return 0;
        current = current->next;
    }
    return 1;
}
