#include <stdio.h>

void add(int a[10][10], int b[10][10], int r, int c) {
    int i, j;
    printf("Addition Result:\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++)
            printf("%d ", a[i][j] + b[i][j]);
        printf("\n");
    }
}

void multiply(int a[10][10], int b[10][10], int r, int c) {
    int i, j, k, sum;
    int res[10][10];

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            sum = 0;
            for (k = 0; k < c; k++)
                sum += a[i][k] * b[k][j];
            res[i][j] = sum;
        }
    }

    printf("Multiplication Result:\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++)
            printf("%d ", res[i][j]);
        printf("\n");
    }
}

void transpose(int a[10][10], int r, int c) {
    int i, j;
    printf("Transpose:\n");
    for (i = 0; i < c; i++) {
        for (j = 0; j < r; j++)
            printf("%d ", a[j][i]);
        printf("\n");
    }
}

int main() {
    int a[10][10], b[10][10], r, c, i, j;

    printf("Enter rows and columns: ");
    scanf("%d %d", &r, &c);

    printf("Enter Matrix A:\n");
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            scanf("%d", &a[i][j]);

    printf("Enter Matrix B:\n");
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            scanf("%d", &b[i][j]);

    add(a, b, r, c);
    multiply(a, b, r, c);
    transpose(a, r, c);

    return 0;
}
