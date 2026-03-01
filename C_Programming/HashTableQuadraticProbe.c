#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TABLE_SIZE 7
#define EMPTY_KEY -1

typedef struct {
    int key;
    int value;
} Entry;

typedef struct {
    Entry entries[TABLE_SIZE];
} HashTable;

void init_table(HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; ++i)
        table->entries[i].key = EMPTY_KEY;
}

int hash(int key) {
    return key % TABLE_SIZE;
}

// Quadratic probe formula (i is probe number, start from 0)
int quadratic_probe(HashTable* table, int key) {
    int idx = hash(key);
    int i = 0;
    while (i < TABLE_SIZE) {
        int probe_idx = (idx + i * i) % TABLE_SIZE;
        if (table->entries[probe_idx].key == EMPTY_KEY || table->entries[probe_idx].key == key)
            return probe_idx;
        i++;
    }
    return -1; // Table full
}

void insert(HashTable* table, int key, int value) {
    int idx = quadratic_probe(table, key);
    if (idx != -1) {
        table->entries[idx].key = key;
        table->entries[idx].value = value;
    } else {
        printf("Table is full, unable to insert key %d\n", key);
    }
}

int* search(HashTable* table, int key) {
    int idx = hash(key);
    int i = 0;
    while (i < TABLE_SIZE) {
        int probe_idx = (idx + i * i) % TABLE_SIZE;
        if (table->entries[probe_idx].key == EMPTY_KEY)
            return NULL; // not found
        if (table->entries[probe_idx].key == key)
            return &(table->entries[probe_idx].value);
        i++;
    }
    return NULL;
}

int main() {
    HashTable table;
    init_table(&table);

    insert(&table, 10, 100);
    insert(&table, 17, 170);
    insert(&table, 24, 240);
    insert(&table, 31, 310);

    int *value = search(&table, 24);
    printf("Quadratic probe: ");
    if (value) printf("Found key 24 with value %d\n", *value);
    else printf("Key 24 not found\n");

    printf("Hash table (quadratic):\n");
    for (int i = 0; i < TABLE_SIZE; ++i)
        printf("Slot %d: key=%d, value=%d\n", i, table.entries[i].key, table.entries[i].value);

    return 0;
}
