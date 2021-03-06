#include "RoaP.h"

/*
 *Nome da funcao: FASE2
 *
 * Objetivo da funcao:  ler o ficheiro de entrada, criar o ficheiro de saida, aplicar restrições relevantes e juntar as funções que garantem o bom funcionamento da fase 2
 * 
 * Argumentos de entrada:
 *          str: nome do ficheiro de entrada
 * 
 */ 

void FASE2(char str[])
{

    FILE *fpIN, *fpOUT;

    edge** LADJ;

    int C, L, P, i = 0, c, l, V, cIMP, lIMP, flag = 0,v;
    int SalaDoTesouro;
    int *labirinto;
    char *filename;
    int namesize = strlen(str);

    if (str[namesize - 1] != 'n' || str[namesize - 2] != 'i' || str[namesize - 3] != '.')
    { // vê se o ficheiro tem a extensão .in
        exit(0);
    }

    /*cria o nome do ficheiro de output*/
    filename = (char *)malloc(sizeof(char) * (namesize + 2));
    if (filename == NULL)
    {
        exit(0);
    }
    for (i = 0; i < (namesize + 2); i++)
    {
        filename[i] = '\0';
    }

    strcpy(filename, str);
    filename[namesize] = 'l';
    filename[namesize - 1] = 'o';
    filename[namesize - 2] = 's';

    if ((fpIN = fopen(str, "r")) == NULL)
    { // abre o ficheiro de entrada
        free(filename);
        exit(0);
    }

    if ((fpOUT = fopen(filename, "w")) == NULL)
    { // cria o ficheiro de saída
        free(filename);
        fclose(fpIN);
        exit(0);
    }

    free(filename);

    do
    {
        //verifica se há um novo labirinto
        if (flag == 1)
        {
            fseek(fpIN, -sizeof(char), SEEK_CUR);
            flag = 0;
        }

        if (fscanf(fpIN, "%d %d", &L, &C) != 2)
        {
            fclose(fpOUT);
            fclose(fpIN);
            exit(0);
        }

        if (fscanf(fpIN, "%d %d", &lIMP, &cIMP) != 2)
        {
            fclose(fpOUT);
            fclose(fpIN);
            exit(0);
        }

        if (fscanf(fpIN, "%d", &P) != 1)
        {
            fclose(fpOUT);
            fclose(fpIN);
            exit(0);
        }

        if (lIMP < 1 || cIMP < 1 || lIMP > L || cIMP > C)
        {
            fprintf(fpOUT, "%d\n\n", -1);
            for (i = 0; i < P; i++)
            {
                if (fscanf(fpIN, "%d %d %d", &l, &c, &v) != 3)
                {
                    fclose(fpOUT);
                    fclose(fpIN);
                    exit(0);
                }
            }
            continue;
        }

        labirinto = (int *)malloc((C * L) * sizeof(int)); // aloca o espaço de memória para o labirinto

        if (labirinto == NULL)
        {
            fclose(fpOUT);
            fclose(fpIN);
            exit(0);
        }

        /*inicializa as "casas" com custo 0*/
        for (i = 0; i < L * C; i++)
        {
            labirinto[i] = 0;
        }

        /*atribui o valor às casas necessárias*/
        for (i = 0; i < P; i++)
        {
            if (fscanf(fpIN, "%d %d %d", &l, &c, &v) != 3)
            {
                free(labirinto);
                fclose(fpOUT);
                fclose(fpIN);
                exit(0);
            }
            labirinto[(l - 1) * C + c - 1] = v;
        }

        //verifica se a casa destino e "valida"
        if (A1(L, C, lIMP, cIMP, labirinto) != 0)
        {
            fprintf(fpOUT, "%d\n\n", -1);
            free(labirinto);
            continue;
        }
        //verifica se a casa de partida e "valida"
        if (A1(L, C, 1, 1, labirinto) != 0)
        {
            fprintf(fpOUT, "%d\n\n", -1);
            free(labirinto);
            continue;
        }
         
        
        V=encontraSalas(L,C,lIMP,cIMP,labirinto,&SalaDoTesouro);
        //casa de partida e casa de destino estao na mesma sala
        if (V==-1)
        {
            fprintf(fpOUT, "%d\n\n", 0);
            free(labirinto);
            continue;
        }
        
        flag = 1;
      

        LADJ=GRAPHinit(V);
        GRAPHfill(labirinto,C,L,LADJ); 

        free(labirinto);   

        if (magicRoapSolver(SalaDoTesouro,V,LADJ,fpOUT)==1)
        {
            fprintf(fpOUT, "%d\n\n", -1);
        }
        
        
        GRAPHfree(LADJ,V);
    


    } while ((getc(fpIN) != EOF));

    fclose(fpOUT);
    fclose(fpIN);
}


/*
 *Nome da funcao: magicRoapSolver
 *
 * Objetivo da funcao: descobrir o custo do caminho mais barato entre a casa de partida e a de destino utilizando uma versão do algoritmo do excelentissimo senhor holandes que não sabemos pronuncionar o nome
 * 
 * Argumentos de entrada:
 *          objetivo: sala onde se encontra a casa de destino
 *          nV: numero de salas
 *          **adj: ponteiro para a estrutura de dados do grafo
 *          *FPOUT: ponteiro para o ficheiro de output
 * 
 * Argumentos de saida:
 *          1: se foi possivel chegar a uma resposta satisfatoria
 *          0: o contrario de 1
 * 
 */ 

