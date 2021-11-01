#include "RoaP.h"

#define rebate(c,l,C) ({int retval; retval = (l-1)*C + c-1; retval;})

int main(int argc, char *argv[]){

    if (argc==3 && strcmp("-s",argv[1])==0)
    {
        FASE1(argv[2]);
    }else if(argc==2){
        FASE2(argv[1]);
    }

}


void FASE1(char str[]){

    FILE *fpIN, *fpOUT;

    int C,L,P,i=0,c,l,v,cIMP,lIMP,cF=1,lF=1,aux,flag=0;
    int *labirinto;
    char tipo[3], *filename;
    int namesize=strlen(str);

    if (str[namesize-1]!='1' || str[namesize-2]!='n' || str[namesize-3]!='i' || str[namesize-4]!='.'){       //vê se o ficheiro tem a extensão .in1
        exit(0);
    }

    filename = (char*) malloc(sizeof(char)*(namesize+2));
    if (filename==NULL){
        exit(0);
    }
    for ( i = 0; i < (namesize+2); i++)
    {
        filename[i]='\0';
    }
    
    

    strcpy(filename,str);
    filename[namesize]='1';
    filename[namesize-1]='l';
    filename[namesize-2]='o';
    filename[namesize-3]='s';           //cria o nome do ficheiro de saida


    if ((fpIN= fopen(str, "r"))==NULL){                                     //abre o ficheiro de entrada
        free(filename);
        exit(0);
    }

    if ((fpOUT= fopen(filename, "w"))==NULL){                              //cria o ficheiro de saída
        free(filename);
        fclose(fpIN);
        exit(0);
    }

    do{ 
        lF=1;
        cF=1;
        if (flag==1){
            fseek(fpIN,-sizeof(char),SEEK_CUR);
            flag=0;
        }
        
        if (fscanf(fpIN,"%d %d",&L,&C)!=2)
        {
            free(filename);
            fclose(fpOUT);
            fclose(fpIN);
            exit(0);
        }
        

        if (fscanf(fpIN, "%d %d %s",&lIMP,&cIMP,tipo)!=3)
        {
            fclose(fpOUT);
            fclose(fpIN);
            free(filename);
            exit(0);
        }

        
        
        if(strcmp(tipo,"A6")==0){
            if (fscanf(fpIN, "%d %d",&lF,&cF)!=2)
            {
                fclose(fpOUT);
                fclose(fpIN);
                free(filename);
                exit(0);
            }
        }
        
        if (fscanf(fpIN,"%d",&P)!=1)
        {
            fclose(fpOUT);
            fclose(fpIN);
            free(filename);
            exit(0);
        }

        if (lIMP<1||cIMP<1||lF<1||cF<1||lIMP>L||cIMP>C||lF>L||cF>C)
        {
            fprintf(fpOUT, "%d\n\n", -2);
            for ( i = 0; i < P; i++)
            {
                if (fscanf(fpIN,"%d %d %d",&l,&c,&v)!=3)
                {
                    fclose(fpOUT);
                    fclose(fpIN);
                    free(filename);
                    exit(0);
                } 
            }
            continue;
        }


        labirinto = (int *)malloc((C * L) * sizeof(int)); // aloca o espaço de memória para o labirinto

        if (labirinto==NULL){
            free(filename);
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
        for(i=0;i<P;i++){
            if (fscanf(fpIN,"%d %d %d",&l,&c,&v)!=3)
            {
                free(labirinto);
                fclose(fpOUT);
                fclose(fpIN);
                free(filename);
                exit(0);
            }
            labirinto[(l-1)*C+c-1]=v;
        }
        
        switch (aux=tipo[1]-'0')                  //escolhe o modo de funfar (ou seja funcionar, mas funfar é mais giro de escrever)
        {
        case 1:
            fprintf(fpOUT, "%d\n\n", A1(L,C,lIMP,cIMP,labirinto));
            break;
        
        case 2:
            fprintf(fpOUT, "%d\n\n", A234(L,  C,  lIMP,  cIMP, labirinto, 0));
            break;

        case 3:
            fprintf(fpOUT, "%d\n\n", A234(L,  C,  lIMP,  cIMP, labirinto, 1));
            break;

        case 4:
            fprintf(fpOUT, "%d\n\n", A234(L,  C,  lIMP,  cIMP, labirinto, -1));
            break;

        case 5:
            fprintf(fpOUT, "%d\n\n", A5(L,C,lIMP,cIMP,labirinto));
            break;

        case 6:
            i=A6(L,C,lIMP,cIMP,lF,cF,labirinto);
            if (i==-3){
                free(labirinto);
                fclose(fpOUT);
                fclose(fpIN);
                free(filename);
                exit(0);
            }
            fprintf(fpOUT, "%d\n\n",i);
            break;
        default:
            exit(0);
            break;
        }
        flag=1;
        free(labirinto);
    }while((getc(fpIN)!=EOF));

    fclose(fpOUT);
    fclose(fpIN);
    free(filename);
}

int A1(int L, int C, int lIMP, int cIMP, int *maze){
    if (cIMP-1<0 || lIMP-1<0 || lIMP>L || cIMP>C)
    {
        return -2;
    }else{
        return (maze[(lIMP-1)*C + cIMP-1]);
    }
}

int A234(int L, int C, int l, int c, int *maze,int v){
    int aux=0;

    if (c-1<0 || l-1<0 || l>L || c>C)
    {
        return -2;
    }

    if (v==1){
        aux=A1(L,C,l+1,c,maze);
        if (aux!=0 && aux!=-1 && aux!=-2){
            return 1;
        } 
        aux=A1(L,C,l-1,c,maze);
        if (aux!=0 && aux!=-1 && aux!=-2){
            return 1;
        }
        aux=A1(L,C,l,c+1,maze);
        if (aux!=0 && aux!=-1 && aux!=-2){
            return 1;
        }
        aux=A1(L,C,l,c-1,maze); 
        if (aux!=0 && aux!=-1 && aux!=-2){
            return 1;
        }
    }else{
        if (A1(L,C,l+1,c,maze)==v){
            return 1;
        } if (A1(L,C,l-1,c,maze)==v){
            return 1;
        } if (A1(L,C,l,c+1,maze)==v){
            return 1;
        } if (A1(L,C,l,c-1,maze)==v){
            return 1;
        }
    }
    return 0;
}

int A5(int L, int C, int l, int c, int *maze){
    int aux=A1(L,C,l,c,maze);

    if (aux==-2){
        return -2;
    }else if(( aux==0 || aux==-1 )){
        return -1;
    }else if(( A1(L,C,l+1,c,maze)!=0 && A1(L,C,l,c+1,maze)!=0 )){
        return 0;
    }else if(( A1(L,C,l+1,c,maze)!=0 && A1(L,C,l,c-1,maze)!=0 )){
        return 0;
    }else if(( A1(L,C,l-1,c,maze)!=0 && A1(L,C,l,c+1,maze)!=0 )){
        return 0;
    }else if(( A1(L,C,l-1,c,maze)!=0 && A1(L,C,l,c-1,maze)!=0 )){
        return 0;
    }else{
        return 1;
    }
}

int A6(int L, int C, int linit, int cinit, int lend, int cend, int *maze){
    data *stack=NULL;
    data *insertNode=NULL;
    char *visited;
    int c=cinit,l=linit;
    int i=0;

    if ((i=A1(L,C,linit,cinit,maze))==-2)
    {
        return -2;
    }else if(i!=0)
    {
        return 0;
    }
    
    if ((i=A1(L,C,lend,cend,maze))==-2 )
    {
        return -2;
    }else if(i!=0)
    {
        return 0;
        
    }


    visited = (char *)malloc((C * L) * sizeof(char));
    if (visited==NULL)
    {
        return -3;
    }
    for (i = 0; i < L * C; i++)
    {
        visited[i]='0';
    }
    
    insertNode=cria_no(c,l,0);
    stack=push(stack,insertNode);

    while(stack!=NULL){
        stack=read_pop(stack,&c,&l);

        if (c==cend && l==lend)
        {
            free(visited);
            liberta_lista(stack);
            return 1;
        }
        
        if (visited[(l-1)*C + c-1]=='0')
        {
            visited[(l-1)*C + c-1]='1';
            
            if (A1(L,C,l-1,c,maze)==0)
            {
                insertNode=cria_no(c,l-1,0);
                stack=push(stack,insertNode);
            }
            if (A1(L,C,l+1,c,maze)==0)
            {
                insertNode=cria_no(c,l+1,0);
                stack=push(stack,insertNode);
            }
            if (A1(L,C,l,c-1,maze)==0)
            {
                insertNode=cria_no(c-1,l,0);
                stack=push(stack,insertNode);
            }
            if (A1(L,C,l,c+1,maze)==0)
            {
                insertNode=cria_no(c+1,l,0);
                stack=push(stack,insertNode);
            }
        }
        
    }
    free(visited);
    liberta_lista(stack);
    return 0; 
}

void FASE2(char str[]){

    FILE *fpIN, *fpOUT;

    int C,L,P,i=0,c,l,v,cIMP,lIMP,flag=0,AUX=0;
    int *labirinto;
    char *filename;
    int namesize=strlen(str);

    if (str[namesize-1]!='n' || str[namesize-2]!='i' || str[namesize-3]!='.'){       //vê se o ficheiro tem a extensão .in
        exit(0);
    }

    filename = (char*) malloc(sizeof(char)*(namesize+2));
    if (filename==NULL){
        exit(0);
    }
    for ( i = 0; i < (namesize+2); i++)
    {
        filename[i]='\0';
    }
    
    

    strcpy(filename,str);
    filename[namesize]='l';
    filename[namesize-1]='o';
    filename[namesize-2]='s';


    if ((fpIN= fopen(str, "r"))==NULL){                                     //abre o ficheiro de entrada
        free(filename);
        exit(0);
    }

    if ((fpOUT= fopen(filename, "w"))==NULL){                              //cria o ficheiro de saída
        free(filename);
        fclose(fpIN);
        exit(0);
    }

    free(filename);

    do{ 
        if (flag==1){
            fseek(fpIN,-sizeof(char),SEEK_CUR);
            flag=0;
        }
        
        if (fscanf(fpIN,"%d %d",&L,&C)!=2)
        {
            fclose(fpOUT);
            fclose(fpIN);
            exit(0);
        }
        

        if (fscanf(fpIN, "%d %d",&lIMP,&cIMP)!=2)
        {
            fclose(fpOUT);
            fclose(fpIN);
            exit(0);
        }
        AUX++; //A REMOVER
        
        if (fscanf(fpIN,"%d",&P)!=1)
        {
            fclose(fpOUT);
            fclose(fpIN);
            exit(0);
        }

        if (lIMP<1||cIMP<1||lIMP>L||cIMP>C)
        {
            fprintf(fpOUT, "%d\n\n", -1);
            for ( i = 0; i < P; i++)
            {
                if (fscanf(fpIN,"%d %d %d",&l,&c,&v)!=3)
                {
                    fclose(fpOUT);
                    fclose(fpIN);
                    exit(0);
                } 
            }
            continue;
        }


        labirinto = (int *)malloc((C * L) * sizeof(int)); // aloca o espaço de memória para o labirinto

        if (labirinto==NULL){
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
        for(i=0;i<P;i++){
            if (fscanf(fpIN,"%d %d %d",&l,&c,&v)!=3)
            {
                free(labirinto);
                fclose(fpOUT);
                fclose(fpIN);
                exit(0);
            }
            labirinto[(l-1)*C+c-1]=v;
        }

        if (A1(L,C,lIMP,cIMP,labirinto)!=0)  //dá para fazer esta verificação mais cedo
        {
           fprintf(fpOUT, "%d\n\n", -1);
           free(labirinto);
           continue;
        }
        
        v=magicRoapSolver(L,C,lIMP,cIMP,labirinto,fpOUT);
        if(v==0){
                free(labirinto);
                fclose(fpOUT);
                fclose(fpIN);
                exit(0);
        }

        flag=1;
        free(labirinto);

    }while((getc(fpIN)!=EOF));

    fclose(fpOUT);
    fclose(fpIN);
}

int magicRoapSolver(int L, int C, int lend, int cend, int *maze,FILE* FPOUT){
    unsigned int size = C*L, ocup=0,provDist,prevNode;
    int PresC,PresL,NeighC=0,NeighL=0,NeighState;
    int i,j;


    int VizC[4]={0,0,1,-1};
    int VizL[4]={1,-1,0,0};

    int* dist = (int *)malloc(size * sizeof(int));
    if (dist==NULL){
        return 0;
    }
    
    unsigned int* prev = (unsigned int *)malloc(size * sizeof(int)); //marcar o prev de outra maneira
    if (prev==NULL){
        free(dist);
        return 0;
    }

    char* visited = (char *)malloc(size * sizeof(char));
    if (visited==NULL){
        free(dist);
        free(prev);
        return 0;
    }
    
    Hdata** HEAP = (Hdata **)malloc(size * sizeof(Hdata*)); 
    if (HEAP==NULL){
        free(dist);
        free(prev);
        free(visited);
        return 0;
    }

    for (i = 0; i < size; i++)
    {
        dist[i] = __INT_MAX__;
        prev[i] = 0;
        HEAP[i] = NULL;
        visited[i] = '0';
    }

    dist[0]=0;
    ocup=HInsert(1,1,0,size,ocup,HEAP);

    while (HEAP[0]->dist!=__INT_MAX__){
        ocup=HRemove(&PresC,&PresL,size,ocup,HEAP);

        visited[(PresL-1)*C + PresC-1]='1';

        if (PresC==cend && PresL==lend){
            prevNode=(PresL-1)*C + PresC-1;
            ocup=0;
            i=0;

            do{
                if (maze[prevNode]!=0){
                    i++;
                    ocup=ocup+maze[prevNode];
                }
                prevNode=prev[prevNode];
            } while (prevNode!=0);

            fprintf(FPOUT,"%d\n",ocup);
            if(ocup!=0){
                fprintf(FPOUT,"%d\n",i);
            }
            free(visited);
            free(dist);
            libertem_a_heap(HEAP,size);

            int* cinzento = (int *)malloc(i * sizeof(int));
            if (cinzento==NULL){
                return 0;
            }
            
            prevNode=(PresL-1)*C + PresC-1;
            j=i-1;
            do{
                if (maze[prevNode]!=0){
                    cinzento[j]=prevNode;
                    j--;
                }
                prevNode=prev[prevNode];
            } while (prevNode!=0);

            for ( j = 0; j < i; j++)
            {
                PresL=(cinzento[j]+1)/C+1;
                PresC=(cinzento[j])%C+1;
                fprintf(FPOUT,"%d %d %d\n",PresL,PresC,maze[cinzento[j]]);
            }
            fprintf(FPOUT,"\n");
        

            free(cinzento);   
            free(prev);
            
            
            return 1;
        }

        if (maze[(PresL-1)*C + PresC-1]!=0){
            prevNode=prev[(PresL-1)*C + PresC-1];
                if (maze[prevNode]!=0){
                    continue;
                }
                
                if (prevNode+1==((PresL-1)*C + PresC-1)){  
                    NeighC=PresC+1;
                    NeighL=PresL;
                    //printf("C:%d L:%d DIREITA\n",PresC,PresL);
                }
                else if (prevNode-1==((PresL-1)*C + PresC-1)){ 
                    NeighC=PresC-1;
                    NeighL=PresL;
                    //printf("C:%d L:%d ESQUERDA\n",PresC,PresL);
                }
                else if (prevNode+C==((PresL-1)*C + PresC-1)){ 
                    NeighC=PresC;
                    NeighL=PresL+1;
                    //printf("C:%d L:%d DESCE\n",PresC,PresL);
                }
                else if (prevNode-C==((PresL-1)*C + PresC-1)){ 
                    NeighC=PresC;
                    NeighL=PresL-1;
                    //printf("C:%d L:%d SOBE\n",PresC,PresL);
                }
                
                if(A1(L,C,NeighL,NeighC,maze)==0){
                   if (visited[(NeighL-1)*C + NeighC-1]=='1'){
                        continue;
                    }                    
                }else{
                    continue;
                }
                //printf("C:%d L:%d D:%d PASSA\n",PresC,PresL,dist[(PresL-1)*C + PresC-1]);
            provDist=dist[(PresL-1)*C + PresC-1] + maze[(NeighL-1)*C + NeighC-1];
            
            if (provDist<dist[(NeighL-1)*C + NeighC-1]){
                dist[(NeighL-1)*C + NeighC-1]=provDist;
                prev[(NeighL-1)*C + NeighC-1]=(PresL-1)*C + PresC-1;
                //printf("COLOCADO: C:%d L:%d D:%d\n",NeighC,NeighL,dist[(NeighL-1)*C + NeighC-1]);
                ocup=HInsert(NeighC,NeighL,provDist,size,ocup,HEAP);
            }
            continue;
        }
        

        for ( i = 0; i < 4; i++)
        {
            NeighC=PresC+VizC[i];
            NeighL=PresL+VizL[i];
            NeighState=A1(L,C,NeighL,NeighC,maze);

            if (NeighState==-1 || NeighState==-2){
                continue;
            } 

            if (visited[(NeighL-1)*C + NeighC-1]=='1'){
                continue;
            }
            
            if (NeighState!=0){
                if(NeighC+VizC[i]<=C && NeighC+VizC[i]>=1 && NeighL+VizL[i]<=L && NeighL+VizL[i]>=1){
                    if (maze[(NeighL+VizL[i]-1)*C + NeighC+VizC[i]-1]!=0)
                    {
                        continue;
                    }
                }else{
                    continue;
                }

                if (A5(L,C,NeighL,NeighC,maze)!=1){
                    continue;
                }
            } 

            provDist=dist[(PresL-1)*C + PresC-1] + maze[(NeighL-1)*C + NeighC-1];
            
            if (provDist<dist[(NeighL-1)*C + NeighC-1]){
                dist[(NeighL-1)*C + NeighC-1]=provDist;
                prev[(NeighL-1)*C + NeighC-1]=((PresL-1)*C + PresC-1);
                //printf("COLOCADO: C:%d L:%d D:%d\n",NeighC,NeighL,dist[(NeighL-1)*C + NeighC-1]);
                ocup=HInsert(NeighC,NeighL,provDist,size,ocup,HEAP);
            }
        }  
    }
            
    free(dist);
    free(prev);
    free(visited);
    libertem_a_heap(HEAP,size);
    return -1;
}
