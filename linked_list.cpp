#include <iostream>
#include <string>

struct Vector2 {
public:
  float x = 0, y = 0;
};

class Entity {
public:
  Vector2 position = {0, 0};
  float rotation = 0;
  Vector2 scale = {1, 1};

  Entity() {}
  Entity(Vector2 position, float rotation, Vector2 scale) {
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
  }

  std::string as_string() const {
    return "Position: (" + std::to_string(this->position.x) + ", " +
           std::to_string(this->position.y) + "), " +
           "Rotation: " + std::to_string(this->rotation) + ", " + "Scale: (" +
           std::to_string(this->scale.x) + ", " +
           std::to_string(this->scale.y) + ")";
  }
};

// Linked list implementation. Should support values of any type.
// Features: push and pop values. Insert and remove values at any position in
// the list.
//
// Goal: implement a map algorithm based on linked lists.
//
// TODO: iterating over the list with range for. Inserting at arbitrary
// positions.
template <class T> class LinkedList {
public:
  // Represents one element of the linked list.
  class Element {
    friend class LinkedList;

  public:
    inline Element(T &p_value) { value = p_value; };
    inline Element *get_next() { return next; }
    inline Element *get_previous() { return previous; }
    inline T &get_value() { return value; }

  private:
    T value;
    Element *previous = nullptr;
    Element *next = nullptr;
  };

public:
  inline Element *get_first() { return contents->first_element; }
  inline Element *get_last() { return contents->last_element; }
  inline int get_size() { return contents->size; }

  void push_back(T &value) {
    // Question: why is there a linter error here? No matching constructor for
    // initialization of LinkedList<Entity>::Element
    Element *element = new Element(value);
    element->previous = contents->last_element;

    if (contents->last_element) {
      contents->last_element->next = element;
    }

    if (!contents->first_element) {
      contents->first_element = element;
    }

    contents->last_element = element;
    contents->size++;
  }

  void pop_back() {
    if (!contents->last_element) {
      return;
    }

    Element *element = contents->last_element;

    contents->last_element = element->previous;
    delete element;
    contents->size--;

    // Without this, calling clear() on an empty list will result in an error.
    if (contents->size == 0) {
      contents->last_element = nullptr;
      contents->first_element = nullptr;
    }
  }

  void remove(const Element *element) {
    if (element == contents->last_element) {
      contents->last_element = element->previous;
    }
    if (element == contents->first_element) {
      contents->first_element = element->next;
    }
    if (element->next) {
      element->previous->next = element->next;
    }
    if (element->previous) {
      element->next->previous = element->previous;
    }
    delete element;
    contents->size--;

    if (contents->size == 0) {
      contents->last_element = nullptr;
      contents->first_element = nullptr;
    }
  }

  // Clears the list and frees all Element instances.
  void clear() {
    Element *current = contents->first_element;
    Element *previous = contents->first_element;
    while (current) {
      previous = current;
      current = current->next;
      delete previous;
    }
    contents->size = 0;
  }

  bool empty() const { return contents->size == 0; }

  LinkedList(){};
  ~LinkedList() {
    clear();
    delete contents;
  };

private:
  struct Contents {
    Element *first_element = nullptr;
    Element *last_element = nullptr;
    int size = 0;
  };
  Contents *contents = new Contents;
};

int main(int argc, char *argv[]) {

  // We make the list on the stack so it gets freed automatically.
  auto list = LinkedList<Entity *>();
  float numbers[] = {1, 2, 3, 4, 5};

  for (float f : numbers) {
    auto *entity = new Entity();
    entity->position.x = f;
    list.push_back(entity);
  }

  for (LinkedList<Entity *>::Element *element = list.get_first(); element;
       element = element->get_next()) {
    std::cout << element->get_value()->as_string() << '\n';
  }

  // Freeing the entities;
    while (list.get_size() > 0) {
    Entity *entity = list.get_last()->get_value();
    delete entity;
    list.pop_back();
  }

  return 0;
}
