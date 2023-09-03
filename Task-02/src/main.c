#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>

#include "iterativo.h"
#include "recursivo.h"

void consumeResources() {
    // Função fictícia para consumir recursos computacionais
    int i, j;
    double result = 0;
    for (i = 0; i < 1000000; i++) {
        for (j = 0; j < 1000; j++) {
            result += i * j;
        }
    }
}

int main(int argc, char *argv[]) 
{
    int input = atoi(argv[1]);

    printf("Fatorial(iterativo) de %d: %lld\n", input, fatorial_iterativo(input));
    printf("Fatorial(recursivo) de %d: %lld\n", input, fatorial_recursivo(input));
    printf("Fibonacci(iterativo) de %d: %lld\n", input, fibonacci_iterativo(input));
    printf("Fibonacci(recursivo) de %d: %lld\n", input, fibonacci_recursivo(input));

    return 0;
}
