#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <lsort.h>

int RAND_SEED = 0;

int64_t convert_to_int(int64_array* arr) {
	int64_t res = 0;
	for(uint64_t i = 0; i < arr->count; i++){
		res += arr->ptr[i] * pow(2, arr->count - 1 - i);
	}
	return res;
}

void test_insertion_sort(const char* command) {
	system(command);
	int64_array* arr = int_read("array.txt");
	insertion_sort(arr);
	verf_print(int_verf(arr, 'a'));
	int_free(arr);
}

void test_linear_search(const char* command) {
	srand(RAND_SEED++);
	system(command);
	int64_array* arr = int_read("array.txt");
	int32_t i = rand() % (arr->count);
	int64_t v = arr->ptr[i];
	uint64_t index = linear_search(arr, v);
	if(arr->ptr[i] == arr->ptr[index]) {
		printf("found value %lld at %llu\n", v, index);
	}
	else {
		printf("failed linear search\n");
	}
	int_free(arr);
}

void test_bit_add(const char* command1, const char* command2) {
	system(command1);
	int64_array* int1 = int_read("array.txt");
	system(command2);
	int64_array* int2 = int_read("array.txt");
	int64_array* intsum = add_bits(int1, int2);
	if(convert_to_int(int1) + convert_to_int(int2) == convert_to_int(intsum)) {
		printf("added two n-bit ints\n");
	}
	else {
		printf("failed to add n-bit\n");
	}
	int_free(int1);
	int_free(int2);
	int_free(intsum);
}

void test_selection_sort(const char* command) {
	system(command);
	int64_array* arr = int_read("array.txt");
	selection_sort(arr);
	verf_print(int_verf(arr, 'a'));
	int_free(arr);
}

void test_merge_sort(const char* command) {
	system(command);
	int64_array* arr = int_read("array.txt");
	merge_sort(arr, 0, arr->count - 1);
	verf_print(int_verf(arr, 'a'));
	int_free(arr);
}

void test_binary_search(const char* command) {
	srand(RAND_SEED++);
	system(command);
	int64_array* arr = int_read("array.txt");
	merge_sort(arr, 0, arr->count - 1);
	int32_t i = rand() % (arr->count);
	int64_t v = arr->ptr[i];
	uint64_t index = binary_search(arr, v);
	if(arr->ptr[i] == arr->ptr[index]) {
		printf("found value %lld at %llu\n", v, index);
	}
	else {
		printf("failed binary search: index = %llu\n", index);
	}
	int_free(arr);
}

int main(int agrc, char** argv) {
	test_insertion_sort("generate -10 10 100");
	test_insertion_sort("generate -100 100 10000");
	test_insertion_sort("generate -100 0 100");
	test_insertion_sort("generate -1000 1000 100000");
	test_insertion_sort("generate 0 1 10000");
	
	test_linear_search("generate -10 10 5");
	test_linear_search("generate -100 100 100");
	test_linear_search("generate -100 0 5000");
	test_linear_search("generate -1000 1000 1000000");
	test_linear_search("generate 0 1 20000");
	
	test_bit_add("generate 0 1 10", "generate 0 1 9");
	test_bit_add("generate 0 1 11", "generate 0 1 5");
	test_bit_add("generate 0 1 18", "generate 0 1 12");
	test_bit_add("generate 0 1 15", "generate 0 1 10");
	test_bit_add("generate 0 1 13", "generate 0 1 2");
	
	test_selection_sort("generate -10 10 100");
	test_selection_sort("generate -100 100 10000");
	test_selection_sort("generate -100 0 100");
	test_selection_sort("generate -1000 1000 100000");
	test_selection_sort("generate 0 1 10000");
	
	test_merge_sort("generate -10 10 100");
	test_merge_sort("generate -100 100 10000");
	test_merge_sort("generate -100 0 100");
	test_merge_sort("generate -1000 1000 100000");
	test_merge_sort("generate 0 1 10000");
	
	test_binary_search("generate -10 10 5");
	test_binary_search("generate -100 100 100");
	test_binary_search("generate -100 0 5000");
	test_binary_search("generate -1000 1000 1000000");
	test_binary_search("generate 0 1 20000");
	test_binary_search("generate 0 1 0");
	
	return 0;
}
