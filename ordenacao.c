#include "ordenacao.h"

#include <string.h>

void getNome(char nome[]) 
{
    // substitua por seu nome
    strncpy(nome, "Marcello Eduardo Pereira", MAX_CHAR);
    // adicionada terminação manual para caso de overflow
    nome[MAX_CHAR - 1] = '\0';
}

// a função a seguir deve retornar o seu número de GRR
uint32_t getGRR() { return 20244350; }

static void merge(int vetor[], int inicio, int meio, int fim, uint64_t *comparacoes) 
{
    int tam_esq = meio - inicio + 1; // Calcula o tamanho do subvetor esquerdo
    int tam_dir = fim - meio; // Calcula o tamanho do subvetor direito

    // Aloca memória para os subvetores esquerdo e direito
    int *esq = malloc(tam_esq * sizeof(int));
    int *dir = malloc(tam_dir * sizeof(int));

    // Verifica se a alocação de memória foi bem-sucedida
    if (esq == NULL || dir == NULL) {
        if (esq != NULL)
            free(esq);
        if (dir != NULL)
            free(dir);
        return;
    }

    // Copia os elementos para os subvetores esquerdo e direito
    for (int i = 0; i < tam_esq; i++)
        esq[i] = vetor[inicio + i];
    for (int j = 0; j < tam_dir; j++)
        dir[j] = vetor[meio + 1 + j];

    int i = 0;
    int j = 0;
    int k = inicio;

    // Mescla os subvetores ordenados
    while (i < tam_esq && j < tam_dir) {
        (*comparacoes)++;
        if (esq[i] <= dir[j]) {
            vetor[k] = esq[i];
            i++;
        } else {
            vetor[k] = dir[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes do subvetor esquerdo, se houver
    while (i < tam_esq) {
        vetor[k] = esq[i];
        i++;
        k++;
    }

    // Copia os elementos restantes do subvetor direito, se houver
    while (j < tam_dir) {
        vetor[k] = dir[j];
        j++;
        k++;
    }

    // Libera a memória alocada para os subvetores esquerdo e direito
    free(esq);
    free(dir);
}

uint64_t mergeSort(int vetor[], size_t tam) 
{
    if (tam <= 1) return 0;

    uint64_t numComp = 0;

    size_t meio = tam / 2;

    // Chamadas recursivas para ordenar os subvetores esquerdo e direito
    numComp += mergeSortRec(vetor, meio);
    numComp += mergeSortRec(vetor + meio, tam - meio);

    // Mescla os subvetores ordenados
    merge(vetor, 0, meio - 1, tam - 1, &numComp);

    return numComp; // Retorna o número total de comparações realizadas
}

int trocar (int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(int vetor[], int inicio, int fim) 
{
    int pivo = vetor[fim]; // escolha do último elemento como pivô
    int i = (inicio - 1); // índice do menor elemento

    for (int j = inicio; j <= fim - 1; j++) {
        // Se o elemento atual for menor ou igual ao pivô
        if (vetor[j] <= pivo) {
            i++; // incrementa o índice do menor elemento
            trocar(&vetor[i], &vetor[j]); // troca vetor[i] e vetor[j]
        }
    }
    trocar(&vetor[i + 1], &vetor[fim]); // coloca o pivô na posição correta
    return (i + 1); // retorna o índice onde o pivô está agora
}

uint64_t quickSort(int vetor[], size_t tam) 
{
    static uint64_t numComp = 0;
}

void maxHeapify(int vetor[], int tam, int i) 
{
    int maior = i; //nó atual como o maior
    int esq = 2 * i + 1; //índice do filho esquerdo
    int dir = 2 * i + 2; //índice do filho direito

    //filho esquerdo é maior que o nó atual...
    if (esq < tam && vetor[esq] > vetor[maior]) maior = esq;

    //filho direito é maior que o nó atual...
    if (dir < tam && vetor[dir] > vetor[maior]) maior = dir;

    //se o maior não for o nó atual, troca e chama recursivamente no nó afetado
    if (maior != i) {
        trocar(&vetor[i], &vetor[maior]);
        maxHeapify(vetor, tam, maior);
    }
}

uint64_t heapSort(int vetor[], size_t tam) {
    vetor[0] = 99;
    return -1;
}

uint64_t mergeSortSR(int vetor[], size_t tam) {
    vetor[0] = 99;
    return -1;
}

uint64_t quickSortSR(int vetor[], size_t tam) {
    vetor[0] = 99;
    return -1;
}

uint64_t heapSortSR(int vetor[], size_t tam) {
    vetor[0] = 99;
    return -1;
}