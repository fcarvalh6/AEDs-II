#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct
typedef struct tabela_ {
    char* nome;
    char* posicao;
    char* naturalidade;
    char* clube;
    char* idade;
} tabela;

// Find the maximum string length in the array
int getMaxStringLength(tabela* arr, int n) {
    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        int len = strlen(arr[i].nome);
        if (len > maxLen) {
            maxLen = len;
        }
    }
    return maxLen;
}

// Counting sort by character position
void countingSort(tabela* arr, int n, int pos) {
    int count[256] = {0};
    tabela* output = (tabela*)malloc(n * sizeof(tabela));

    // Count occurrences of each character at position `pos`
    for (int i = 0; i < n; i++) {
        char c = pos < strlen(arr[i].nome) ? arr[i].nome[pos] : 0; // 0 for shorter strings
        count[(unsigned char)c]++;
    }

    // Update count array to hold cumulative sums
    for (int i = 1; i < 256; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        char c = pos < strlen(arr[i].nome) ? arr[i].nome[pos] : 0;
        output[--count[(unsigned char)c]] = arr[i];
    }

    // Copy sorted data back to the original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);
}

// Radix Sort
void radixSort(tabela* arr, int n) {
    int maxLen = getMaxStringLength(arr, n);

    // Perform counting sort for each character position from right to left
    for (int pos = maxLen - 1; pos >= 0; pos--) {
        countingSort(arr, n, pos);
    }
}

// Helper function to print the array
void printArray(tabela* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("Nome: %s, Posição: %s, Naturalidade: %s, Clube: %s, Idade: %s\n",
               arr[i].nome, arr[i].posicao, arr[i].naturalidade, arr[i].clube, arr[i].idade);
    }
}

// Main function to demonstrate sorting
int main() {
    tabela arr[] = {
        {"Carlos", "Defensor", "Brasil", "Santos", "25"},
        {"Ana", "Meio-campo", "Brasil", "Palmeiras", "23"},
        {"Bruno", "Atacante", "Argentina", "River Plate", "28"},
        {"Daniel", "Goleiro", "Uruguai", "Nacional", "30"},
        {"Felipe", "Defensor", "Brasil", "Flamengo", "22"}
    };

    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Before sorting:\n");
    printArray(arr, n);

    radixSort(arr, n);

    printf("\nAfter sorting:\n");
    printArray(arr, n);

    return 0;
}