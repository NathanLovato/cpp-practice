#include "stdbool.h"
#include "stdlib.h"

struct Vector {
  void **items;
  unsigned int itemCount; // Current number of items contained in the vector
  unsigned int capacity;  // Maximum number of items the vector can hold before
                          // needing a resize
} typedef Vector;

Vector *VectorCreate(int initialSize);
bool VectorResize(Vector *vector, int newCapacity);
void VectorAppend(Vector *vector, void *newItem);
void VectorRemove(Vector *vector, int index);
void VectorSet(Vector *vector, int index, void *item);
void *VectorGet(Vector *vector, int index);
void VectorFree(Vector *vector);

Vector *VectorCreate() {
  Vector *vector = (Vector *)malloc(sizeof(Vector));
  vector->itemCount = 0;
  vector->capacity = 6;
  return vector;
}

bool VectorResize(Vector *vector, int newCapacity) {
  if (!vector)
    return true;

  bool result = false;
  void **items = realloc(vector->items, sizeof(void *) * newCapacity);
  if (items) {
    vector->items = items;
    vector->capacity = newCapacity;
    result = true;
  }

  return result;
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
}
