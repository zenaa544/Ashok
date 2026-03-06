/*
  1. "Passing arrays reduces to a pointer"
When you pass an array to a function in C (and C++), the array name decays to a pointer to its first element.

This means:

For a 1D array:

void func(int arr[]);
// OR
void func(int *arr);
When you call func(arr);, you are passing a pointer to arr[0].

Inside the function, the parameter does NOT "know" the array's original length.

It just sees a pointer (int *), not the full array type.

Example:
c

void func(int *arr) {
    arr[0] = 10; // modifying the original array's first element!
}

int main() {
    int a[5] = {0};
    func(a); // 'a' decays to 'int *'
}
func(a); passes a pointer to the first element of a, so changes affect the original array.
2. "Column value must be passed for 2D static arrays"
A 2D array in C is actually stored as one big block of memory, row by row.

Example:

int arr[3][4];
In memory: arr[0][0], arr[0][1], ... arr[1][0], ... up to arr[2][3]
The compiler needs to know how many columns to calculate where arr[i][j] lives (i.e., to jump by the correct multiple).
Function parameter for 2D arrays requires column size!

void func(int arr[][4]);     // VALID: column size known
// or
void func(int (*arr)[4]);    // function receives pointer to array of 4 ints
If you only say int arr[][], the compiler doesn’t know how to do the math for arr[i][j]! That's why column size MUST be specified.

What happens "under the hood":
For statement: arr[i][j]
Address calculated as: base_address + (i * num_cols + j) * sizeof(int)
So the compiler must know num_cols.
If you want variable columns?
In C99 (with VLAs), you can write

void func(int rows, int cols, int arr[rows][cols]);
But in standard C, you typically do:

void func(int *arr, int rows, int cols); // Use manual indexing: arr[i*cols + j]
Summary Table
Array Declaration	What function "sees"	Can this access arr[i]?	Can this access arr[i][j]?
int arr[10]	int *arr or int arr[]	Yes, valid	N/A
int arr[3][4]	int arr[][4] or int (*arr)[4]	N/A	Yes, needs col#
int arr[3][n] (VLA)	int arr[][n] in C99	N/A	Yes, n must be in scope
In Plain Language:
When you pass func(myArray), you are really passing &myArray[0].
For 2D arrays, unless your function explicitly knows the number of columns, C can't find arr[i][j] locations.
This is why the size of the last dimension(s) must be given in the parameter.
Bonus: Visual

int arr[3][4];

//   arr       arr[0]    arr[0][0]
//  |---| ===> |---| ... |---|
arr is type int (*)[4] (pointer to array of 4 ints)
arr[0] is int *
When passed to a function, it’s a pointer to the first row, but the compiler must know the row length ([4]) to compute &arr[i][j].

*/
//1-Static 2D array
#include <stdio.h>

void printStatic(int arr[][4], int rows) {
    for(int i=0; i<rows; ++i) {
        for(int j=0; j<4; ++j)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

int main() {
    int arr[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9,10,11,12}
    };
    printStatic(arr, 3);
    return 0;
}



//2- Variable Length Array (VLA, C99+)
#include <stdio.h>

void printVLA(int rows, int cols, int arr[rows][cols]) {
    for(int i=0; i<rows; ++i) {
        for(int j=0; j<cols; ++j)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

int main() {
    int rows = 2, cols = 5;
    int arr[rows][cols]; // VLA
    int cnt = 1;
    for(int i=0; i<rows; ++i)
        for(int j=0; j<cols; ++j)
            arr[i][j] = cnt++;

    printVLA(rows, cols, arr);
    return 0;
}


//3-Dynamic 2D Array (int **)
#include <stdio.h>
#include <stdlib.h>

void printDyn2D(int **arr, int rows, int cols) {
    for(int i=0; i<rows; ++i) {
        for(int j=0; j<cols; ++j)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

int main() {
    int rows = 3, cols = 2;
    int **arr = malloc(rows * sizeof(int *));
    for(int i=0; i<rows; ++i)
        arr[i] = malloc(cols * sizeof(int));

    int cnt = 1;
    for(int i=0; i<rows; ++i)
        for(int j=0; j<cols; ++j)
            arr[i][j] = cnt++;

    printDyn2D(arr, rows, cols);

    for(int i=0; i<rows; ++i) free(arr[i]);
    free(arr);
    return 0;
}

//4. Flat 1D Array (manual 2D indexing)
#include <stdio.h>
#include <stdlib.h>

void printFlat(int *arr, int rows, int cols) {
    for(int i=0; i<rows; ++i) {
        for(int j=0; j<cols; ++j)
            printf("%d ", arr[i*cols + j]);
        printf("\n");
    }
}

int main() {
    int rows = 2, cols = 3;
    int *arr = malloc(rows * cols * sizeof(int));
    int cnt = 1;
    for(int i=0; i<rows; ++i)
        for(int j=0; j<cols; ++j)
            arr[i*cols+j] = cnt++;

    printFlat(arr, rows, cols);
    free(arr);
    return 0;
}
