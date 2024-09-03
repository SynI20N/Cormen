#ifndef _L_DS_H
#define _L_DS_H 1
#include <format>
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

// TYPES
template <typename T> class Stack {
private:
  T *stackArray;
  int capacity;
  int top;

public:
  Stack(int size = 10) : capacity(size), top(-1) {
    stackArray = new T[capacity];
  }

  ~Stack() { delete[] stackArray; }

  void push(const T &element) {
    if (top >= capacity - 1) {
      std::cerr << "Stack overflow\n";
      return;
    }
    stackArray[++top] = element;
  }

  T pop() {
    if (is_empty()) {
      std::cerr << "Stack underflow\n";
      throw std::out_of_range("Stack is empty");
    }
    return stackArray[top--];
  }

  bool is_empty() const { return top == -1; }
};

template <typename T> class Queue {
private:
  T *queueArray;
  int capacity;
  int tail;
  int head;

public:
  Queue(int size = 10) : capacity(size), tail(0), head(0) {
    queueArray = new T[capacity];
  }

  ~Queue() { delete[] queueArray; }

  void enqueue(const T &element) {
    if (head == tail + 1 || tail == head + capacity - 1) {
      std::cerr << "Queue overflow\n";
      return;
    }
    queueArray[tail] = element;
    if (tail == capacity - 1) {
      tail = 0;
    } else {
      tail++;
    }
  }

  T dequeue() {
    if (head == tail) {
      std::cerr << "Queue underflow\n";
      throw std::out_of_range("Queue is empty");
    }
    T element = queueArray[head];
    if (head == capacity - 1) {
      head = 0;
    } else {
      head++;
    }
    return element;
  }
};

template <typename T> struct LinkedListNode {
  LinkedListNode *next;
  LinkedListNode *prev;
  T key;
};

template <typename T> class LinkedList {
private:
  LinkedListNode<T> *head;

public:
  LinkedList() {}

  ~LinkedList() {
    LinkedListNode<T> *next = head->next;
    LinkedListNode<T> *curr = head;
    while (next != nullptr) {
      delete curr;
      curr = next;
      next = next->next;
    }
  }

  LinkedListNode<T> *search(T k) {
    LinkedListNode<T> *x = head;
    while (x != nullptr && x->key != k) {
      x = x->next;
    }
    return x;
  }

  void prepend(T k) {
    LinkedListNode<T> *n = new LinkedListNode<T>;
    n->next = head;
    n->key = k;
    if (head != nullptr) {
      head->prev = n;
    }
    head = n;
    n->prev = nullptr;
  }

  void remove(LinkedListNode<T> *x) {
    if (x->prev != nullptr) {
      x->prev->next = x->next;
    } else {
      head = x->next;
    }
    if (x->next != nullptr) {
      x->next->prev = x->prev;
    }
  }

  void remove(T k) {
    LinkedListNode<T> *x = search(k);
    remove(x);
  }

  void print() {
    LinkedListNode<T> *x = head;
    while (x != nullptr) {
      std::cout << std::format("<-{}->", x->key);
      x = x->next;
    }
    std::cout << "\n";
  }

  void reverse() {
    if (head == nullptr) {
      return;
    }
    LinkedListNode<T> *x = head;
    LinkedListNode<T> *n = x->next;
    while (n != nullptr) {
      LinkedListNode<T> *c = new LinkedListNode<T>;
      c->next = x;
      c->key = n->key;
      remove(n);
      x->prev = c;
      x = c;
      n = n->next;
    }
    head = x;
  }
};

template <typename K, typename V> struct AugDataEntry {
  K key;
  shared_ptr<V> value;
};

template <typename K> class IKeyHolder {
public:
  virtual K GetKey();
};

template <typename K> class IMoveable {
public:
  virtual void CopyTo(K that);
};

template <typename K> struct BaseLinkedListNode : IKeyHolder, IMoveable {
  shared_ptr<BaseLinkedListNode> next;
  shared_ptr<BaseLinkedListNode> prev;
};

template <typename K, typename V> struct AugmentedLinkedListNode : BaseLinkedListNode<K> {
  AugDataEntry<K, V> entry;

  virtual K GetKey() {
    return entry->key;
  }

  virtual void CopyTo(AugDataEntry<K, V> that) {
    that = entry;
  }
};

template <typename T> struct KeyedLinkedListNode : BaseLinkedListNode<T> {
  T key;

  virtual T GetKey() {
    return key;
  }

  virtual void CopyTo(T that) {
    that = key;
  }
};

template <typename K, typename Node> class BaseLinkedList {
private:
  shared_ptr<Node> head;

public:
  AugmentedLinkedList() {}

  ~AugmentedLinkedList() {
    Node *next = head->get()->next;
    Node *curr = head->get();
    while (next != nullptr) {
      delete curr;
      curr = next;
      next = next->next;
    }
  }

  Node* search(K k) {
    Node *x = head->get();
    while (x != nullptr && x->GetKey() != k) {
      x = x->next;
    }
    return x;
  }

  void prepend(const Node &k) {
    Node *n = new Node;
    n->next = head;
    n->GetKey() = k;
    if (head != nullptr) {
      head->prev = n;
    }
    head = n;
    n->prev = nullptr;
  }

  void remove(Node *x) {
    if (x->prev != nullptr) {
      x->prev->next = x->next;
    } else {
      head = x->next;
    }
    if (x->next != nullptr) {
      x->next->prev = x->prev;
    }
  }

  void remove(K k) {
    Node *x = search(k);
    remove(x);
  }

  void print() {
    Node *x = head;
    while (x != nullptr) {
      std::cout << std::format("<-{}->", x->GetKey());
      x = x->next;
    }
    std::cout << "\n";
  }

  void reverse() {
    if (head == nullptr) {
      return;
    }
    LinkedListNode<T> *x = head;
    LinkedListNode<T> *n = x->next;
    while (n != nullptr) {
      LinkedListNode<T> *c = new LinkedListNode<T>;
      c->next = x;
      c->
      remove(n);
      x->prev = c;
      x = c;
      n = n->next;
    }
    head = x;
  }
};

class IHashFunction {
public:
  virtual int64_t Hash(int64_t key);
};

class DivisionMethod : public IHashFunction {
private:
  uint64_t capacity;

public:
  DivisionMethod(uint64_t m) : capacity(m) {}
  ~DivisionMethod() {}
  virtual int64_t Hash(int64_t key) { return key % capacity; }
};

template <typename K, typename V> class HashTable {
private:
  LinkedList<AugDataEntry<K, V>> *table;
  std::shared_ptr<IHashFunction> hash_func;
  uint64_t capacity;

public:
  HashTable(uint64_t size = 10, std::shared_ptr<IHashFunction> obj = std::make_shared<DivisionMethod>())
      : capacity(size), hash_func{std::move(obj)} {
    table = new LinkedList<HashTableEntry<K, V>>[capacity];
  }

  ~HashTable() {}

  void insert(const HashTableEntry<K, V> &item) {
    table[hash_func.get()->Hash(item.key)].prepend(item);
  }

  HashTableEntry<K, V> *search(K key) {
    return table[hash_func.get()->Hash(key)].search(key);
  }

  void remove(const HashTableEntry<K, V> &item) {
    table[hash_func.get()->Hash(item.key)].remove(item);
  }
};

#endif
