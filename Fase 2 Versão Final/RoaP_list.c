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

data *cria_no(int C, int L)
{
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

data *push(data *head, data *nodulo)
{
    if (head == NULL)
    {
        head = nodulo;
    }
    else
    {
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

data *read_pop(data *head, int *C, int *L)
{
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

void liberta_lista(data *head)
{
    data *aux;

    while (head != NULL) // percorre a lista
    {
        aux = head;
        head = head->next;
        free(aux); // dá free ao nó
    }
}

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

void FixUp(int *acervo, int Idx, int *distancia)
{
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


void FixDown(int *acervo, int Idx, int *distancia,int N)
{

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

edge* addNODE(edge* ADJ,int weight,int no,int c,int l)
{
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


/*
 * Nome da funcao: createStack
 *
 * Objetivo da funcao: criar uma pilha explícita que armazene dados do tipo int
 * 
 * Argumentos de entrada:
 *          capacity: capacidade da stack
 * 
 * Argumentos de saida: 
 *          queue: ponteiro ppara a stack
 */
stack* createStack(unsigned capacity)
{
    stack* queue = (stack*)malloc(sizeof(stack));
    if (queue==NULL)
    {
        exit(0);
    }
    
    queue->capacity = capacity;
    queue->top = -1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    if (queue->array==NULL)
    {
        exit(0);
    }
    return queue;
}
 

/*
 * Nome da funcao: isFullStack
 *
 * Objetivo da funcao: verifica se a stack esta cheia 
 * 
 * Argumentos de entrada:
 *          *stack: ponteiro para uma estrutura do tipo stack
 * 
 * Argumentos de saida: 
 *          1:  stack esta cheia
 *          0: stack nao esta cheia
 */

int isFullStack(stack* stack)
{
    return stack->top == stack->capacity - 1;
}
 
 /*
 * Nome da funcao: isEmptyStack
 *
 * Objetivo da funcao: verifica se a stack esta vazia
 * 
 * Argumentos de entrada:
 *          *stack: ponteiro para uma estrutura do tipo stack
 * 
 * Argumentos de saida: 
 *          1:  stack esta vazia
 *          0: stack nao esta vazia
 */

int isEmptyStack(stack* stack)
{
    return stack->top == -1;
}
 
 /*
 * Nome da funcao: pushStack
 *
 * Objetivo da funcao: insere um novo int no array
 * 
 * Argumentos de entrada:
 *          *stack: ponteiro para uma estrutura do tipo stack
 *          item: valor a colocar no arrayda stack
 * 
 * Argumentos de saida: void
 */

void pushStack(stack* stack, int item)
{
    if (isFullStack(stack))
        return;
    stack->array[++stack->top] = item;
}
 
 /*
 * Nome da funcao: popStack
 *
 * Objetivo da funcao: remove um item da stack
 * 
 * Argumentos de entrada:
 *          *stack: ponteiro para uma estrutura do tipo stack
 * 
 * Argumentos de saida:
 *          ultimo valor a ser introduzido na stack
 */

int popStack(stack* stack)
{
    if (isEmptyStack(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}
 
/*
 *Nome da funcao:peekStack
 *
 * Objetivo da funcao: ver o valor do ultimo valor da stack sem o retirar (self-evident, pelo nome da funcao)
 * 
 * Argumentos de entrada:
 *          *stack: ponteiro para uma estrutura do tipo stack
 * 
 * Argumentos de saida:
 *          stack->array[stack->top]: valor do ultimo elemento da stack
 */ 

int peekStack(stack* stack)
{
    if (isEmptyStack(stack))
        return INT_MIN;
    return stack->array[stack->top];
}

/*
 *Nome da funcao: freeStack
 *
 * Objetivo da funcao: limpar a memoria alocada para a stack 
 * 
 * Argumentos de entrada:
 *          *stack: ponteiro para a stack
 * 
 * Argumentos de saida: void
 * 
 */ 

void freeStack(stack* stack){
    free(stack->array);
    free(stack);
}