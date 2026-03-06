/*Concept
Uses two hash functions.
First hash function determines initial slot.
Second hash function determines the step size for subsequent probes.
Probe sequence:

idx = (hash1(key) + i * hash2(key)) % TABLE_SIZE

where i = 0, 1, 2, ...

This greatly reduces clustering, especially if TABLE_SIZE is prime and hash2 never gives zero.
  */

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

void init_table(HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; ++i)
        table->entries[i].key = EMPTY_KEY;
}

// First hash function (primary)
int hash1(int key) {
    return key % TABLE_SIZE;
}

// Second hash function (must never return zero—use a prime smaller than table size)
int hash2(int key) {
    return 1 + (key % (TABLE_SIZE - 2));
}

// Double hashing probe
int double_hash_probe(HashTable* table, int key) {
    int idx1 = hash1(key);
    int idx2 = hash2(key);
    int i = 0;

    while (i < TABLE_SIZE) {
        int probe_idx = (idx1 + i * idx2) % TABLE_SIZE;
        if (table->entries[probe_idx].key == EMPTY_KEY || table->entries[probe_idx].key == key)
            return probe_idx;
        i++;
    }
    return -1; // Table full
}

void insert(HashTable* table, int key, int value) {
    int idx = double_hash_probe(table, key);
    if (idx != -1) {
        table->entries[idx].key = key;
        table->entries[idx].value = value;
    } else {
        printf("Table is full, unable to insert key %d\n", key);
    }
}

int* search(HashTable* table, int key) {
    int idx1 = hash1(key);
    int idx2 = hash2(key);
    int i = 0;

    while (i < TABLE_SIZE) {
        int probe_idx = (idx1 + i * idx2) % TABLE_SIZE;
        if (table->entries[probe_idx].key == EMPTY_KEY)
            return NULL;
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
    printf("Double hashing: ");
    if (value) printf("Found key 24 with value %d\n", *value);
    else printf("Key 24 not found\n");

    printf("Hash table (double hashing):\n");
    for (int i = 0; i < TABLE_SIZE; ++i)
        printf("Slot %d: key=%d, value=%d\n", i, table.entries[i].key, table.entries[i].value);

    return 0;
}
