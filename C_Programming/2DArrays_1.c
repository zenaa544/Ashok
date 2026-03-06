/*
 * 2D Array Handling in C: All major methods – ready to compile & study!
 *
 * Demonstrates:
 * 1. Static 2D array (fixed size)
 * 2. Dynamically allocated 2D array using pointer-to-pointer (int **)
 * 3. Flat 1D array used as 2D manually (portable, recommended for C/C++)
 */

#include <stdio.h>
#include <stdlib.h> // for malloc and free

// ----- 1. Static 2D Array (Fixed size) -----
void print_static(int arr[][4], int rows) {
    printf("Static 2D Array:\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < 4; ++j)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

// ----- 2. Dynamic 2D Array using Double Pointer (int **) -----
void print_dyn2d(int **arr, int rows, int cols) {
    printf("Dynamic 2D Array (int **):\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

// ----- 3. Flat 1D Array Used as 2D -----
void print_flat2d(int *arr, int rows, int cols) {
    printf("Flat 1D-as-2D Array:\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            printf("%d ", arr[i * cols + j]);
        printf("\n");
    }
}

// ===== Main driver =====
int main(void) {
    // ----- 1. Static 2D Array -----
    int static_arr[3][4];
    int cnt = 1;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 4; ++j)
            static_arr[i][j] = cnt++;
    print_static(static_arr, 3);
    printf("---\n");

    // ----- 2. Dynamic 2D Array (int **) -----
    int rows = 3, cols = 4;
    int **dyn2d = (int **)malloc(rows * sizeof(int *));
    if (!dyn2d) {
        printf("malloc failed!\n");
        return 1;
    }
    for (int i = 0; i < rows; ++i) {
        dyn2d[i] = (int *)malloc(cols * sizeof(int));
        if (!dyn2d[i]) {
            printf("malloc failed!\n");
            // Free previously allocated rows before exit
            for (int k = 0; k < i; ++k) free(dyn2d[k]);
            free(dyn2d);
            return 1;
        }
    }
    cnt = 101;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            dyn2d[i][j] = cnt++;
    print_dyn2d(dyn2d, rows, cols);
    printf("---\n");

    // Free dynamic 2D array (int **)
    for (int i = 0; i < rows; ++i)
        free(dyn2d[i]);
    free(dyn2d);

    // ----- 3. Flat 1D array used as 2D -----
    int *flat2d = (int *)malloc(rows * cols * sizeof(int));
    if (!flat2d) {
        printf("malloc failed!\n");
        return 1;
    }
    cnt = 201;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            flat2d[i * cols + j] = cnt++;
    print_flat2d(flat2d, rows, cols);
    free(flat2d);

    return 0;
}

/*
Output will be:
Static 2D Array:
1 2 3 4
5 6 7 8
9 10 11 12
---
Dynamic 2D Array (int **):
101 102 103 104
105 106 107 108
109 110 111 112
---
Flat 1D-as-2D Array:
201 202 203 204
205 206 207 208
209 210 211 212
*/
