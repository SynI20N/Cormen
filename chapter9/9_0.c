//interestingly enough, more optimal code in lsort.c runs 70% slower on average than just 2n - 2 solution
//when I omit -O3 on gcc 9_0.c, the situation changes drastically so this is all compiler magic

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <lsort.h>

int main(int argc, char** argv) {
	srand(time(0));
	uint64_t i = 0;
	if(argc == 2){
		i = atoi(argv[1]);
	}
	int64_array* arr = int_read("array.txt");
	
	clock_t begin = clock();
	int64_ord ord1;
	ord1.max = find_max(arr);
	ord1.min = find_min(arr);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("cpu: %.5lf seconds\n", time_spent);
	
	begin = clock();
	int64_ord ord2 = borders(arr);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("cpu: %.5lf seconds\n", time_spent);
	
	if(ord1.max == ord2.max && ord1.min == ord2.min) {
		printf("borders found correct\n");
	}
	else {
		printf("borders incorrect\n");
	}
	int64_t linear_order = linear_select(arr->ptr, 0, arr->count - 1, i);
	int64_t orderi = quick_select(arr->ptr, 0, arr->count - 1, i);
	int64_t iter_orderi = quick_select_iterative(arr->ptr, 0, arr->count - 1, i);
	if(orderi == linear_order) {
		printf("select functions work correctly\n");
	}
	else {
		printf("at least one select function is incorrect\n");
	}
	int_print(arr);
	printf("linear ans = [%ld]\n", linear_order);
	printf("quick ans = [%ld]\n", orderi);
	
	int_free(arr);
	return 0;
}
