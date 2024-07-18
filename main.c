#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ordenacao.h"

void imprimirVetor(int vetor[], size_t tam) {
    printf("Vetor: ");
    for (size_t i = 0; i < tam; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL)); // Inicializa a semente para números aleatórios com o tempo atual

    char nome[MAX_CHAR];
    uint64_t numComp;
    getNome(nome);
    printf("Trabalho de %s\n", nome);
    printf("GRR %u\n", getGRR());

    size_t tamVetor;
    printf("Digite o tamanho do vetor a ser ordenado: ");
    scanf("%lu", &tamVetor);

    int* vetor = (int*)malloc(tamVetor * sizeof(int));
    if (vetor == NULL) {
        printf("Falha fatal. Impossível alocar memoria.");
        return 1;
    }

    for (size_t i = 0; i < tam; i++) {
        vetor[i] = rand() % 100; // Números aleatórios entre 0 e 99
    }

    int verVetor;
    printf("Deseja ver o vetor original? (1 para sim, 0 para não): ");
    scanf("%d", &verVetor);

    if (verVetor) imprimirVetor(vetor, tamVetor);

    printf("\n=== Resultados da Ordenação ===\n");

    printf("\nMerge Sort: ");
    numComp = mergeSort(vetor, tamVetor);
    printf("NumComp: %lu\n", numComp);
    if (verVetor) imprimirVetor(vetor, tamVetor);

    printf("\nQuick Sort: ");
    numComp = quickSort(vetor, tamVetor);
    printf("NumComp: %lu\n", numComp);
    if (verVetor) imprimirVetor(vetor, tamVetor);

    printf("\nHeap Sort: ");
    numComp = heapSort(vetor, tamVetor);
    printf("NumComp: %lu\n", numComp);
    if (verVetor) imprimirVetor(vetor, tamVetor);

    printf("\nMerge Sort Recursivo: ");
    numComp = mergeSortSR(vetor, tamVetor);
    printf("NumComp: %lu\n", numComp);
    if (verVetor) imprimirVetor(vetor, tamVetor);

    printf("\nQuick Sort Recursivo: ");
    numComp = quickSortSR(vetor, tamVetor);
    printf("NumComp: %lu\n", numComp);
    if (verVetor) imprimirVetor(vetor, tamVetor);

    printf("\nHeap Sort Recursivo: ");
    numComp = heapSortSR(vetor, tamVetor);
    printf("NumComp: %lu\n", numComp);
    if (verVetor) imprimirVetor(vetor, tamVetor);

    free(vetor);

    return 0;
}
