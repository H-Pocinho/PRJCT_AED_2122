#include "RoaP.h"


int main(int argc, char *argv[]){

    if (argc==3 && strcmp("-s",argv[1])==0)
    {
        FASE1(argv[2]);
    }

}


void FASE1(char str[]){

    FILE *fpIN, *fpOUT;

    int C,L,P,i=0,c,l,v,cIMP,lIMP,cF,lF,aux;
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
        if (fscanf(fpIN,"%d %d",&L,&C)!=2)
        {
            free(filename);
            fclose(fpOUT);
            fclose(fpIN);
            exit(0);
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

        if (fscanf(fpIN, "%d %d %s",&lIMP,&cIMP,tipo)!=3)
        {
            free(labirinto);
            fclose(fpOUT);
            fclose(fpIN);
            free(filename);
            exit(0);
        }
        
       
        

        if(strcmp(tipo,"A6")==0){
            if (fscanf(fpIN, "%d %d",&lF,&cF)!=2)
            {
                free(labirinto);
                fclose(fpOUT);
                fclose(fpIN);
                free(filename);
                exit(0);
            }
        }

        if (fscanf(fpIN,"%d",&P)!=1)
        {
            free(labirinto);
            fclose(fpOUT);
            fclose(fpIN);
            free(filename);
            exit(0);
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

        if (getc(fpIN)==EOF)        //ve se chegou ao fim do ficheiro
        {  
            free(labirinto);
            fclose(fpOUT);
            fclose(fpIN);
            free(filename);
            exit(0);
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
            fprintf(fpOUT, "%d\n\n",A6(L,C,lIMP,cIMP,lF,cF,labirinto));
            break;
        default:
            exit(0);
            break;
        }

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
    if (c-1<0 || l-1<0 || l>L || c>C)
    {
        return -2;
    }
    if (v==1){
        if ((maze[(l-1)*C + c]!=0) && (maze[(l-1)*C + c]!=-1) && (!(c<0 || l-1<0 || l>L || c+1>C))){
            return 1;
        }else if ((maze[(l-1)*C + c-2]!=0) && (maze[(l-1)*C + c-2]!=-1) && (!(c-2<0 || l-1<0 || l>L || c-1>C))){
            return 1;
        }else if ((maze[(l)*C + c-1]!=0) && (maze[(l)*C + c-1]!=-1) && (!(c-1<0 || l<0 || l+1>L || c>C))){
            return 1;
        }else if ((maze[(l-2)*C + c-1]!=0) && (maze[(l-2)*C + c-1]!=-1) && (!(c-1<0 || l-2<0 || l-1>L || c>C))){
            return 1;
        }else{        
            return 0;
        }
    }else{
        if ((maze[(l-1)*C + c]==v) && (!(c<0 || l-1<0 || l>L || c+1>C))){
            return 1;
        }else if ((maze[(l-1)*C + c-2]==v) && (!(c-2<0 || l-1<0 || l>L || c-1>C))){
            return 1;
        }else if ((maze[(l)*C + c-1]==v) && (!(c-1<0 || l<0 || l+1>L || c>C))){
            return 1;
        }else if ((maze[(l-2)*C + c-1]==v) && (!(c-1<0 || l-2<0 || l-1>L || c>C))){
            return 1;
        }else{        
            return 0;
        }
    }
}

int A5(int L, int C, int l, int c, int *maze){
    if (c-1<0 || l-1<0 || l>L || c>C){
        return -2;
    }else if(( maze[(l-1)*C + c-1]==0 || maze[(l-1)*C + c-1]==-1 )){
        return -1;
    }else if(l+1>L && c+1>C){
        return 0;
    }else if(l+1>L && c-2<0){
        return 0;
    }else if(l-2<0 && c-2<0){
        return 0;
    }else if(l-2<0 && c+1>C){
        return 0;
    }else if(( maze[(l-1)*C + c]!=0 && maze[(l)*C + c-1]!=0 )){
        return 0;
    }else if(( maze[(l-1)*C + c-2]!=0 && maze[(l)*C + c-1]!=0 )){
        return 0;
    }else if(( maze[(l-1)*C + c-2]!=0 && maze[(l-2)*C + c-1]!=0 )){
        return 0;
    }else if(( maze[(l-1)*C + c]!=0 && maze[(l-2)*C + c-1]!=0 )){
        return 0;
    }else{
        return 1;
    }
}

int A6(int L, int C, int linit, int cinit, int lend, int cend, int *maze){
    data *headToSearch=NULL;
    data *headSearched=NULL;
    data *insertNode=NULL;
    int c=cinit,l=linit,lAUX=0,cAUX=0;
    int flag=0;

    if (cinit-1<0 || linit-1<0 || linit>L || cinit>C || cend-1<0 || lend-1<0 || lend>L || cend>C){
        return -2;
    }

    if (maze[(linit-1)*C + cinit-1]!=0||maze[(lend-1)*C + cend-1]!=0)
    {
        return 0;
    }
    

    while(c!=cend || l!=lend){
        if(search(headSearched,c,l)){
            if (c+1<=C){
                if (maze[(l-1)*C + c]==0)
                {
                    if (flag==0)
                    {
                        lAUX=l;
                        cAUX=c+1;
                        flag=1;
                    }else{
                        insertNode=cria_no(c+1,l);
                        headToSearch=insere_head(headToSearch,insertNode);
                    }
                }
                

            } if (c>=2){
                if (maze[(l-1)*C + c-2]==0)
                {
                    if (flag==0)
                    {
                        lAUX=l;
                        cAUX=c-1;
                        flag=1;
                    }else{
                        insertNode=cria_no(c-1,l);
                        headToSearch=insere_head(headToSearch,insertNode);
                    }
                }
            } if (l+1<=L){
                if (maze[(l)*C + c-1]==0)
                {
                    if (flag==0)
                    {
                        lAUX=l+1;
                        cAUX=c;
                        flag=1;
                    }else{
                        insertNode=cria_no(c,l+1);
                        headToSearch=insere_head(headToSearch,insertNode);
                    }  
                }
            } if (l>=2){
                if (maze[(l-2)*C + c-1]==0)
                {
                    if (flag==0)
                    {
                        lAUX=l-1;
                        cAUX=c;
                        flag=1;
                    }else{
                        insertNode=cria_no(c,l-1);
                        headToSearch=insere_head(headToSearch,insertNode);
                    }
                }
            }
        }

        insertNode=cria_no(c,l);
        headSearched=insere_head(headSearched,insertNode);

        if (flag==1)
        {
            l=lAUX;
            c=cAUX;
            flag=0;
        }else{
            if (headToSearch==NULL)
            {
                liberta_lista(headSearched);
                return 0;
            }
            headToSearch=read_remove_head(headToSearch,&c,&l);
        }
    }
    liberta_lista(headToSearch);
    liberta_lista(headSearched);
    return 1; 
}

