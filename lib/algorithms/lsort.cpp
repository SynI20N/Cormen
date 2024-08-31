#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <lsort.hpp>

#define lmax(x, y) ( (x) > (y) ? (x) : (y) )

int64_array* SORTCALL int_read(const char* path){
	int64_array* a = (int64_array*)malloc(sizeof(*a));
	FILE* f = fopen(path, "r");
	if(f == 0){
		printf("error loading file\n");
		exit(-1);
	}
	uint64_t count = 0;
	int64_t num = 0;
	while(fscanf(f, "%ld ", &num) != EOF){
		count++;
	}
	if(count == 0) {
		printf("array count is 0 terminating . . .\n");
		exit(-1);
	}
	fseek(f, 0, 0);
	a->ptr = (int64_t*)malloc(sizeof(int64_t) * count);
	count = 0;
	while(fscanf(f, "%ld ", a->ptr + count) != EOF){
		count++;
	}
	a->count = count;
	fclose(f);
	return a;
}

str_array* SORTCALL str_read(const char* path){
	str_array* t = (str_array*)malloc(sizeof(*t));
	FILE* f = fopen(path, "r");
	if(f == 0){
		printf("error loading file\n");
		exit(-1);
	}
	uint64_t count = 0;
	uint64_t currword = 0;
	uint64_t maxword = 0;
	char ch = 0;
	while(fscanf(f, "%c", &ch) != EOF){
		if(ch == ' '){
			count++;
			if(currword > maxword){
				maxword = currword;
			}
			currword = 0;
		}
		currword++;
	}
	fseek(f, 0, 0);
	t->ptr = (char**)malloc(sizeof(*t) * count);
	t->count = count;
	uint64_t i = 0;
	char* str = (char*)malloc(sizeof(char) * (maxword + 1));
	while(fscanf(f, "%s ", str) != EOF){
		t->ptr[i] = (char*)malloc(sizeof(char) * (strlen(str) + 1));
		strcpy(t->ptr[i], str);
		i++;
	}
	free(str);
	fclose(f);
	return t;
}

int64_array* SORTCALL merge(int64_array* a, int64_array* b){
	int64_array* res = (int64_array*)malloc(sizeof(*res));
	uint64_t pa = 0;
	uint64_t pb = 0;
	int64_t* A = a->ptr;
	int64_t* B = b->ptr;
	uint64_t na = a->count;
	uint64_t nb = b->count;
	uint64_t i = 0;
	int64_t* C = (int64_t*)malloc(sizeof(int64_t) * (na + nb));
	while(pa != na - 1 && pb != na - 1){
		if(A[pa] <= B[pb]){
			C[i] = A[pa];
			pa++;
		}
		else {
			C[i] = B[pb];
			pb++;
		}
		i++;
	}
	for(uint64_t j = pa; j != na - 1; j++){
		C[i] = A[j];
		i++;
	}
	for(uint64_t j = pb; j != nb - 1; j++){
		C[i] = B[j];
		i++;
	}
	res->ptr = C;
	res->count = i;
	int_free(a);
	int_free(b);
	return res;
}

void SORTCALL merge_subroutine(int64_array* a, uint64_t lo, uint64_t pivot, uint64_t hi) {
	uint64_t n1 = pivot - lo + 1;
	uint64_t n2 = hi - pivot;
	int64_t* L = (int64_t*)malloc(sizeof(*L) * (n1 + 1));
	int64_t* R = (int64_t*)malloc(sizeof(*L) * (n2 + 1));
	uint64_t i, j;
	for(i = 0; i < n1; i++) {
		L[i] = a->ptr[lo + i];
	}
	for(j = 0; j < n2; j++) {
		R[j] = a->ptr[pivot + j + 1];
	}
	L[n1] = INT64_MAX;
	R[n2] = INT64_MAX;
	i = 0;
	j = 0;
	for(uint64_t k = lo; k <= hi; k++) {
		if(L[i] <= R[j]) {
			a->ptr[k] = L[i];
			i++;
		}
		else {
			a->ptr[k] = R[j];
			j++;
		}
	}
	free(L);
	free(R);
}