int magicRoapSolver(int objectivo,int nV,edge** adj,FILE *FPOUT)
{
    int i,j;
    int ocup=0;
    int Present;
    int PDist;
    edge* aux;

    //aloca o vetor que contém as distâncias mínimas aos vértices
    int* dist = (int *)malloc(nV*sizeof(int));
    if (dist == NULL)
    {
        exit(0);
    }

    //aloca o vetor que contém os vértices que correspondem ao caminho de menor custo
    int* prev = (int *)malloc(nV*sizeof(int));
    if (prev == NULL)
    {
        free(dist);
        exit(0);
    }

    //aloca o acervo
    int* HEAP = (int*)malloc(nV*sizeof(int));
    if (HEAP == NULL)
    {
        free(dist);
        free(prev);
        exit(0);
    }

    //inicializa os valores nos diferentes parametros (em particular dá o valor "infinito" a valor das distâncias a todos os vertices) 
    for(i=0;i<nV;i++){
        prev[i]=-1;
        dist[i]=__INT_MAX__;
        HEAP[i]=-1;
    }

    dist[objectivo]=0;
    ocup=addToHeap(objectivo,HEAP,dist,nV,ocup);//adiciona o vertice que corresponde à sala destino à heap

    while (HEAP[0]!=-1)
    {
        ocup = removeFromHeap(&Present,HEAP,dist,nV,ocup);
        
        if(Present == 0){
            j=Present;
            i=prev[Present];
            ocup=0;
            
            fprintf(FPOUT,"%d\n",dist[Present]);//escreve o custo total do caminho no ficheiro de saida
            //indica quantas paredes foram partidas, caso tenham sido
            while (i!=-1)
            {
                for (aux = adj[j]; aux != NULL; aux = aux->next){
                    if (aux->noLigado==i)
                    {
                        ocup++;
                    }  

                }
                j=i;
                i=prev[i];
            }
            fprintf(FPOUT,"%d\n",ocup);
                        j=Present;
            i=prev[Present];
            //indica que paredes foram partidas e qual o seu custo
            while (i!=-1)
            {
                for (aux = adj[j]; aux != NULL; aux = aux->next){
                    if (aux->noLigado==i)
                    {
                        fprintf(FPOUT,"%d %d %d\n",aux->l,aux->c,aux->peso);
                        break;
                    }
                    
                }
                j=i;
                i=prev[i];
            }
            fprintf(FPOUT,"\n");
            
            free(dist);
            free(prev);
            free(HEAP);           
            return 0;
        }

        /*____Algoritmo de Dijkstra___*/
        for (aux = adj[Present]; aux != NULL; aux = aux->next){
            PDist=dist[Present]+aux->peso;
            if (PDist<dist[aux->noLigado])
            {
                dist[aux->noLigado]=PDist;
                if (prev[aux->noLigado]==-1)
                {
                    ocup=addToHeap(aux->noLigado,HEAP,dist,nV,ocup);
                    prev[aux->noLigado]=Present;
                    continue;
                }
                prev[aux->noLigado]=Present;
                FixUp(HEAP,inHeap(HEAP,ocup,aux->noLigado),dist);  
            }
        }

    
    }

    free(dist);
    free(prev);
    free(HEAP);
    return 1;
    
}


/*
 * Nome da funcao: encontraSalas
 *
 * Objetivo da funcao: identificar quantas salas (espaços delimitados por paredes e/ou pelo limites do labirinto) 
 *                      do labirinto existem e pinta-las
 *                      
 * Argumentos de entrada: 
 *          L: numero total de linhas do labirinto
 *          C: numero total de colunas do labirinto
 *          lend: coordenada da linha da casa destino
 *          cend: coorndenada da coluna da casa destino
 *          *maze: ponteiro para o labirinto
 *          *Sala: ponteiro para int, onde se vai guardar a "cor" (numero identificador) da sala
 * 
 * Argumentos de saida:
 *          count: numero de salas existentes no labirinto
 *          -1: caso haja apenas uma sala
 * 
 */ 


int encontraSalas(int L, int C, int lend, int cend, int *maze,int* Sala)
{
    stack *S = NULL;
    unsigned int i = 0, index=0;
    int count=-3;
    


    S=createStack(C*L);


    for ( i = 0; i < C*L; i++)
    {
            if(maze[i]==0){
                pushStack(S,i);
                while (isEmptyStack(S)!=1)
                {
                    index=popStack(S);

                    maze[index]=count;

                    if (index == (lend-1)*C + cend-1)
                    {
                        if (count==-3) 
                        {
                            freeStack(S);
                            return -1;
                        }
                        *Sala=abs(count)-3;
                    }

                        if (index>C)
                        {
                            if (maze[index-C]==0)
                            {
                                pushStack(S,index-C);
                            }
                        }
                        if (index<L*C-C)
                        {
                            if (maze[index+C]==0)
                            {
                                pushStack(S,index+C);
                            }
                        }
                        if (((index+1)%C) !=0)
                        {
                            if (maze[index+1]==0)
                            {
                                pushStack(S,index+1);
                            }
                        }
                        if (((index)%C) !=0)
                        {
                            if (maze[index-1]==0)
                            {
                                pushStack(S,index-1);
                            }
                        }
                }
                count--;
            }
    }
    freeStack(S);
    count=abs(count)-3;

    return count;
}
