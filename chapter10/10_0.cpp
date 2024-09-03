#include <lds.hpp>
#include <lsort.hpp>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

int main(int argc, char **argv) {
  std::vector<int> numbers;
  Stack<int64_t> *S1 = new Stack<int64_t>();
  S1->push(2);
  S1->push(105);
  S1->push(10);
  S1->push(11);
  S1->push(3);
  printf("%ld\n", S1->pop());
  S1->push(4);
  S1->push(2);
  S1->push(64);
  S1->push(47);
  S1->push(1);
  S1->push(4);
  S1->push(100);
  S1->push(1235252059);
  S1->pop();
  S1->pop();
  S1->pop();

  Queue<int64_t> *Q1 = new Queue<int64_t>();
  Q1->enqueue(5);
  Q1->enqueue(9);
  Q1->enqueue(19);
  Q1->enqueue(21);
  Q1->enqueue(14);
  Q1->enqueue(53);
  printf("%ld\n", Q1->dequeue());
  Q1->dequeue();
  Q1->dequeue();
  printf("%ld\n", Q1->dequeue());

  LinkedList<int64_t> *L1 = new LinkedList<int64_t>();
  L1->prepend(10);
  L1->prepend(5);
  L1->prepend(11);
  L1->remove(10);
  L1->print();
  L1->prepend(414);
  L1->prepend(14);
  L1->prepend(1);
  L1->prepend(4);
  L1->print();
  L1->reverse();
  L1->print();
  LinkedListNode<int64_t> *node = L1->search(414);
  printf("%ld\n", node->prev->key);

  size_t m = 10;
  DivisionMethod* hash_method = new DivisionMethod(m);
  HashTable<long, std::string>* T1 = new HashTable<long, std::string>(m);
  HashTableEntry<long, std::string>* e1 = new HashTableEntry<long, std::string>();
  e1->key = 2523;
  e1->value = "hello";
  HashTableEntry<long, std::string>* e2 = new HashTableEntry<long, std::string>();
  e2->key = 141;
  e2->value = "privet";
  T1->insert(*e2);
  HashTableEntry<long, std::string>* found = T1->search(141);
  std::cout << found->value << std::endl;

  return 0;
}
