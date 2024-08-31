//k-sorting

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <lsort.h>

int main(int argc, char** argv){
	srand(time(0));
	int64_t k = 0;
	if(argc == 2){
		k = atoi(argv[1]);
	}
	int64_array* arr = int_read("array.txt");
	clock_t begin = clock();
	modified_quicksort(arr->ptr, 0, arr->count - 1, k);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("cpu: %.5lf seconds\n", time_spent);
	verf_print(int_verf_ksorted(arr, 'a', k));
	int_free(arr);
	
	return 0;
}