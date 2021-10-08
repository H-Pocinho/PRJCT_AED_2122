#include "RoaP.h"


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


data *read_remove_head(data *head,int *C,int *L){
    data *tmp = head;


    *C=head->c;
    *L=head->l;

    head = tmp->next; 
    free(tmp);

    return head;
}

void liberta_lista(data *head){
    data* aux;

    while (head != NULL)                //percorre a lista
    {
        aux = head;
        head = head->next;
        free(aux);                      //dá free ao nó 
    }
}

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
