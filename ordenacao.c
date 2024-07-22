#include "ordenacao.h"
#include <stdlib.h>
#include <string.h>

void getNome(char nome[]) {
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
    numComp += mergeSort(vetor, meio);
    numComp += mergeSort(vetor + meio, tam - meio);

    // Mescla os subvetores ordenados
    merge(vetor, 0, meio - 1, tam - 1, &numComp);

    return numComp; // Retorna o número total de comparações realizadas
}

void trocar (int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


int particionar(int vetor[], int inicio, int fim, uint64_t *numComp) 
{
    int pivo = vetor[fim]; // escolha do último elemento como pivô
    int i = (inicio - 1); // índice do menor elemento

    for (int j = inicio; j <= fim - 1; j++) 
    {
        (*numComp)++; // Incrementa o número de comparações
        if (vetor[j] <= pivo) 
        {
            i++; // incrementa o índice do menor elemento
            trocar(&vetor[i], &vetor[j]); // troca vetor[i] e vetor[j]
        }
    }
    trocar(&vetor[i + 1], &vetor[fim]); // coloca o pivô na posição correta
    return (i + 1); // retorna o índice onde o pivô está agora
}


void quicksort(int vetor[], int inicio, int fim, uint64_t *numComp) 
{
    if (inicio < fim) 
    {
        int pi = particionar(vetor, inicio, fim, numComp);
        quicksort(vetor, inicio, pi - 1, numComp);
        quicksort(vetor, pi + 1, fim, numComp);
    }
}

uint64_t quickSort(int vetor[], size_t tam) 
{
    uint64_t numComp = 0;
    quicksort(vetor, 0, tam - 1, &numComp);
    return numComp;
}

void maxHeapify(int heap[], int tam, int no, uint64_t* numComp) 
{
    int maior = no; //nó atual como o maior
    int esq = 2 * no + 1; //índice do filho esquerdo
    int dir = 2 * no + 2; //índice do filho direito

    //filho esquerdo é maior que o nó atual...
    if (esq < tam && heap[esq] > heap[maior]) maior = esq;

    //filho direito é maior que o nó atual...
    if (dir < tam && heap[dir] > heap[maior]) maior = dir;

    //se o maior não for o nó atual, troca e chama recursivamente no nó afetado
    if (maior != no) {
        trocar(&heap[no], &heap[maior]);
        maxHeapify(heap, tam, maior, numComp);
    }
}

void construirMaxHeap(int v[], int tam, uint64_t* numComp) 
{
    for (int i = tam / 2 - 1; i >= 0; i--) 
    {
        maxHeapify(v, tam, i, numComp);
    }
}

uint64_t heapSort(int vetor[], size_t tam) 
{
    uint64_t numComp = 0;
    construirMaxHeap(vetor, tam, &numComp);
    for (int i = tam - 1; i > 0; i--) 
    {
        trocar(&vetor[0], &vetor[i]);
        numComp++;
        maxHeapify(vetor, i, 0, &numComp);
    }
    return numComp;
}

uint64_t mergeSortSR(int vetor[], size_t tam) 
{
    int* inicio = (int*)malloc(tam * sizeof(int));
        int* fim = (int*)malloc(tam * sizeof(int));
        int topo = -1;
        uint64_t numComp = 0;

        // Empilhar o estado inicial (todo o array)
        inicio[++topo] = 0;
        fim[topo] = tam - 1;

        while (topo >= 0) 
        {
            int i = inicio[topo];
            int f = fim[topo];
            topo--;

            if (i < f) 
            {
                int m = i + (f - i) / 2;

                // Empilhar estados para mesclar após dividir
                inicio[++topo] = i;
                fim[topo] = m;

                inicio[++topo] = m + 1;
                fim[topo] = f;

                // Mesclar os subarrays divididos
                merge(vetor, i, m, f, &numComp);
            }
        }

        free(inicio);
        free(fim);
        return numComp;
}

void quicksort_iterativo(int vetor[], int inicio, int fim, uint64_t *numComp) 
{
    // Cria a pilha
    int* pilha = (int*)malloc((fim - inicio + 1) * sizeof(int));
    int topo = -1;

    // Empilha o estado inicial
    pilha[++topo] = inicio;
    pilha[++topo] = fim;

    while (topo >= 0) 
    {
        // Desempilha o fim e o início
        fim = pilha[topo--];
        inicio = pilha[topo--];

        // Particiona o vetor e obtém o índice do pivô
        int pi = particionar(vetor, inicio, fim, numComp);

        // Se houver elementos à esquerda do pivô, empilha esses índices
        if (pi - 1 > inicio) 
        {
            pilha[++topo] = inicio;
            pilha[++topo] = pi - 1;
        }

        // Se houver elementos à direita do pivô, empilha esses índices
        if (pi + 1 < fim) 
        {
            pilha[++topo] = pi + 1;
            pilha[++topo] = fim;
        }
    }

    // Libera a memória da pilha
    free(pilha);
}

uint64_t quickSortSR(int vetor[], size_t tam) 
{
    uint64_t numComp = 0;
    quicksort_iterativo(vetor, 0, tam - 1, &numComp);
    return numComp;
}

void maxHeapifyIT(int vetor[], int tam, int no, uint64_t *numComp)
{
    while (no < tam)
        {
            int maior = no;
            int esq = 2 * no + 1;
            int dir = 2 * no + 2;

        if (esq < tam && vetor[esq] > vetor[maior]) 
        {
            maior = esq;
            (*numComp)++;
        }

        if (dir < tam && vetor[dir] > vetor[maior]) 
        {
            maior = dir;
            (*numComp)++;
        }

        if (maior != no) 
        {
            trocar(&vetor[no], &vetor[maior]);
            no = maior;
        } 

        else 
        {
            break;
        }
    }
}

uint64_t heapSortSR(int vetor[], size_t tam) 
{
    uint64_t numComp = 0;
    for (int i = tam / 2 - 1; i >= 0; i--)
        maxHeapifyIT(vetor, tam, i, &numComp);

    // Extrai um a um os elementos do heap
    for (int i = tam - 1; i > 0; i--) 
    {
        // Move a raiz atual para o fim
        trocar(&vetor[0], &vetor[i]);
        // Chama max heapify na heap reduzida
        maxHeapifyIT(vetor, i, 0, &numComp);
    }
    return numComp;
}