#include "stdbool.h"
#include "stdlib.h"
#include <stdio.h>

typedef struct Vector {
  void **items;
  size_t itemCount; // Current number of items contained in the vector
  size_t capacity;  // Maximum number of items the vector can hold before
                          // needing a resize
} Vector;

Vector *VectorCreate();
void VectorResize(Vector *vector, int newCapacity);
void VectorAppend(Vector *vector, void *newItem);
void VectorRemove(Vector *vector, int index);
void VectorSet(Vector *vector, int index, void *item);
void *VectorGet(Vector *vector, int index);
void VectorFree(Vector *vector);
void VectorPrint(Vector *vector);

Vector *VectorCreate() {
  Vector *vector = (Vector *)malloc(sizeof(Vector));
  vector->itemCount = 0;
  vector->capacity = 6;
  return vector;
}

void VectorResize(Vector *vector, int newCapacity) {
  if (!vector)
    return;

  void *items = realloc(vector->items, sizeof(void *) * newCapacity);
  if (!items) {
    exit(1);
  }

  vector->items = &items;
  vector->capacity = newCapacity;
}

void VectorAppend(Vector *vector, void *newItem) {
  if (!vector)
    return;

  if (vector->itemCount == vector->capacity) {
    VectorResize(vector, vector->capacity * 2);
  }
  vector->itemCount += 1;
  vector->items[vector->itemCount] = newItem;
}

void VectorRemove(Vector *vector, int index) {
  if (!vector)
    return;

  if (index > vector->itemCount || index < 0)
    return;

  vector->items[index] = NULL;
  for (int i = index; i < vector->itemCount - 1; ++i) {
    vector->items[i] = vector->items[i + 1];
    vector->items[i + 1] = NULL;
  }
  vector->itemCount -= 1;
  if (vector->itemCount > 0 && vector->itemCount == vector->capacity / 4) {
    VectorResize(vector, vector->capacity / 2);
  }
}

void VectorSet(Vector *vector, int index, void *item) {
  if (!vector)
    return;

  if (index > vector->itemCount || index < 0)
    return;

  vector->items[index] = item;
};

void *VectorGet(Vector *vector, int index) {
  if (!vector)
    return NULL;
  if (index > vector->itemCount || index < 0)
    return NULL;
  return vector->items[index];
}

void VectorFree(Vector *vector) {
  if (!vector)
    return;
  free(vector->items);
  free(vector);
}

void VectorPrint(Vector *vector) {
  for (int i = 0; i < vector->itemCount; i++) {
    printf("%p\n", vector->items[i]);
  }
}
