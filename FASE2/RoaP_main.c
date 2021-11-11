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
 *          exit(0) caso tudo falhe
 * 
 */

int main(int argc, char *argv[]){
    
    if (argc == 3 && strcmp("-s", argv[1]) == 0)
    {
        FASE1(argv[2]);
    }
    else if (argc == 2)
    {
        FASE2(argv[1]);
    }else{
        exit(0);
    }
}
