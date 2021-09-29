#include "RoaP.h"

void leFicheiro(char str[]);


int main(int argc, char *argv[]){
leFicheiro(argv[1]);

}


void leFicheiro(char str[]){

    FILE *fpIN;

    int C,L,P,i=0,c,l,v,cO,lO,cF,lF;
    int *labirinto;
    char tipo[3];
    

    if ((fpIN= fopen(str, "r"))==NULL){                                     //abre o ficheiro
        printf("Não foi possivel abrir o ficheiro. Programa terminado\n");
        exit(EXIT_FAILURE);
    } 

    fscanf(fpIN,"%d %d",&L,&C);

    labirinto = (int *)malloc((C * L) * sizeof(int));

    if (labirinto==NULL){
        printf("malloc falhou. programa terminado.\n");
        fclose(fpIN); 
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < L * C; i++)
    {
        labirinto[i] = 0; //Giving value to the pointer and simultaneously printing it.
    }


    fscanf(fpIN, "%d %d %s",&cO,&lO,tipo);
    if(strcmp(tipo,"A6")==0){
        fscanf(fpIN, "%d %d",&cF,&lF);
        labirinto[(lF-1)*C+cF-1]=-3;
    }

    labirinto[(lO-1)*C+cO-1]=-2;
    

    fscanf(fpIN,"%d",&P);

    for(i=0;i<P;i++){
        fscanf(fpIN,"%d %d %d",&l,&c,&v);
        labirinto[(l-1)*C+c-1]=v;
    }


    fclose(fpIN);                                       //fecha o ficheiro

    for (i = 0; i < L * C; i++)
    {
        printf("%d ", labirinto[i]);
        if ((i + 1) % C == 0)
        {
            printf("\n");
        }
    }

}