#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h>

#include "iterativo.h"
#include "recursivo.h"

int main(int argc, char *argv[]) {
    if (argc != 4) 
    {
        printf("Uso: %s <Funcao> <inicio> <fim>\n", argv[0]);
        return 1;
    }

    clock_t start_time, end_time;
    double elapsed_time;

    char *function = argv[1];
    unsigned int start = atoi(argv[2]);
    unsigned int end = atoi(argv[3]);
    int i;
    int operacoes = (end - start + 1);

    start_time = clock();

    if (strcmp(function, "fatorial-recursivo") == 0) 
    {
        for(i = start; i<= end; i++)
        {
            fatorial_recursivo(i);
            //printf("Factorial(recursivo) de %d eh: %lld\n", i, fatorial_recursivo(i));
        }
    } 
    else if (strcmp(function, "fatorial-iterativo") == 0) 
    {
        for(i = start; i<= end; i++)
        {
            fatorial_iterativo(i);
            //printf("Factorial(iterativo) de %d eh: %lld\n", i, fatorial_iterativo(i));
        }
    }
    else if (strcmp(function, "fibonacci-recursivo") == 0) 
    {    
        for(i = start; i<= end; i++)
        {
            fibonacci_recursivo(i);
            //printf("Fibonacci(recursivo) de %d eh: %lld\n", i, fibonacci_recursivo(i));
        }
    } 
    else if (strcmp(function, "fibonacci-iterativo") == 0) 
    {    
        for(i = start; i<= end; i++)
        {
            fibonacci_iterativo(i);
            //printf("Fibonacci(iterativo) de %d eh: %lld\n", i, fibonacci_iterativo(i));
        }
    } 
    else 
    {
        printf("Função desconhecida: %s\n", function);
        return 1;
    }

    end_time = clock();
    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Tempo total: %.9f\n", elapsed_time);
    printf("Tempo médio: %.9f\n", elapsed_time / operacoes);
    printf("Número de operações: %d\n", operacoes);

    return 0;
}