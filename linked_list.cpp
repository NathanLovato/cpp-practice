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

template <class T> class LinkedList {
public:
  class Element {
    friend class LinkedList;

  public:
    inline Element(T &value) { value = value; };
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

  void push_back(const T &value) {
    if (!contents) {
      contents = new Contents();
    }
    Element *element = new Element(value);
    element->value = value;
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
  }

  bool remove(const Element *element) {
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
  }

  LinkedList() { contents = new Contents; };
  ~LinkedList(){};

private:
  struct Contents {
    Element *first_element = nullptr;
    Element *last_element = nullptr;
    int size = 0;
  };
  Contents *contents;
};

int main(int argc, char *argv[]) {

  auto list = LinkedList<Entity>();
  auto entity = new Entity();
  list.push_back(*entity);
  list.push_back(*entity);
  list.push_back(*entity);

  auto *element = list.get_first();

  exit(0);
}
