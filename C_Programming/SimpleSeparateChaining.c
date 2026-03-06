#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define MAX_ELEMENTS 100

typedef struct Entry {
    int key;
    int val;
    struct Entry* next;
} Entry;

typedef struct HashTable {
    unsigned int table_size;
    unsigned int num_elements;
    Entry* Entries[TABLE_SIZE]; // Array of pointers to Entry (chains)
} HashTable;

void initHashTable(HashTable *hashTable) {
    hashTable->num_elements = 0;
    hashTable->table_size = TABLE_SIZE;
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->Entries[i] = NULL;
    }
}

HashTable* createHashTable() {
    HashTable* hashTable = malloc(sizeof(HashTable));
    if (!hashTable) return NULL;
    initHashTable(hashTable);
    return hashTable;
}

unsigned int Hash(int key, unsigned int size) {
    return key % size;
}

Entry* search(int key, HashTable *table) {
    unsigned int index = Hash(key, table->table_size);
    Entry *current = table->Entries[index];
    while (current != NULL) {
        if (current->key == key)
            return current;
        current = current->next;
    }
    return NULL;
}

int addKeyToTable(int key, int value, HashTable *table) {
    if (table->num_elements >= MAX_ELEMENTS) {
        printf("No space in table\n");
        return -1;
    }

    unsigned int index = Hash(key, table->table_size);
    Entry *current = table->Entries[index];
    while (current != NULL) {
        if (current->key == key) {
            current->val = value;
            return 0; // Updated value for existing key
        }
        current = current->next;
    }

    Entry *new_entry = malloc(sizeof(Entry));
    if (!new_entry) return -1;
    new_entry->key = key;
    new_entry->val = value;
    new_entry->next = table->Entries[index];
    table->Entries[index] = new_entry;
    table->num_elements++;

    return 0; // Success
}

int deleteKey(int key, HashTable *table) {
    unsigned int index = Hash(key, table->table_size);
    Entry *current = table->Entries[index];
    Entry *prev = NULL;
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                table->Entries[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            table->num_elements--;
            return 0;
        }
        prev = current;
        current = current->next;
    }
    return -1; // Key not found
}

// Example main for testing
int main() {
    HashTable* ht = createHashTable();

    addKeyToTable(10, 100, ht);
    addKeyToTable(20, 200, ht);
    addKeyToTable(10, 999, ht); // update
    addKeyToTable(21, 211, ht);

    Entry *e = search(21, ht);
    printf("Search 21: %d\n", e ? e->val : -1);

    deleteKey(20, ht);

    // Print all
    for (int i = 0; i < ht->table_size; ++i) {
        printf("Bucket %d: ", i);
        Entry *curr = ht->Entries[i];
        while (curr) {
            printf("(%d->%d) ", curr->key, curr->val);
            curr = curr->next;
        }
        printf("\n");
    }

    // Free all entries (not shown for brevity)
    return 0;
}