void SORTCALL merge_sort(int64_array* a, uint64_t lo, uint64_t hi) {
	if(lo < hi) {
		uint64_t q = floor((lo + hi) >> 1);
		merge_sort(a, lo, q);
		merge_sort(a, q + 1, hi);
		merge_subroutine(a, lo, q, hi);
	}
}

int64_t SORTCALL hoare_partition_around(int64_t* arr, int64_t lo, int64_t hi, int64_t x) {
	int64_t i = lo - 1;
        int64_t j = hi + 1;
        int64_t tmp;
        while(1){
                do{ j--; }while(arr[j] > x);
                do{ i++; }while(arr[i] < x);
                if(i < j){
                        tmp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = tmp;
                }
                else{
                        return j;
                }
        }
}

int64_t SORTCALL hoare_partition(int64_t* arr, int64_t lo, int64_t hi){
	int64_t x = arr[rand() % (hi - lo) + lo];
	return hoare_partition_around(arr, lo, hi, x);
}

void SORTCALL modified_quicksort(int64_t* a, int64_t lo, int64_t hi, int64_t k){
	while(lo < hi - k + 1){
		int64_t q = hoare_partition(a, lo, hi);
		modified_quicksort(a, lo, q, k);
		lo = q + 1;
	}
}

void SORTCALL insertion_sort(int64_array* arr) {
	int64_t* A = arr->ptr;
	int64_t key = 0;
	int64_t i;
	for(uint64_t j = 1; j < arr->count; j++) {
		key = A[j];
		i = j - 1;
		while(i >= 0 && A[i] > key) {
			A[i+1] = A[i];
			i--;
		}
		A[i+1] = key;
	}
}

void SORTCALL selection_sort(int64_array* arr) {
	int64_t* A = arr->ptr;
	uint64_t k, i, j = 0;
	int64_t temp = 0;
	while(j < arr->count - 1) {
		k = j;
		for(i = j + 1; i < arr->count; i++) {
			if(A[i] < A[k]) {
				k = i;
			}
		}
		temp = A[k];
		A[k] = A[j];
		A[j] = temp;
		j++;
	}
}

int64_t SORTCALL quick_select(int64_t* a, int64_t lo, int64_t hi, uint64_t i) {
	if(lo == hi) {
		return a[lo];
	}
	int64_t q = hoare_partition(a, lo, hi);
	uint64_t k = q - lo + 1;
	if(i <= k) {
		return quick_select(a, lo, q, i);
	}
	else return quick_select(a, q + 1, hi, i - k);
}

int64_t SORTCALL quick_select_iterative(int64_t* a, int64_t lo, int64_t hi, uint64_t i) {
	while(lo < hi) {
		int64_t q = hoare_partition(a, lo, hi);
		uint64_t k = q - lo + 1;
		if(i <= k) {
			hi = q;
		}
		else {
			lo = q + 1;
			i -= k;
		}
	}
	return a[lo];
}

int64_t SORTCALL linear_select(int64_t* a, int64_t lo, int64_t hi, uint64_t i) {
	while((hi - lo + 1) % 5 != 0) {
		for(int64_t j = lo + 1; j <= hi; j++) {
			if(a[lo] > a[j]) {
				int64_t temp = a[lo];
				a[lo] = a[j];
				a[j] = temp;
			}
		}
		if(i == 1) {
			return a[lo];
		}
		lo += 1;
		i -= 1;
	}
	int64_t g = (hi - lo + 1) / 5;
	for(int64_t j = lo; j <= lo + g - 1; j++) {
		for(int64_t k = g; k < 5 * g; k += g) {
	                int64_t key = a[j + k];
                	int64_t i = j + k - g;
        	        while(i >= j && a[i] > key) {
	                        a[i + g] = a[i];
                        	i -= g;
                	}
                	a[i + g] = key;
        	}
	}
	int64_t x = linear_select(a, lo + 2*g, lo + 3*g - 1, ceil((double)g / 2));
	int64_t q = hoare_partition_around(a, lo, hi, x);
	uint64_t k = q - lo + 1;
	if(i <= k) {
		return linear_select(a, lo, q, i);
	}
	else return linear_select(a, q + 1, hi, i - k);
}

