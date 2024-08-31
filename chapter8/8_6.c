//merging two arrays

#include <stdlib.h>
#include <stdint.h>
#include <lsort.h>

#define INT_RDX_COUNT 20

void lsd_radix_sort(int64_array* a){
	int64_t* A = a->ptr;
	uint64_t count = a->count;
	int* C = (int*)calloc(INT_RDX_COUNT, sizeof(int));
	uint16_t* I = malloc(sizeof(uint16_t) * count);
	int64_t* B = (int64_t*)malloc(sizeof(*B) * count);
	int64_t max = A[0];
	for(uint64_t i = 1; i < count; i++){
		if(llabs(A[i]) > max){
			max = llabs(A[i]);
		}
	}
	uint16_t digits = 0;
	while(max != 0){
		max /= 10;
		digits++;
	}
	int64_t div = 1;
	for(uint16_t g = 1; g <= digits; g++){
		for(uint64_t i = 0; i < count; i++){
			I[i] = (A[i] / div) % 10 + 9;
			C[I[i]]++;
		}
		for(uint16_t i = 1; i < INT_RDX_COUNT; i++){
			C[i] += C[i-1];
		}
		for(uint16_t i = 0; i < INT_RDX_COUNT; i++){
			C[i]--;
		}
		for(int64_t i = count - 1; i >= 0; i--){
			B[C[I[i]]--] = A[i];
		}
		for(uint64_t i = 0; i < count; i++){
			A[i] = B[i];
		}
		for(uint16_t i = 0; i < INT_RDX_COUNT; i++){
			C[i] = 0;
		}
		div *= 10;
	}
	free(B);
	free(C);
	free(I);
}

int main(int argc, char** argv){
	system("generate -1000 1000 100");
	int64_array* arr1 = int_read("array.txt");
	lsd_radix_sort(arr1);
	system("generate -1000 1000 100");
	int64_array* arr2 = int_read("array.txt");
	lsd_radix_sort(arr2);
	int64_array* m = merge(arr1, arr2);
	verf_print(int_verf(m, 'a'));
	int_free(m);
	return 0;
}