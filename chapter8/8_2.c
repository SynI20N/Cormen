#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <lsort.h>

typedef struct{
	int start;
	int end;
} sort_data;

uint16_t k = 3;

//this code fails to sort when array a doesnt contain all possible value from [1, k]
//i shall return to this later
void modified_counting_sort(int64_array* a, uint16_t k){
	int64_t* A = a->ptr;
	sort_data* C = (sort_data*)calloc(k, sizeof(*C));
	for(uint64_t i = 0; i < a->count; i++){
		C[A[i] - 1].end++;
	}
	for(uint64_t i = 1; i < k; i++){
		C[i].end += C[i-1].end;
	}
	C[0].start = 0;
	for(uint64_t i = 1; i < k; i++){
		C[i].start = C[i-1].end;
	}
	for(uint64_t i = 0; i < k; i++){
		C[i].end--;
	}
	
	uint64_t i = 0;
	uint64_t j = 0;
	int64_t tmp = 0;
	uint64_t count = 0;
	while(j < a->count){
		if(j > C[i].end){
			i++;
		}
		if(A[j]-1 == i){
			j++;
		}
		else{
			if(A[C[A[j]-1].start] == A[j]){
				C[A[j]-1].start++;
			}
			else{
				tmp = A[C[A[j]-1].start];
				A[C[A[j]-1].start] = A[j];
				A[j] = tmp;
			}
		}
		count++;
	}
	printf("iterations: %lu\n", count);
	free(C);
}

int main(int argc, char** argv){
	if(argc == 2){
		k = atoi(argv[1]);
	}
	int64_array* arr = int_read("array.txt");
	modified_counting_sort(arr, k);
	verf_print(int_verf(arr, 'a'));
	int_free(arr);
	return 0;
}