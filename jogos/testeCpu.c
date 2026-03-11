#include <windows.h>
#include <stdio.h>
#include <math.h>

void benchmark_cpu() {
    long long iteracoes = 10000000; // 10 milhões de cálculos
    double resultado = 0;

    // Início da medição de tempo
    LARGE_INTEGER frequencia, inicio, fim;
    QueryPerformanceFrequency(&frequencia);
    QueryPerformanceCounter(&inicio);

    // O TRABALHO: Um loop pesado para a CPU
    for (long long i = 0; i < iteracoes; i++) {
        resultado += sqrt((double)i);
    }

    // Fim da medição
    QueryPerformanceCounter(&fim);

    double tempo_total = (double)(fim.QuadPart - inicio.QuadPart) / frequencia.QuadPart;
    printf("CPU levou: %f segundos para %lld calculos frequencia %lld.\n", tempo_total, iteracoes,frequencia);
    printf("Resultado final (so para o compilador nao ignorar o loop): %f\n", resultado);
}

int main() {
    printf("Iniciando Benchmark...\n");
    benchmark_cpu();
    return 0;
}