uint64_t SORTCALL linear_search(int64_array* a, int64_t value) {
	int64_t* A = a->ptr;
	for(uint64_t i = 0; i < a->count; i++) {
		if(A[i] == value) {
			return i;
		}
	}
	return -1;
}

uint64_t SORTCALL binary_search(int64_array* a, int64_t value) {
	int64_t* A = a->ptr;
	uint64_t lo = 0;
	uint64_t hi = a->count - 1;
	uint64_t mi;
	while(lo <= hi) {
		mi = floor((lo + hi) >> 1);
		if(A[mi] == value) {
			return mi;
		}
		if(A[mi] > value) {
			hi = mi - 1;
		}
		else if(A[mi] < value) {
			lo = mi + 1;
		}
	}
	return -1;
}

SORTAPI int64_sub SORTCALL brute_force_subarray(int64_array* a) {
	int64_t* A = a->ptr;
	uint64_t lo = 0;
	uint64_t hi = 0;
	int64_t max = INT64_MIN;
	int64_sub sub = {0};
	for(uint64_t i = 1; i < a->count; i++) {
		A[i] += A[i-1];
	}
	for(uint64_t i = 0; i < a->count; i++) {
		for(uint64_t j = i + 1; j < a->count; j++) {
			if(A[j] - A[i] > max) {
				max = A[j] - A[i];
				hi = j;
				lo = i;
			}
		}
	}
	sub.low = lo;
	sub.high = hi;
	sub.sum = max;
	return sub;
}

int64_sub max_crossing_subarray(int64_t* a, int64_t lo, int64_t mid, int64_t hi) {
	int64_sub s = {0};
	int64_t i;
	int64_t left_sum = INT64_MIN;
	int64_t sum = 0;
	for(i = mid; i >= lo; i--) {
		sum += a[i];
		if(sum > left_sum) {
			left_sum = sum;
			s.low = i;
		}
	}
	int64_t right_sum = INT64_MIN;
	sum = 0;
	for(i = mid + 1; i <= hi; i++) {
		sum += a[i];
		if(sum > right_sum) {
			right_sum = sum;
			s.high = i;
		}
	}
	s.sum = left_sum + right_sum;
	return s;
}

SORTAPI int64_sub SORTCALL recursive_subarray(int64_t* a, int64_t lo, int64_t hi) {
	if(lo == hi) { 
		int64_sub sub = { .low = lo, .high = hi, .sum = a[lo] };
		return sub;
	}
	else {
		int64_t mid = floor((lo + hi) >> 1);
		int64_sub left = recursive_subarray(a, lo, mid);
		int64_sub right = recursive_subarray(a, mid + 1, hi);
		int64_sub cross = max_crossing_subarray(a, lo, mid, hi);
		if(left.sum >= right.sum && left.sum >= cross.sum) {
			return left;
		}
		else if(right.sum >= cross.sum) {
			return right;
		}
		else return cross;
	}
}

SORTAPI int64_sub SORTCALL find_maximum_subarray(int64_array* a) {
	int64_t* A = a->ptr;
	int64_sub max = { .low = 0, .high = 0, .sum = A[0] };
	int64_sub curr = max;
	for(int i = 1; i < a->count; i++) {
		if(curr.sum + A[i] >= 0) {
			curr.sum += A[i];
			curr.high = i;
		}
		else {
			curr.sum = 0;
			curr.low = i + 1;
		}
		if(curr.sum > max.sum) {
			max = curr;
		}
	}
	return max;
}

