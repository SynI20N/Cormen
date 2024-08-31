#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <lsort.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define EPS 1

void test_brute_force(const char* command) {
	system(command);
	int64_array* arr = int_read("array.txt");
	clock_t begin = clock();
	int64_sub s = brute_force_subarray(arr);
	clock_t end = clock();
	printf("low: %llu high: %llu sum: %lld\n", s.low, s.high, s.sum); 
	double time_spent = ((double)(end - begin) / CLOCKS_PER_SEC) * 1000;
	printf("cpu: %5.2lf\n", time_spent);
	int_free(arr);
}

void test_recursive(const char* command) {
	system(command);
	int64_array* arr = int_read("array.txt");
	clock_t begin = clock();
	int64_sub s = recursive_subarray(arr-> ptr, 0, arr->count - 1);
	clock_t end = clock();
	printf("low: %llu high: %llu sum: %lld\n", s.low, s.high, s.sum); 
	double time_spent = ((double)(end - begin) / CLOCKS_PER_SEC) * 1000;
	printf("cpu: %5.2lf\n", time_spent);
	int_free(arr);
}

void test_dp(const char* command) {
	system(command);
	int64_array* arr = int_read("array.txt");
	clock_t begin = clock();
	int64_sub s = find_maximum_subarray(arr);
	clock_t end = clock();
	printf("low: %llu high: %llu sum: %lld\n", s.low, s.high, s.sum); 
	double time_spent = ((double)(end - begin) / CLOCKS_PER_SEC) * 1000;
	printf("cpu: %5.2lf\n", time_spent);
	int_free(arr);
}

void compare_brute_and_recursive() {
	int64_sub s = {0};
	char* cmd = malloc(sizeof(char) * 100);
	double time1 = 0, time2 = 0;
	clock_t begin, end;
	int32_t length = 1;
	while(fabs(time1 - time2) <= EPS) {
		memset(cmd, 0, sizeof(char) * 100);
		sprintf(cmd, "generate.out -100 100 %d", length);
		system(cmd);
		int64_array* arr = int_read("array.txt");
		begin = clock();
		s = brute_force_subarray(arr);
		end = clock();
		time1 = ((double)(end - begin) / CLOCKS_PER_SEC) * 1000;
		begin = clock();
		s = recursive_subarray(arr->ptr, 0, arr->count - 1);
		end = clock();
		time2 = ((double)(end - begin) / CLOCKS_PER_SEC) * 1000;
		int_free(arr);
		length++;
	}
	printf("n0 = %d\n", length);
	free(cmd);
}

void test_naive_multiply(const char* command) {
	system(command);
	int64_array* arr1 = int_read("array.txt");
	system(command);
	int64_array* arr2 = int_read("array.txt");

	
	int64_matrix* A = array_to_matrix(arr1);
	matrix_print(A);
	int64_matrix* B = array_to_matrix(arr2);
	matrix_print(B);
	int64_matrix* C = matrix_multiply(A, B);
	matrix_print(C);
	matrix_free(A);
	matrix_free(B);
	matrix_free(C);
}

void cmp_strass(strassen_matrix* A, int64_matrix* B) {
	uint64_t n = B->rows;
	for(uint64_t i = 0; i < n; i++) {
		for(uint64_t j = 0; j < n; j++) {
			if(B->ptr[i][j] != A->ptr[A->rmin + i][A->cmin + j]) {
				printf("test not passed\n");
				return;
			}
		}
	}
	printf("test passed\n");
}

void test_strassen_multiply(const char* command) {
        system(command);
        int64_array* arr1 = int_read("array.txt");
        system(command);
        int64_array* arr2 = int_read("array.txt");


        int64_matrix* A = array_to_matrix(arr1);
        int64_matrix* B = array_to_matrix(arr2);
        int64_matrix* C = matrix_multiply(A, B);
	strassen_matrix* A_S = matrix_to_strass(A);
	strassen_matrix* B_S = matrix_to_strass(B);
	strassen_matrix* C_S = strassen_multiply(A_S, B_S);
	cmp_strass(C_S, C);
	strassen_free(A_S);
	strassen_free(B_S);
	strassen_free(C_S);
	free(A);
	free(B);
        matrix_free(C);
}


int main(int argc, char** argv) {
	/*test_brute_force("generate -1 1 10");
	test_recursive("");
	test_dp("");
	test_brute_force("generate -100 100 1000");
	test_recursive("");
	test_dp("");
	test_brute_force("generate -10 10 100");
	test_recursive("");
	test_dp("");
	test_brute_force("generate -1000 1000 10000");
	test_recursive("");
	test_dp("");
	test_brute_force("generate -10 10 5");
	test_recursive("");
	test_dp("");
	printf("---------------\n"); */
	compare_brute_and_recursive();
	test_naive_multiply("generate.out -10 10 9");
	test_strassen_multiply("generate.out -10 10 25 1452");
	test_strassen_multiply("generate.out -10 10 16 642");
	test_strassen_multiply("generate.out -100 100 125 2");
	test_strassen_multiply("generate.out -100 100 49 52");
	test_strassen_multiply("generate.out -100 100 6324 452");
	test_strassen_multiply("generate.out -100 100 1024 5");
	test_strassen_multiply("generate.out -50 50 2048 12");
	test_strassen_multiply("generate.out -100 100 10000 14");
	test_strassen_multiply("generate.out -100 100 1 53534");
	test_strassen_multiply("generate.out -100 100 4 7543");
	test_strassen_multiply("generate.out -100 100 12 1456");
	test_strassen_multiply("generate.out -100 100 9000 575");
	return 0;
}
