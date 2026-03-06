#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Node {
    char* key;
    int value;
    struct Node* next;
} Node;

typedef struct HashTable {
    Node* buckets[TABLE_SIZE];
} HashTable;

HashTable* create_table() {
    HashTable* table = malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++)
        table->buckets[i] = NULL;
    return table;
}
unsigned int hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % TABLE_SIZE;
}

void insert(HashTable* table, const char* key, int value) {
    unsigned int idx = hash(key);

    Node* curr = table->buckets[idx];
    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            curr->value = value; // Update value if key exists
            return;
        }
        curr = curr->next;
    }

    // If key doesn't exist, create new node at head
    Node* new_node = malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = table->buckets[idx];
    table->buckets[idx] = new_node;
}


int* search(HashTable* table, const char* key) {
    unsigned int idx = hash(key);

    Node* curr = table->buckets[idx];
    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            return &curr->value;
        }
        curr = curr->next;
    }
    return NULL;
}

void delete(HashTable* table, const char* key) {
    unsigned int idx = hash(key);
    Node* curr = table->buckets[idx];
    Node* prev = NULL;

    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            if (prev == NULL)
                table->buckets[idx] = curr->next;
            else
                prev->next = curr->next;
            free(curr->key);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

int main() {
    HashTable* table = create_table();

    insert(table, "apple", 10);
    insert(table, "banana", 30);
    insert(table, "grape", 50);

    int* value = search(table, "banana");
    if (value) printf("Value for banana: %d\n", *value); // should print 30

    delete(table, "banana");

    value = search(table, "banana");
    if (!value) printf("banana not found\n");

    // Freeing not shown for brevity
    return 0;
}
