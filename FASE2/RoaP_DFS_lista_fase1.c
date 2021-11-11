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

data *cria_no(int C, int L){
    data *novoNo;

    if ((novoNo = (data *)malloc(sizeof(data))) == NULL)
    { // Aloca espaço para o nó
        exit(0);
    }

    novoNo->c = C;
    novoNo->l = L;
    novoNo->next = NULL;

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

data *push(data *head, data *nodulo){

    if (head == NULL){

        head = nodulo;
    }else{

        nodulo->next = head;
        head = nodulo;
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

data *read_pop(data *head, int *C, int *L){
    data *tmp = head; // guarda a head

    *C = head->c; // Leitura do dados do nó
    *L = head->l;

    head = tmp->next; // Colocação da nova head
    free(tmp);        // Remoção da antiga head

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
    data *aux;

    while (head != NULL) // percorre a lista
    {
        aux = head;
        head = head->next;
        free(aux); // dá free ao nó
    }
}