int64_ord SORTCALL borders(int64_array* a){
	int64_t* A = a->ptr;
	int64_ord res;
	uint64_t n = a->count - 1;
	uint64_t i;
	if(a->count & 1 > 0){
		res.max = A[0];
		res.min = res.max;
		i = 1;
	}
	else {
		if(A[0] > A[1]) {
			res.max = A[0];
			res.min = A[1];
		}
		else {
			res.max = A[1];
			res.min = A[0];
		}
		i = 2;
	}
	for(; i < n; i+=2){
		if(A[i] > A[i+1]) {
			if(A[i] > res.max) {
				res.max = A[i];
			}
			if(A[i+1] < res.min) {
				res.min = A[i+1];
			}
		}
		else {
			if(A[i+1] > res.max) {
				res.max = A[i+1];
			}
			if(A[i] < res.min) {
				res.min = A[i];
			}
		}
	}
	return res;
}

int64_t SORTCALL find_max(int64_array* a) {
	int64_t* A = a->ptr;
	int64_t res = A[0];
	for(uint64_t i = 1; i < a->count; i++) {
		if(A[i] > res) {
			res = A[i];
		}
	}
	return res;
}

int64_t SORTCALL find_min(int64_array* a) {
	int64_t* A = a->ptr;
	int64_t res = A[0];
	for(uint64_t i = 1; i < a->count; i++) {
		if(A[i] < res) {
			res = A[i];
		}
	}
	return res;
}

int64_matrix* SORTCALL matrix_ctor(uint64_t rows, uint64_t cols) {
	int64_matrix* res = (int64_matrix*)(sizeof(*res));
        res->ptr = (int64_t**)malloc(sizeof(int64_t*) * rows);
        res->rows = rows;
        res->cols = cols;
        for(uint64_t i = 0; i < rows; i++) {
                res->ptr[i] = (int64_t*)malloc(sizeof(int64_t) * cols);
        }
	return res;
}

int64_matrix* SORTCALL array_to_matrix(int64_array* a) {
        uint64_t n = floor(sqrt(a->count));
        int64_matrix* res = matrix_ctor(n, n);
        for(uint64_t i = 0; i < n; i++) {
                for(uint64_t j = 0; j < n; j++) {
                        res->ptr[i][j] = a->ptr[i * n + j];
                }
        }
        int_free(a);
        return res;
}

