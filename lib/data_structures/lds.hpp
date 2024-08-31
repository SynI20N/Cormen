#ifdef WIN
#ifdef LDS_EXPORTS
#define DSAPI __declspec(dllexport)
#else
#define DSAPI __declspec(dllimport)
#endif
#else
#ifdef LDS_EXPORTS
#define DSAPI
#else
#define DSAPI
#endif
#endif

#ifdef WIN
#define DSCALL __cdecl
#else
#define DSCALL
#endif

#ifndef _L_DS_H
#define _L_DS_H 1
#include <iostream>
#include <stdexcept>
#include <format>

// TYPES
template <typename T>
class Stack
{
private:
  T *stackArray;
  int capacity;
  int top;

public:
  Stack(int size = 10) : capacity(size), top(-1)
  {
    stackArray = new T[capacity];
  }

  ~Stack()
  {
    delete[] stackArray;
  }

  void push(const T &element)
  {
    if (top >= capacity - 1)
    {
      std::cerr << "Stack overflow\n";
      return;
    }
    stackArray[++top] = element;
  }

  T pop()
  {
    if (is_empty())
    {
      std::cerr << "Stack underflow\n";
      throw std::out_of_range("Stack is empty");
    }
    return stackArray[top--];
  }

  bool is_empty() const
  {
    return top == -1;
  }
};

template <typename T>
class Queue
{
private:
  T *queueArray;
  int capacity;
  int tail;
  int head;

public:
  Queue(int size = 10) : capacity(size), tail(0), head(0)
  {
    queueArray = new T[capacity];
  }

  ~Queue()
  {
    delete[] queueArray;
  }

  void enqueue(const T &element)
  {
    if (head == tail + 1 || tail == head + capacity - 1)
    {
      std::cerr << "Queue overflow\n";
      return;
    }
    queueArray[tail] = element;
    if (tail == capacity - 1)
    {
      tail = 0;
    }
    else
    {
      tail++;
    }
  }

  T dequeue()
  {
    if (head == tail)
    {
      std::cerr << "Queue underflow\n";
      throw std::out_of_range("Queue is empty");
    }
    T element = queueArray[head];
    if (head == capacity - 1)
    {
      head = 0;
    }
    else
    {
      head++;
    }
    return element;
  }
};

template <typename T>
struct LinkedListNode
{
  LinkedListNode *next;
  LinkedListNode *prev;
  T key;
};

template <typename T>
class LinkedList
{
private:
  LinkedListNode<T> *head;

public:
  LinkedList()
  {
    head = new LinkedListNode<T>;
  }

  ~LinkedList()
  {
    delete head;
  }

  LinkedListNode<T>* search(T k)
  {
    LinkedListNode<T> *x = head;
    while (x != NULL && x->key != k)
    {
      x = x->next;
    }
    return x;
  }

  void insert(T k)
  {
    LinkedListNode<T> *n = new LinkedListNode<T>;
    n->next = head;
    n->key = k;
    if (head != NULL)
    {
      head->prev = n;
    }
    head = n;
    n->prev = NULL;
  }

  void remove(LinkedListNode<T> *x)
  {
    if (x->prev != NULL)
    {
      x->prev->next = x->next;
    }
    else
    {
      head = x->next;
    }
    if (x->next != NULL)
    {
      x->next->prev = x->prev;
    }
  }

  void remove(T k)
  {
    LinkedListNode<T> *x = search(k);
    remove(x);
  }

  void print()
  {
    LinkedListNode<T> *x = head;
    while (x != NULL)
    {
      std::cout << std::format("<-{}-", x->key);
      x = x->next;
    }
    std::cout << "\n";
  }

  void reverse()
  {
    if (head == NULL)
    {
      return;
    }
    LinkedListNode<T> *x = head;
    LinkedListNode<T> *n = x->next;
    while (n != NULL)
    {
      LinkedListNode<T> *c = new LinkedListNode<T>;
      c->next = x;
      c->key = n->key;
      remove(n);
      x = c;
      n = n->next;
    }
    head = x;
  }
};

#endif
