#define EMPTY_KEY -1

typedef struct { int key, value; } Entry;

typedef struct {
    Entry entries[TABLE_SIZE];
} HashTable;

void init_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; ++i)
        table->entries[i].key = EMPTY_KEY;
}

int hash(int key) { return key % TABLE_SIZE; }

int probe(HashTable* table, int key) {
    int idx = hash(key);
    int start = idx;
    do {
        if (table->entries[idx].key == EMPTY_KEY || table->entries[idx].key == key)
            return idx;
        idx = (idx + 1) % TABLE_SIZE;
    } while (idx != start);
    return -1; // Table full
}

void insert(HashTable* table, int key, int value) {
    int idx = probe(table, key);
    if (idx != -1) {
        table->entries[idx].key = key;
        table->entries[idx].value = value;
    }
}
int* search(HashTable* table, int key) {
    int idx = hash(key);
    int start = idx;
    do {
        if (table->entries[idx].key == EMPTY_KEY)
            return NULL; // not found
        if (table->entries[idx].key == key)
            return &table->entries[idx].value;
        idx = (idx + 1) % TABLE_SIZE;
    } while (idx != start);
    return NULL;
}
