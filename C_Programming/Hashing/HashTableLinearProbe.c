/*probing sequentially (i.e., idx+1, idx+2, idx+3, ...)*/

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 7
#define EMPTY_KEY -1

typedef struct {
    int key;
    int value;
} Entry;

typedef struct {
    Entry entries[TABLE_SIZE];
} HashTable;

// Initialize table to empty
void init_table(HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; ++i)
        table->entries[i].key = EMPTY_KEY;
}

// Hash function: Modulo TABLE_SIZE
int hash(int key) {
    return key % TABLE_SIZE;
}

// Linear Probe: Find the slot to insert/search
int probe(HashTable* table, int key) {
    int idx = hash(key);
    int start = idx;
    do {
        if (table->entries[idx].key == EMPTY_KEY || table->entries[idx].key == key)
            return idx;
        idx = (idx + 1) % TABLE_SIZE;
    } while (idx != start);
    return -1; // Table is full
}

// Insert function
void insert(HashTable *table, int key, int value) {
    int idx = probe(table, key);
    if (idx != -1) {
        table->entries[idx].key = key;
        table->entries[idx].value = value;
    } else {
        printf("Table is full, unable to insert key %d\n", key);
    }
}

// Search function
int* search(HashTable *table, int key) {
    int idx = hash(key);
    int start = idx;
    do {
        if (table->entries[idx].key == EMPTY_KEY)
            return NULL; // Not found
        if (table->entries[idx].key == key)
            return &(table->entries[idx].value);
        idx = (idx + 1) % TABLE_SIZE;
    } while (idx != start);
    return NULL; // Not found after full loop
}

// Simple demo
int main() {
    HashTable table;
    init_table(&table);

    insert(&table, 10, 100);
    insert(&table, 17, 170); // 10 and 17 hash to same index
    insert(&table, 24, 240); // So does 24
    insert(&table, 5, 50);

    int *value = search(&table, 24);
    if (value) printf("Found key 24 with value %d\n", *value);
    else printf("Key 24 not found\n");

    // Print table
    printf("Hash table:\n");
    for (int i = 0; i < TABLE_SIZE; ++i)
        printf("Slot %d: key=%d, value=%d\n", i, table.entries[i].key, table.entries[i].value);

    return 0;
}