void SORTCALL matrix_print(int64_matrix* A) {
	for(uint64_t i = 0; i < A->rows; i++) {
		for(uint64_t j = 0; j < A->cols; j++) {
			printf("%5ld", A->ptr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void SORTCALL matrix_free(int64_matrix* A) {
	for(uint64_t i = 0; i < A->rows; i++) {
		free(A->ptr[i]);
	}
	free(A->ptr);
	free(A);
}

void SORTCALL strassen_print(strassen_matrix* A) {
        for(uint64_t i = A->rmin; i < A->size; i++) {
                for(uint64_t j = A->cmin; j < A->size; j++) {
                        printf("%5ld", A->ptr[i][j]);
                }
                printf("\n");
        }
	printf("\n");
}

void SORTCALL strassen_free(strassen_matrix* A) {
        for(uint64_t i = A->rmin; i < A->size; i++) {
                free(A->ptr[i]);
        }
        free(A->ptr);
        free(A);
}


int64_matrix* SORTCALL matrix_multiply(int64_matrix* A, int64_matrix* B) {
	if(A->cols != B->rows) { return 0; }
	int64_matrix* res = matrix_ctor(A->rows, B->cols);
	for(uint64_t i = 0; i < A->rows; i++) {
		for(uint64_t j = 0; j < B->cols; j++) {
			res->ptr[i][j] = 0;
			for(uint64_t k = 0; k < A->cols; k++) {
				res->ptr[i][j] += A->ptr[i][k] * B->ptr[k][j];
			}
		}
	}
	return res;
}

strassen_matrix* partition_matrix(strassen_matrix* M, int16_t corner) {
	strassen_matrix* res = (strassen_matrix*)(sizeof(*res));
	res->ptr = M->ptr;
	res->rmin = (corner >> 1) * (M->size >> 1) + M->rmin;
	res->cmin = (corner % 2) * (M->size >> 1) + M->cmin;
	res->size = M->size >> 1; 
	return res;
}

strassen_matrix* subtract_matrix(strassen_matrix* A, strassen_matrix* B) {
	uint64_t n = A->size;
	strassen_matrix* S = matrix_to_strass(matrix_ctor(n, n));
	for(uint64_t i = 0; i < n; i++) {
		for(uint64_t j = 0; j < n; j++) {
			S->ptr[i][j] = A->ptr[A->rmin + i][A->cmin + j] - B->ptr[B->rmin + i][B->cmin + j]; 
		}
	}
	return S;
}

strassen_matrix* add_matrix(strassen_matrix* A, strassen_matrix* B) {
        uint64_t n = A->size;
        strassen_matrix* S = matrix_to_strass(matrix_ctor(n, n));
        for(uint64_t i = 0; i < n; i++) {
                for(uint64_t j = 0; j < n; j++) {
                        S->ptr[i][j] = A->ptr[A->rmin + i][A->cmin + j] + B->ptr[B->rmin + i][B->cmin + j];
                }
        }
        return S;
}

void copy_matrix(strassen_matrix* src, strassen_matrix* dest) {
	uint64_t n = src->size;
        for(uint64_t i = 0; i < n; i++) {
                for(uint64_t j = 0; j < n; j++) {
                        dest->ptr[dest->rmin + i][dest->cmin + j] = src->ptr[i][j];
                }
        }
}

strassen_matrix* SORTCALL matrix_to_strass(int64_matrix* a) {
	strassen_matrix* res = (strassen_matrix*)(sizeof(*res));
	if(a->rows != 1 && (a->rows & (a->rows - 1))) {
		uint64_t p2 = 1;
		while(p2 < a->rows) {
			p2 <<= 1;
		}
		a->ptr = (int64_t**)realloc(a->ptr, sizeof(int64_t*) * p2);
		for(uint64_t i = 0; i < a->rows; i++) {
			a->ptr[i] = (int64_t*)realloc(a->ptr[i], sizeof(int64_t) * p2);
		}
		for(uint64_t i = a->rows; i < p2; i++) {
			a->ptr[i] = (int64_t*)malloc(sizeof(int64_t) * p2);
		}
		for(uint64_t i = 0; i < a->rows; i++) {
                        for(uint64_t j = a->rows; j < p2; j++) {
                                a->ptr[i][j] = 0;
                        }
                }
		for(uint64_t i = a->rows; i < p2; i++) {
			for(uint64_t j = 0; j < p2; j++) {
				a->ptr[i][j] = 0;
			}
		}
		res->size = p2;
	}
	else {
		res->size = a->rows;
	}
	res->ptr = a->ptr;
	res->rmin = 0;
	res->cmin = 0;
	return res;
}


strassen_matrix* SORTCALL strassen_multiply(strassen_matrix* A, strassen_matrix* B) {
	uint64_t n = A->size;
	strassen_matrix* C = matrix_to_strass(matrix_ctor(n, n));
	if(n == 1) { C->ptr[0][0] = A->ptr[A->rmin][A->cmin] * B->ptr[B->rmin][B->cmin]; }
	else {
		strassen_matrix* A11 = partition_matrix(A, 0);
		strassen_matrix* A12 = partition_matrix(A, 1);
		strassen_matrix* A21 = partition_matrix(A, 2);
		strassen_matrix* A22 = partition_matrix(A, 3);
		strassen_matrix* B11 = partition_matrix(B, 0);
		strassen_matrix* B12 = partition_matrix(B, 1);
		strassen_matrix* B21 = partition_matrix(B, 2);
		strassen_matrix* B22 = partition_matrix(B, 3);
		strassen_matrix* C11 = partition_matrix(C, 0);
		strassen_matrix* C12 = partition_matrix(C, 1);
		strassen_matrix* C21 = partition_matrix(C, 2);
		strassen_matrix* C22 = partition_matrix(C, 3);

		strassen_matrix* S1 = subtract_matrix(B12, B22);
		strassen_matrix* S2 = add_matrix(A11, A12);
		strassen_matrix* S3 = add_matrix(A21, A22);
		strassen_matrix* S4 = subtract_matrix(B21, B11);
		strassen_matrix* S5 = add_matrix(A11, A22);
		strassen_matrix* S6 = add_matrix(B11, B22);
		strassen_matrix* S7 = subtract_matrix(A12, A22);
		strassen_matrix* S8 = add_matrix(B21, B22);
		strassen_matrix* S9 = subtract_matrix(A11, A21);
		strassen_matrix* S10 = add_matrix(B11, B12);

		strassen_matrix* P1 = strassen_multiply(A11, S1);
		strassen_matrix* P2 = strassen_multiply(S2, B22);
		strassen_matrix* P3 = strassen_multiply(S3, B11);
		strassen_matrix* P4 = strassen_multiply(A22, S4);
		strassen_matrix* P5 = strassen_multiply(S5, S6);
		strassen_matrix* P6 = strassen_multiply(S7, S8);
		strassen_matrix* P7 = strassen_multiply(S9, S10);


		/*strassen_print(S1);
		strassen_print(S2);
		strassen_print(S3);
		strassen_print(S4);
		strassen_print(S5);
		strassen_print(P1);
		strassen_print(P2);
		strassen_print(P3);
		strassen_print(P4);
		strassen_print(P5);*/
		
		copy_matrix(add_matrix(subtract_matrix(add_matrix(P5, P4), P2), P6), C11);
		copy_matrix(add_matrix(P1, P2), C12);
		copy_matrix(add_matrix(P3, P4), C21);
		copy_matrix(subtract_matrix(subtract_matrix(add_matrix(P5, P1), P3), P7), C22);
	}	
	return C;
}

int SORTCALL int_verf(int64_array* a, char mode){
	int64_t* A = a->ptr;
	if(mode == 'a'){
		for(uint64_t i = 0; i < a->count - 1; i++){
			if(A[i] > A[i+1]){
				return 0;
			}
		}
	}
	else if(mode == 'd'){
		for(uint64_t i = 0; i < a->count - 1; i++){
			if(A[i] < A[i+1]){
				return 0;
			}
		}
	}
	else {
		return -1;
	}
	return 1;
}

int SORTCALL int_verf_ksorted(int64_array* a, char mode, uint64_t k){
	int64_t* A = a->ptr;
	if(mode == 'a'){
		for(uint64_t i = 0; i < a->count - k; i++){
			if(A[i] > A[i+k]){
				return 0;
			}
		}
	}
	else if(mode == 'd'){
		for(uint64_t i = 0; i < a->count - k; i++){
			if(A[i] < A[i+k]){
				return 0;
			}
		}
	}
	else {
		return -1;
	}
	return 1;
}

int SORTCALL str_verf(str_array* a, char mode){
	char** t = a->ptr;
	uint64_t n = a->count;
	uint64_t j = 0;
	int ch1 = 0;
	int ch2 = 0;
	for(uint64_t i = 0; i < n-1; i++){
		while(1){
			ch1 = t[i][j];
			ch2 = t[i+1][j];
			if(ch1 != '\0' && ch2 == '\0'){
				return 0;
			}
			else if(ch1 == '\0' || ch2 == '\0'){
				break;
			}
			else if(ch2 < ch1){
				return 0;
			}
			else if(ch2 > ch1){
				break;
			}
			j++;
		}
		j = 0;
	}
	return 1;
}

void SORTCALL verf_print(int res){
	if(res){
		printf("array sorted\n");
	}
	else{
		printf("array not sorted\n");
	}
}

void SORTCALL int_free(int64_array* a){
	free(a->ptr);
	free(a);
}

void SORTCALL str_free(str_array* a){
	for(uint64_t i = 0; i < a->count; i++){
		free(a->ptr[i]);
	}
	free(a->ptr);
	free(a);
}

//i, j are constrained to int16_t
int SORTCALL comp16(const void *i, const void *j){
	int32_t x = *((const int*)i);
	int32_t y = *((const int*)j);
	return x - y;
}

//i, j are constrained to int64_t
int SORTCALL comp64(const void *i, const void *j){
	int64_t x = *((const int64_t*)i);
	int64_t y = *((const int64_t*)j);
	if(x >= y) return 1;
	if(x < y) return -1;
	return 0;
}

void SORTCALL str_print(str_array* a){
	for(uint64_t i = 0; i < a->count; i++){
		printf("%s ", a->ptr[i]);
	}
	printf("\n");
}

void SORTCALL int_print(int64_array* a){
	for(uint64_t i = 0; i < a->count; i++){
		printf("%ld ", a->ptr[i]);
	}
	printf("\n");
}

void extend(int64_array* a, uint64_t k){
	a->ptr = (int64_t*)realloc(a->ptr, sizeof(int64_t) * (a->count + k));
	for(uint64_t i = 0; i < k; i++){
		a->ptr[a->count + i] = 0;
	}
	for(uint64_t i = a->count - 1; i < a->count; i--){
		a->ptr[i + k] = a->ptr[i];
		a->ptr[i] = 0;
	}
	a->count += k;
}

//adds n-bit integer with m-bit integer
int64_array* SORTCALL add_bits(int64_array* i1, int64_array* i2) {
	int64_array* res = (int64_array*)(sizeof(*res));
	uint64_t n = lmax(i1->count, i2->count) + 1;
	int64_t k = i1->count - i2->count;
	res->ptr = (int64_t*)calloc(n, sizeof(int64_t));
	res->count = n;
	if(k > 0) {
		extend(i2, k);
	}
	else if(k < 0) {
		k = 0 - k;
		extend(i1, k);
	}
	int64_t* A = i1->ptr;
	int64_t* B = i2->ptr;
	int64_t* C = res->ptr;
	int64_t carry = 0;
	int64_t i = i1->count - 1;
	int64_t sum_i = n - 1;
	while(i >= 0) {
		carry = (A[i] + B[i] + C[sum_i]) >> 1;
		C[sum_i - 1] += carry;
		C[sum_i] = (A[i] + B[i] + C[sum_i]) & 1;
		i--;
		sum_i--;
	}
	return res;
}

uint64_t inversion_sub(int64_array* a, uint64_t lo, uint64_t pivot, uint64_t hi) {
	uint64_t n1 = pivot - lo + 1;
	uint64_t n2 = hi - pivot;
	int64_t* L = (int64_t*)malloc(sizeof(*L) * (n1 + 1));
	int64_t* R = (int64_t*)malloc(sizeof(*L) * (n2 + 1));
	uint64_t i, j;
	for(i = 0; i < n1; i++) {
		L[i] = a->ptr[lo + i];
	}
	for(j = 0; j < n2; j++) {
		R[j] = a->ptr[pivot + j + 1];
	}
	L[n1] = INT64_MAX;
	R[n2] = INT64_MAX;
	i = 0;
	j = 0;
	uint64_t inversions = 0;
	for(uint64_t k = lo; k <= hi; k++) {
		if(L[i] <= R[j]) {
			a->ptr[k] = L[i];
			i++;
		}
		else {
			a->ptr[k] = R[j];
			j++;
			inversions += n1 - i;
		}
	}
	free(L);
	free(R);
	return inversions;
}

//returns the number of inversions required to permute array in non-decreasing order and sorts the input
//im not a fan that this function also sorts but the book wants me to i guess
uint64_t SORTCALL inversion_count(int64_array* a, uint64_t lo, uint64_t hi) {
	if(lo < hi) {
		uint64_t q = floor((lo + hi) >> 1);
		uint64_t left = inversion_count(a, lo, q);
		uint64_t right = inversion_count(a, q + 1, hi);
		uint64_t inversions = inversion_sub(a, lo, q, hi) + left + right;
		return inversions;
	}
	return 0;
}
