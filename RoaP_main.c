#include "RoaP.h"

/*
 *Nome da funcao: main
 *
 * Objetivo da funcao: fazer o que é pedido no enunciado do projecto
 * 
 * Argumentos de entrada:
 *          argc: numero de parametros passados
 *          *argv[]: ponteiro para vectores onde se encotram os parametros
 * 
 * Argumentos de saida: 
 *          1 : programa executado sem problemas 
 * 
 */

int main(int argc, char *argv[]){
    
    if (argc == 3 && strcmp("-s", argv[1]) == 0)
    {
        FASE1(argv[2]);
        return 1;
    }
    else if (argc == 2)
    {
        FASE2(argv[1]);
        return 1;
    }else{
        exit(0);
    }
}
