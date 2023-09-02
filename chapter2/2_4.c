#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <lsort.h>

uint64_t seed;

void test_inversions(char* command) {
	system(command);
	int64_array* arr = int_read("array.txt");
	uint64_t invs = inversion_count(arr, 0, arr->count - 1);
	printf("inversion count = %llu\n", invs);
	int_free(arr);
}

int main(int argc, char** argv) {
	test_inversions("generate -10 10 5");
	test_inversions("generate -100 100 100");
	test_inversions("generate -1400 50 5000");
	test_inversions("generate -1300 5000 10000");
	test_inversions("generate -1000 1000 50000");
	
	return 0;
}