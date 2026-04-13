#include <stdio.h>
//#include <omp.h>
#include  <time.h>

int main() {
    int m = 2, n = 3, p = 2; // Dimensões: A(2x3), B(3x2), C(2x2)
    int a[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int b[3][2] = {{7, 8}, {9, 1}, {2, 3}};
    int c[2][2] = {0}; // Matriz resultante zerada

    // Multiplicação de matrizes
    for (int i = 0; i < m; i++) { // Linhas de A
        for (int j = 0; j < p; j++) { // Colunas de B
            for (int k = 0; k < n; k++) { // Dimensão comum
                printf("a[i:%d][k:%d] * b[k:%d][j:%d] \n",i,k,k,j);
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    // Impressão do resultado
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    return 0;
}
