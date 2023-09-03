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

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <Funcao> <inicio> <fim>\n", argv[0]);
        return 1;
    }

    char *function = argv[1];
    unsigned int start = atoi(argv[2]);
    unsigned int end = atoi(argv[3]);
    int i;
    int operacoes = (end - start + 1);

    struct tms start_cpu, end_cpu;
    clock_t start_time, end_time;
    double elapsed_time, user_time, system_time;

    start_time = clock();
    times(&start_cpu);

    for (i = start; i <= end; i++) {
        if (strcmp(function, "fatorial-recursivo") == 0) {
            fatorial_recursivo(i);
        } else if (strcmp(function, "fatorial-iterativo") == 0) {
            fatorial_iterativo(i);
        } else if (strcmp(function, "fibonacci-recursivo") == 0) {
            fibonacci_recursivo(i);
        } else if (strcmp(function, "fibonacci-iterativo") == 0) {
            fibonacci_iterativo(i);
        } else {
            printf("Função desconhecida: %s\n", function);
            return 1;
        }

        // consumeResources(); // Funcao ficticia para consumir recursos
    }

    end_time = clock();
    times(&end_cpu);

    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    user_time = (double)(end_cpu.tms_utime - start_cpu.tms_utime) / sysconf(_SC_CLK_TCK);
    system_time = (double)(end_cpu.tms_stime - start_cpu.tms_stime) / sysconf(_SC_CLK_TCK);


    printf("Tempo total de relógio: %.4f segundos\n", elapsed_time);
    printf("Tempo médio de relógio por operação: %.9f segundos\n\n", elapsed_time / operacoes);
    printf("Tempo total de usuário: %.4f segundos\n", user_time);
    printf("Tempo total de sistema: %.4f segundos\n", system_time);
    printf("Número de operações: %d\n\n", operacoes);

    return 0;
}
