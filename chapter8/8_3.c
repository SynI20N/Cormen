#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <lsort.h>

#define INT_RDX_COUNT 20
#define CHAR_RDX_COUNT 26

typedef struct {
	char** T;
	char** B;
} sort_data;

void gen_random_int(uint64_t n, const char* path){
	FILE* f = fopen(path, "w");
	uint64_t sum = 0;
	uint16_t size = 0;
	int neg = 0;
	while(sum < n){
		size = rand() % 15 + 1;
		neg = rand() % 2;
		if(neg){
			fprintf(f, "-");
		}
		for(uint16_t i = 0; i < size; i++){
			fprintf(f, "%d", rand() % (10 - !i) + !i);
		}			
		fprintf(f, " ");
		sum += size;
	}
	fclose(f);
}

void gen_random_str(uint64_t n, const char* path){
	FILE* f = fopen(path, "w");
	uint64_t sum = 0;
	uint16_t size = 0;
	while(sum < n){
		size = rand() % 30 + 1;
		for(uint16_t i = 0; i < size; i++){
			fprintf(f, "%c", rand() % CHAR_RDX_COUNT + 97);
		}			
		fprintf(f, " ");
		sum += size;
	}
	fclose(f);
}

void recurse_radix_call(sort_data* d, int64_t lo, int64_t hi, uint16_t digit){
	char** T = d->T;
	char** B = d->B;
	int* C = (int*)calloc(CHAR_RDX_COUNT + 2, sizeof(int));
	uint16_t index;
	for(uint64_t i = lo; i < hi; i++){
		index = digit + 1 > strlen(T[i]) ? 0 : (T[i][digit] - 96);
		C[index]++;
	}
	for(uint16_t i = 1; i < CHAR_RDX_COUNT + 2; i++){
		C[i] += C[i-1];
	}
	for(uint16_t i = 0; i < CHAR_RDX_COUNT + 2; i++){
		C[i]--;
	}
	for(int64_t i = hi - 1; i >= lo; i--){
		index = digit + 1 > strlen(T[i]) ? 0 : (T[i][digit] - 96);
		strcpy(B[lo + C[index]], T[i]);
		C[index]--;
	}
	for(uint64_t i = lo; i < hi; i++){
		strcpy(T[i], B[i]);
	}
	for(uint16_t i = 0; i < CHAR_RDX_COUNT + 2; i++){
		C[i]++;
	}
	for(uint16_t i = 1; i < CHAR_RDX_COUNT + 1; i++){
		if(C[i+1] > C[i] + 1){
			recurse_radix_call(d, lo + C[i], lo + C[i+1], digit + 1);
		}
	}
	free(C);
}

void str_radix_sort(str_array* s){
	char** text = s->ptr;
	uint64_t n = s->count;
	uint16_t max = strlen(text[0]);
	for(uint64_t i = 1; i < n; i++){
		if(strlen(text[i]) > max){
			max = strlen(text[i]);
		}
	}
	char** B = malloc(sizeof(*B) * n);
	for(uint64_t i = 0; i < n; i++){
		B[i] = malloc(sizeof(char) * (max + 1));
	}
	//this is cringe, possible errors when using lib
	for(uint64_t i = 0; i < n; i++){
		text[i] = realloc(text[i], sizeof(char) * (max + 1));
	}
	//
	sort_data* d = malloc(sizeof(*d));
	d->B = B;
	d->T = s->ptr;
	recurse_radix_call(d, 0, n, 0);
	free(d);
	for(uint64_t i = 0; i < n; i++){
		free(B[i]);
	}
	free(B);
}

//only for radix 10 integers
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
	uint64_t n = 0;
	srand(time(0));
	if(argc == 2){
		n = atoi(argv[1]);
	}
	gen_random_str(n, "array_str.txt");
	gen_random_int(n, "array_int.txt");
	int64_array* arr = int_read("array_int.txt");
	clock_t begin = clock();
	lsd_radix_sort(arr);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("cpu: %.5lf seconds\n", time_spent);
	verf_print(int_verf(arr, 'a'));
	int_free(arr);
	str_array* txt = str_read("array_str.txt");
	begin = clock();
	str_radix_sort(txt);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("cpu: %.5lf seconds\n", time_spent);
	verf_print(str_verf(txt, 'a'));
	str_free(txt);
	return 0;
}
