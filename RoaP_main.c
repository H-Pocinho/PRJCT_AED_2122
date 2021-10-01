#include "RoaP.h"




int main(int argc, char *argv[]){

    if (argc==3 && strcmp("-s",argv[1])==0)
    {
        FASE1(argv[2]);
    }
    


}


void FASE1(char str[]){

    FILE *fpIN;

    int C,L,P,i=0,c,l,v,cIMP,lIMP,cF,lF,aux;
    int *labirinto;
    char tipo[3];
    

    if ((fpIN= fopen(str, "r"))==NULL){                                     //abre o ficheiro
        printf("Não foi possivel abrir o ficheiro. Programa terminado\n");
        exit(EXIT_FAILURE);
    } 

    do{
        fscanf(fpIN,"%d %d",&L,&C);

        labirinto = (int *)malloc((C * L) * sizeof(int));

        if (labirinto==NULL){
            printf("malloc falhou. programa terminado.\n");
            fclose(fpIN); 
            exit(EXIT_FAILURE);
        }

        for (i = 0; i < L * C; i++)
        {
            labirinto[i] = 0;
        }


        fscanf(fpIN, "%d %d %s",&lIMP,&cIMP,tipo);
        

        if(strcmp(tipo,"A6")==0){
            fscanf(fpIN, "%d %d",&lF,&cF);
            labirinto[(lF-1)*C+cF-1]=-3;
            labirinto[(lIMP-1)*C+cIMP-1]=-2;
        }

        fscanf(fpIN,"%d",&P);

        for(i=0;i<P;i++){
            fscanf(fpIN,"%d %d %d",&l,&c,&v);
            labirinto[(l-1)*C+c-1]=v;
        }

        if (getc(fpIN)==EOF)
        {
            return;
        }
        

        switch (aux=tipo[1]-'0')
        {
        case 1:
            A1(L,C,lIMP,cIMP,labirinto);
            break;
        
        case 2:
            A234(L,  C,  lIMP,  cIMP, labirinto, 0);
            break;

        case 3:
            A234( L,  C,  lIMP,  cIMP,  labirinto, 1);
            break;

        case 4:
            A234( L,  C,  lIMP,  cIMP,  labirinto, -1);
            break;

        case 5:
            A5(L,C,lIMP,cIMP,labirinto);
            break;

        default:
            return;
            break;
        }
    }while((getc(fpIN)!=EOF));



}






void A1(int L, int C, int lIMP, int cIMP, int *maze){
    if (cIMP-1<0 || lIMP-1<0 || lIMP>L || cIMP>C)
    {
        printf("-2\n");
        return;
    }
    printf("%d\n", maze[(lIMP-1)*C + cIMP-1]);
}


void A234(int L, int C, int l, int c, int *maze,int v){
    if (c-1<0 || l-1<0 || l>L || c>C)
    {
        printf("-2\n");
        return;
    }
    if (v==1){
        if ((maze[(l-1)*C + c]!=0) && (maze[(l-1)*C + c]!=-1) && (!(c<0 || l-1<0 || l>L || c+1>C))){
            printf("1\n");
            return;
        }else if ((maze[(l-1)*C + c-2]!=0) && (maze[(l-1)*C + c-2]!=-1) && (!(c-2<0 || l-1<0 || l>L || c-1>C))){
            printf("1\n");
            return;
        }else if ((maze[(l)*C + c-1]!=0) && (maze[(l)*C + c-1]!=-1) && (!(c-1<0 || l<0 || l+1>L || c>C))){
            printf("1\n");
            return;
        }else if ((maze[(l-2)*C + c-1]!=0) && (maze[(l-2)*C + c-1]!=-1) && (!(c-1<0 || l-2<0 || l-1>L || c>C))){
            printf("1\n");
            return;
        }else{        
            printf("0\n");
            return;
        }
    }else{
        if ((maze[(l-1)*C + c]==v) && (!(c<0 || l-1<0 || l>L || c+1>C))){
            printf("1\n");
            return;
        }else if ((maze[(l-1)*C + c-2]==v) && (!(c-2<0 || l-1<0 || l>L || c-1>C))){
            printf("1\n");
            return;
        }else if ((maze[(l)*C + c-1]==v) && (!(c-1<0 || l<0 || l+1>L || c>C))){
            printf("1\n");
            return;
        }else if ((maze[(l-2)*C + c-1]==v) && (!(c-1<0 || l-2<0 || l-1>L || c>C))){
            printf("1\n");
            return;
        }else{        
            printf("0\n");
            return;
        }
    }
}

void A5(int L, int C, int l, int c, int *maze){
    if (c-1<0 || l-1<0 || l>L || c>C){
        printf("-2\n");
        return;
    }else if(( maze[(l-1)*C + c-1]==0 || maze[(l-1)*C + c-1]==-1 )){
        printf("-1\n");
        return;
    }else if(l+1>L && c+1>C){
        printf("0\n");
        return;
    }else if(l+1>L && c-2<0){
        printf("0\n");
        return;
    }else if(l-2<0 && c-2<0){
        printf("0\n");
        return;
    }else if(l-2<0 && c+1>C){
        printf("0\n");
        return;
    }else if(( maze[(l-1)*C + c]!=0 && maze[(l)*C + c-1]!=0 )){
        printf("0\n");
        return;
    }else if(( maze[(l-1)*C + c-2]!=0 && maze[(l)*C + c-1]!=0 )){
        printf("0\n");
        return;
    }else if(( maze[(l-1)*C + c-2]!=0 && maze[(l-2)*C + c-1]!=0 )){
        printf("0\n");
        return;
    }else if(( maze[(l-1)*C + c]!=0 && maze[(l-2)*C + c-1]!=0 )){
        printf("0\n");
        return;
    }else{
        printf("1\n");
        return;
    }

}