#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 1000
#define N 10

int randomFnTable[M];

typedef struct {
    int n;
    int (*h)(int);
    int* buckets[N];
} HashTable;

int RandomHashFun(int n) {
    return rand() % n;
}

void HashTable_init(HashTable* ht, int (*h)(int)) {
    int i;
    ht->n = N;
    ht->h = h;
    for (i = 0; i < N; i++) {
        ht->buckets[i] = NULL;
    }
}

void HashTable_insert(HashTable* ht, int x) {
    int index = ht->h(x);
    if (ht->buckets[index] == NULL) {
        ht->buckets[index] = malloc(sizeof(int));
        *(ht->buckets[index]) = x;
    } else {
        int size = sizeof(ht->buckets[index]) / sizeof(int);
        ht->buckets[index] = realloc(ht->buckets[index], (size + 1) * sizeof(int));
        ht->buckets[index][size] = x;
    }
}

int* HashTable_delete(HashTable* ht, int x) {
    int index = ht->h(x);
    int* pos = ht->buckets[index];
    int i, size;
    if (pos != NULL) {
        size = sizeof(pos) / sizeof(int);
        for (i = 0; i < size; i++) {
            if (pos[i] == x) {
                if (size == 1) {
                    free(pos);
                    ht->buckets[index] = NULL;
                } else {
                    pos[i] = pos[size - 1];
                    ht->buckets[index] = realloc(pos, (size - 1) * sizeof(int));
                }
                return pos;
            }
        }
    }
    return NULL;
}

int* HashTable_find(HashTable* ht, int x) {
    int index = ht->h(x);
    int* pos = ht->buckets[index];
    int i, size;
    if (pos != NULL) {
        size = sizeof(pos) / sizeof(int);
        for (i = 0; i < size; i++) {
            if (pos[i] == x) {
                return &pos[i];
            }
        }
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    HashTable ht;
    HashTable_init(&ht, RandomHashFun);

    int x = 123;
    int y = 76;
    HashTable_insert(&ht, y);

    if (HashTable_find(&ht, x) != NULL) {
        printf("Se encontró x: %d\n", x);
    } else {
        printf("Error\n");
    }

    return 0;
}