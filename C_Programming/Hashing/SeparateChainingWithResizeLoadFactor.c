#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_TABLE_SIZE 8
#define LOAD_FACTOR_THRESHOLD 0.75

typedef struct Entry {
    int key;
    int value;
    struct Entry* next;
} Entry;

typedef struct HashTable {
    Entry** buckets;         // Array of pointers to Entry (linked list heads)
    unsigned int table_size; // Number of buckets
    unsigned int num_elements; // Total number of key/value entries
} HashTable;

unsigned int hash(int key, unsigned int table_size) {
    // Simple hash mod bucket count; for real use, improve!
    return (unsigned int)key % table_size;
}

HashTable* create_table(unsigned int size) {
    HashTable* table = malloc(sizeof(HashTable));
    if (!table) return NULL;

    table->table_size = size;
    table->num_elements = 0;
    table->buckets = calloc(table->table_size, sizeof(Entry*));
    if (!table->buckets) {
        free(table);
        return NULL;
    }
    return table;
}

void free_table(HashTable* table) {
    for (unsigned int i = 0; i < table->table_size; ++i) {
        Entry* curr = table->buckets[i];
        while (curr) {
            Entry* nxt = curr->next;
            free(curr);
            curr = nxt;
        }
    }
    free(table->buckets);
    free(table);
}

Entry* search(HashTable* table, int key) {
    unsigned int idx = hash(key, table->table_size);
    Entry* curr = table->buckets[idx];
    while (curr) {
        if (curr->key == key)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

int insert_no_resize(HashTable* table, int key, int value) {
    unsigned int idx = hash(key, table->table_size);
    Entry* curr = table->buckets[idx];
    while (curr) {
        if (curr->key == key) {
            curr->value = value;
            return 0; // Updated
        }
        curr = curr->next;
    }
    Entry* e = malloc(sizeof(Entry));
    if (!e) return -1;
    e->key = key;
    e->value = value;
    e->next = table->buckets[idx];
    table->buckets[idx] = e;
    table->num_elements++;
    return 1; // New insert
}

// --- Resizing (rehashing) logic ---

void resize_table(HashTable* table, unsigned int new_size) {
    // Create new table and re-link all entries
    Entry** new_buckets = calloc(new_size, sizeof(Entry*));
    if (!new_buckets) return;
    for (unsigned int i = 0; i < table->table_size; ++i) {
        Entry* curr = table->buckets[i];
        while (curr) {
            Entry* next = curr->next;
            unsigned int new_idx = hash(curr->key, new_size);
            curr->next = new_buckets[new_idx];
            new_buckets[new_idx] = curr;
            curr = next;
        }
    }
    free(table->buckets);
    table->buckets = new_buckets;
    table->table_size = new_size;
    // num_elements stays unchanged
}

int insert(HashTable* table, int key, int value) {
    double lf = (double)table->num_elements / (double)table->table_size;
    if (lf > LOAD_FACTOR_THRESHOLD) {
        resize_table(table, table->table_size * 2);
    }
    return insert_no_resize(table, key, value);
}

int delete(HashTable* table, int key) {
    unsigned int idx = hash(key, table->table_size);
    Entry* curr = table->buckets[idx];
    Entry* prev = NULL;
    while (curr) {
        if (curr->key == key) {
            if (prev == NULL) table->buckets[idx] = curr->next;
            else prev->next = curr->next;
            free(curr);
            table->num_elements--;
            return 1; // deleted
        }
        prev = curr;
        curr = curr->next;
    }
    return 0;
}

void print_table(HashTable* table) {
    printf("HashTable (size %u, %u elements):\n", table->table_size, table->num_elements);
    for (unsigned int i = 0; i < table->table_size; ++i) {
        printf("Bucket %u:", i);
        Entry* curr = table->buckets[i];
        while (curr) {
            printf(" (%d→%d)", curr->key, curr->value);
            curr = curr->next;
        }
        printf("\n");
    }
}

int main() {
    HashTable* ht = create_table(INITIAL_TABLE_SIZE);
    if (!ht) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Insert enough elements to force resize
    for (int i = 0; i < 40; ++i) {
        insert(ht, i, i+100);
    }

    print_table(ht);

    // Search tests
    for (int i = 0; i < 5; ++i) {
        Entry* e = search(ht, i);
        printf("Search %d: %s\n", i, e ? "Found" : "Not found");
    }

    // Delete test
    delete(ht, 3);
    print_table(ht);

    free_table(ht);
    return 0;
}
