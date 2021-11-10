#include "RoaP.h"

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
stack* createStack(unsigned capacity){

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

int isFullStack(stack* stack){
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

int isEmptyStack(stack* stack){

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

void pushStack(stack* stack, int item){

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

int popStack(stack* stack){

    if (isEmptyStack(stack))
        return INT_MIN;
    return stack->array[stack->top--];
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