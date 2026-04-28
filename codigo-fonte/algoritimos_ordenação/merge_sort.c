#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "merge_sort.h"

void merge(int *array, int start,int meio ,int end)
{  
    //começa a ordenação
    int i, j, k;
    int n1 = meio - start + 1;
    int n2 = end - meio;
    
    // Vetores temporários
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    
    for (i = 0; i < n1; i++) L[i] = array[start + i];
    for (j = 0; j < n2; j++) R[j] = array[meio + 1 + j];
    
    i = 0; j = 0; k = start;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
    
    return;
}

void merge_sort(int *array, int start, int end)
{
    if(start < end){
        int meio = start + (end - start) / 2;
        merge_sort(array, start, meio);
        merge_sort(array, meio + 1, end);
        merge(array, start, meio, end);
    };
}