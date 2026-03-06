/*
 * Array of pointers vs. double pointer examples in C
 * Demonstrates:
 * 1. Static array of pointers
 * 2. Dynamic 2D array (int **)
 * 3. Assignments and function calls
 * 4. What is and isn't allowed
 * 5. Complete with comments
 */

#include <stdio.h>
#include <stdlib.h>

// ==== Example 1: Function that takes double pointer (int **)
void print_table(int **table, int rows, int cols) {
    printf("print_table (int **table):\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            printf("%d ", table[i][j]);
        printf("\n");
    }
}

// ==== Example 2: Function that takes array of pointers
void print_table_arr_ptr(int *table[], int rows, int cols) {
    printf("print_table_arr_ptr (int *table[]):\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            printf("%d ", table[i][j]);
        printf("\n");
    }
}

int main(void) {

    // ====================================================
    // PART 1: STATIC ARRAY OF POINTERS (on stack)
    // ====================================================
    int col0[] = {1,2,3}, col1[] = {4,5,6}, col2[] = {7,8,9};
    int *ptrs[3]; // Array of 3 int pointers

    ptrs[0] = col0;
    ptrs[1] = col1;
    ptrs[2] = col2; // each points to an array of 3 (could be different!)

    // Allowed:
    print_table(ptrs, 3, 3);        // int *ptrs[3] decays to int ** (OK!)
    print_table_arr_ptr(ptrs, 3, 3);// explicitly as array of pointers (OK!)

    // You can do:
    int **pptr = ptrs;              // pptr now points to ptrs[0]
    pptr[2][1] = 99; // Valid, means *( *(pptr+2) + 1 ) == col2[1]
    printf("After change: col2[1]=%d\n", col2[1]);
    // And: ptrs[2][1] == pptr[2][1] == col2[1];

    // Not allowed:
    // int *pp[3] = pptr; // error: can't assign int** to int*[3]
    // ptrs = pptr; // error: can't assign to array

    // ====================================================
    // PART 2: DYNAMIC 2D ARRAY (classic int ** version)
    // ====================================================
    int rows = 2, cols = 4;
    int **dyn2d = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i)
        dyn2d[i] = malloc(cols * sizeof(int));

    // Fill with sample data
    int cnt = 10;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            dyn2d[i][j] = cnt++;

    print_table(dyn2d, rows, cols);              // works
    print_table_arr_ptr(dyn2d, rows, cols);      // also works

    // You can do:
    int **another_ptr = dyn2d;                   // points to arrays
    another_ptr[0][1] = 99;
    printf("dyn2d[0][1] set to %d\n", dyn2d[0][1]);

    // Not allowed:
    // int *dyn_array[2] = dyn2d; // can't assign int** to int*[2]

    // Free memory
    for (int i = 0; i < rows; ++i)
        free(dyn2d[i]);
    free(dyn2d);

    // ====================================================
    // PART 3: Assignments -- What works, what doesn't?
    // ====================================================
    {
        int *array_of_pointers[2];
        int value1 = 5, value2 = 10;
        array_of_pointers[0] = &value1;
        array_of_pointers[1] = &value2;

        int **double_ptr;
        double_ptr = array_of_pointers; // Ok: points at array_of_pointers[0]
        // equivalent: double_ptr = &array_of_pointers[0];

        printf("double_ptr[1]=%d (should be 10)\n", *double_ptr[1]); // 10

        // Not allowed: array_of_pointers = double_ptr; // error
    }
    // --- LIMIT: Danger ---
    /*
      You CAN pass your static array of pointers to int ** function, and it works.
      DANGER: Only as long as your function only uses table[i][j] where all i and j
      are valid (i < array size, j within pointed-to array size). If the rows point to arrays
      of different sizes, code using table[i][j] must not access outside.
    */
    // --- DANGER Zone ---
    // int *small[1];
    // int x = 1;
    // small[0] = &x;
    // double_ptr = small;
    // double_ptr[2][3] == ??? // undefined, small is only 1 pointer.

    // ====================================================
    // PART 4: "Jagged" array using array of pointers
    // ====================================================
    int *jagged[3];
    jagged[0] = malloc(2 * sizeof(int)); // row 0: 2 columns
    jagged[1] = malloc(4 * sizeof(int)); // row 1: 4 columns
    jagged[2] = malloc(1 * sizeof(int)); // row 2: 1 column

    jagged[0][1] = 111; // row 0, column 1
    jagged[1][3] = 222;
    jagged[2][0] = 333;

    // You must know row sizes yourself to print
    printf("Jagged array:\n");
    printf("row 0: ");
    for (int j = 0; j < 2; j++) printf("%d ", jagged[0][j]); printf("\n");
    printf("row 1: ");
    for (int j = 0; j < 4; j++) printf("%d ", jagged[1][j]); printf("\n");
    printf("row 2: ");
    for (int j = 0; j < 1; j++) printf("%d ", jagged[2][j]); printf("\n");

    for (int i = 0; i < 3; ++i)
        free(jagged[i]);

    // ====================================================
    // PART 5: Array of pointer to string (char *)
    // ====================================================
    const char *fruits[] = { "banana", "orange", "kiwi" };
    printf("fruits[1]=%s\n", fruits[1]); // orange

    // You can pass fruits to:
    void print_str_table(const char *arr[], int n);
    print_str_table(fruits, 3);

    // Or as: void print_str_table2(const char **arr, int n);
    void print_str_table2(const char **arr, int n);
    print_str_table2(fruits, 3);

    return 0;
}

// ------- Print functions for strings -------
void print_str_table(const char *arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("arr[%d] = %s\n", i, arr[i]);
}

void print_str_table2(const char **arr, int n) {
    for (int i = 0; i < n; ++i)
        printf("arr[%d] = %s\n", i, arr[i]);
}



/*
 * =======================
 * Summary of what's allowed:
 *
 * - int *arr[N]   // array of N pointers to int
 * - Can assign int **p = arr;
 * - Can pass arr to functions as int **, int *[], int *const[]
 *
 * NOT allowed:
 * - int *arr[N] = double_ptr;             // can't assign pointer to array
 * - arr = double_ptr;                     // array name not assignable
 *
 * Danger:
 * - Only use table[i][j] where i and j are in bounds!
 *
 * Use cases:
 * - "Jagged" arrays, for arrays-of-strings (char *arr[])
 *
 * Best practice:
 * - In modern code, prefer dynamic allocation for true 2D (int **),
 *   or flat allocation (int *arr = malloc(rows*cols*sizeof(int)), arr[i*cols+j]).
 */
