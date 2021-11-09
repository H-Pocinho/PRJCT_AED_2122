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




/*funções de manipulação do tipo info*/



/*cria um novo no do tipo info 
* recebe a coordenada das colunas, a coordenada das linhas e o número de colunas existentes no mapa 
*/
info *cria_no_info(int c, int l, int C){

    info *novoNo;

    if ((novoNo = (info *)malloc(sizeof(info))) == NULL)
    { // Aloca espaço para o nó
        exit(0);
    }

    novoNo->casa = (l-1)*C + c-1;
    novoNo->next = NULL;

    return novoNo;
}


info *push_info(info *head, info *nodulo)
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

info *read_pop_info(info *head, int *casa)
{
    info *tmp = head; // guarda a head

    *casa = head->casa; // Leitura do dados do nó

    head = tmp->next; // Colocação da nova head
    free(tmp);        // Remoção da antiga head

    return head;
}

void liberta_info(info *head)
{
    info *aux;

    while (head != NULL) // percorre a lista
    {
        aux = head;
        head = head->next;
        free(aux); // dá free ao nó
    }
}



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

int addToHeap(int vertex,int *acervo,int *distancia,int nV,int ocup){

    if ((ocup + 1) < nV)
    {
        acervo[ocup] = vertex;
        FixUp(acervo, ocup, distancia);
        ocup++;
    }
    return ocup;
}

int removeFromHeap(int* vertex,int *acervo,int *distancia,int nV,int ocup){
    *vertex=acervo[0];
    ocup--;
    

    acervo[0] = acervo[ocup];
    acervo[ocup] = -1;

    FixDown(acervo,0,distancia,ocup);

    return ocup;
}

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

edge **GRAPHinit(int V){
    int v;
    edge **LADJ = (edge**) malloc(V*sizeof(struct edge*));
    for (v = 0; v < V; v++)
        LADJ[v] = NULL;
    return LADJ;
}

void GRAPHfill(int *maze,int C,int L,edge** LADJ){
    int c,l;
    int Va,Vb,Vc,Vd;

    for ( c = 1; c <= C; c++)
    {
        for ( l = 1; l <= L; l++)
        {
            if(maze[(l - 1) * C + c - 1]>0){

                Va = A1(L, C, l - 1, c, maze);
                Vb = A1(L, C, l + 1, c, maze);
                Vc = A1(L, C, l, c - 1, maze);
                Vd = A1(L, C, l, c + 1, maze);

                if (Va!=Vb && Va<-2 && Vb<-2)
                {
                    Va=abs(Va)-3;
                    Vb=abs(Vb)-3;
                    LADJ[Va]=addNODE(LADJ[Va],maze[(l - 1) * C + c - 1],Vb,c,l);
                    LADJ[Vb]=addNODE(LADJ[Vb],maze[(l - 1) * C + c - 1],Va,c,l);
                }
                if (Vc!=Vd && Vc<-2 && Vd<-2)
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

edge* addNODE(edge* ADJ,int weight,int no,int c,int l)
{
    edge* newNode=NULL;
    
    edge *aux = ADJ;

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



data *read_pop_BFS(data *head, int *C, int *L)
{
    data* aux;
    data* aux2=head;

    for ( aux = head ; aux->next->next != NULL; aux=aux->next)
    {
        head=aux;
    }
    
    head->next->c=*C;
    head->next->l=*L;
    head=head->next;
    
    free(head->next);        // Remoção da antiga head

    return aux2;
}