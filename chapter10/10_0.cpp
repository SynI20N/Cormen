#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <lsort.hpp>
#include <lds.hpp>
#include <vector>

int main(int argc, char** argv) {
	std::vector<int> numbers;
	Stack<int64_t>* S1 = new Stack<int64_t>();
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

	Queue<int64_t>* Q1 = new Queue<int64_t>();
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

	LinkedList<int64_t>* L1 = new LinkedList<int64_t>();
	L1->insert(10);
	L1->insert(5);
	L1->insert(11);
	L1->print();
	L1->remove(5);
	L1->insert(414);
	L1->insert(14);
	L1->insert(1);
	L1->insert(4);
	L1->print();
	L1->reverse();
	L1->print();

	return 0;
}



