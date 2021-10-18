#include "RoaP.h"


int main(int argc, char *argv[]){

    if (argc==3 && strcmp("-s",argv[1])==0)
    {
        FASE1(argv[2]);
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


/*
*/


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
    
    insertNode=cria_no(c,l);
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
                insertNode=cria_no(c,l-1);
                stack=push(stack,insertNode);
            }
            if (A1(L,C,l+1,c,maze)==0)
            {
                insertNode=cria_no(c,l+1);
                stack=push(stack,insertNode);
            }
            if (A1(L,C,l,c-1,maze)==0)
            {
                insertNode=cria_no(c-1,l);
                stack=push(stack,insertNode);
            }
            if (A1(L,C,l,c+1,maze)==0)
            {
                insertNode=cria_no(c+1,l);
                stack=push(stack,insertNode);
            }
        }
        
    }
    free(visited);
    liberta_lista(stack);
    return 0; 
}

