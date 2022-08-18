#include <iostream>
#include <stdio.h>

// Simple entities to test the stack implementation.
class Vector2 {
public:
  float x, y;
};

class Entity {
public:
  Vector2 position;
  float rotation;
  Vector2 scale;

  Entity() {
    this->position = {0, 0};
    this->rotation = 0;
    this->scale = {1, 1};
  }
  Entity(Vector2 position, float rotation, Vector2 scale) {
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
  }
};

// Stack implementation. Can increase and decrease capacity like std::vector,
// push, and pop elements on the back end. Functions allow you to get any
// element from the stack.
template <class T> class Stack {
private:
  unsigned int capacity;
  unsigned int size;
  T *elements;

public:
  Stack(unsigned int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->elements = new T[capacity];
  }

  ~Stack() { delete[] elements; }

  inline bool empty() const { return size == 0; }

  inline T *pop_back() {
    if (size == 0)
      return nullptr;

    size--;
    return &elements[size];
  }

  inline void push_back(T value) {
    // If we reached the maximum capacity, we double it and reallocate memory,
    // copying all the elements over. This is the principle of vectors.
    if (size == capacity) {
      T *old = elements;
      capacity *= 2;
      elements = new T[capacity];
      for (int i = 0; i < size; ++i) {
        elements[i] = old[i];
      }
      delete[] old;
    }

    elements[size] = value;
    size++;
  }

  inline T *back() {
    if (size == 0) {
      return nullptr;
    }
    return &elements[size - 1];
  }

  inline T *front() {
    if (size == 0) {
      return nullptr;
    }
    return &elements[0];
  }

  inline T *get(unsigned int index) {
    if (index < 0 || index >= size) {
      return nullptr;
    }
    return &elements[index];
  }

  int get_capacity() const { return capacity; }
  int get_size() const { return size; }
};

int main(int argc, char *argv[]) {
  const int size = 40;
  // Allocating on the stack instead of the heap allows for faster access and
  // the Stack object itself will be freed when going out of scope.
  auto stack = new Stack<Entity>(size/2);

  for (int i = 0; i < size; i++) {
    // We allocate entities on the heap as in a real game they'd likely be used
    // in several places.
    const Entity *entity =
        new Entity({10 + float(i), 10 + float(i)}, 5, {10, 10});
    stack->push_back(*entity);
  }

  Entity *entity = stack->front();
  std::cout << "Position: " << entity->position.x << ", " << entity->position.y
            << std::endl;
  std::cout << "Rotation: " << entity->rotation << std::endl;
  std::cout << "Scale: " << entity->scale.x << ", " << entity->scale.y
            << std::endl;

  // We need to free the entities to avoid memory leaks, then the stack.
  while (!stack->empty()) {
    delete stack->pop_back();
  }

  return 0;
}
