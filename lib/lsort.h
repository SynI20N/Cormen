#ifdef WIN
#ifdef LSORT_EXPORTS
  #define SORTAPI __declspec(dllexport)
#else
  #define SORTAPI __declspec(dllimport)
#endif
#else
#ifdef LSORT_EXPORTS
  #define SORTAPI
#else
  #define SORTAPI
#endif
#endif

#ifdef WIN
#define SORTCALL __cdecl
#else
#define SORTCALL
#endif

typedef struct{
	uint64_t low;
	uint64_t high;
	int64_t sum;
} int64_sub;

typedef struct{
	int64_t* ptr;
	uint64_t count;
} int64_array;

typedef struct{
	char** ptr;
	uint64_t count;
} str_array;

typedef struct{
	int64_t min;
	int64_t max;
} int64_ord;

typedef struct{
	int64_t** ptr;
	uint64_t cols;
	uint64_t rows;
} int64_matrix;

typedef struct{
	int64_t** ptr;
	uint64_t rmin;
	uint64_t cmin;
	uint64_t size;
} strassen_matrix;

//INT ARRAY FUNCTIONS
SORTAPI int64_array* SORTCALL int_read(const char* path);
SORTAPI void SORTCALL int_print(int64_array* a);
SORTAPI void SORTCALL int_free(int64_array* a);
SORTAPI int SORTCALL int_verf(int64_array* a, char mode);
SORTAPI int SORTCALL int_verf_ksorted(int64_array* a, char mode, uint64_t k);
SORTAPI int64_array* SORTCALL merge(int64_array* a, int64_array* b);
//minmax
SORTAPI int64_ord SORTCALL borders(int64_array* a);
SORTAPI int64_t SORTCALL find_max(int64_array* a);
SORTAPI int64_t SORTCALL find_min(int64_array* a);
//sort
SORTAPI int64_t SORTCALL hoare_partition_around(int64_t* arr, int64_t lo, int64_t hi, int64_t x);
SORTAPI int64_t SORTCALL hoare_partition(int64_t* arr, int64_t lo, int64_t hi);
SORTAPI void SORTCALL modified_quicksort(int64_t* a, int64_t lo, int64_t hi, int64_t k);
SORTAPI void SORTCALL insertion_sort(int64_array* arr);
SORTAPI void SORTCALL selection_sort(int64_array* arr);
SORTAPI void SORTCALL merge_sort(int64_array* a, uint64_t lo, uint64_t hi);
//select
SORTAPI int64_t SORTCALL linear_select(int64_t* a, int64_t lo, int64_t hi, uint64_t i);
SORTAPI int64_t SORTCALL quick_select(int64_t* a, int64_t lo, int64_t hi, uint64_t i);
SORTAPI int64_t SORTCALL quick_select_iterative(int64_t* a, int64_t lo, int64_t hi, uint64_t i);
//search
SORTAPI uint64_t SORTCALL linear_search(int64_array* a, int64_t value);
SORTAPI uint64_t SORTCALL binary_search(int64_array* a, int64_t value);
//maximum subarray
SORTAPI int64_sub SORTCALL brute_force_subarray(int64_array* a);
SORTAPI int64_sub SORTCALL recursive_subarray(int64_t* a, int64_t lo, int64_t hi);
SORTAPI int64_sub SORTCALL find_maximum_subarray(int64_array* a);
//random permutations
SORTAPI int64_array* SORTCALL permute_by_sort(int64_array* a);
SORTAPI int64_array* SORTCALL randomize_in_place(int64_array* a);
//INT MATRIX FUNCTIONS
SORTAPI int64_matrix* SORTCALL matrix_ctor(uint64_t rows, uint64_t cols);
SORTAPI strassen_matrix* SORTCALL matrix_to_strass(int64_matrix* a);
SORTAPI int64_matrix* SORTCALL array_to_matrix(int64_array* a);
SORTAPI void SORTCALL matrix_print(int64_matrix* A);
SORTAPI void SORTCALL matrix_free(int64_matrix* A);
SORTAPI void SORTCALL strassen_print(strassen_matrix* A);
SORTAPI void SORTCALL strassen_free(strassen_matrix* A);
//matrix multiplication
SORTAPI int64_matrix* SORTCALL matrix_multiply(int64_matrix* A, int64_matrix* B);
SORTAPI strassen_matrix* SORTCALL strassen_multiply(strassen_matrix* A, strassen_matrix* B);

//STRING ARRAY FUNCTIONS
SORTAPI str_array* SORTCALL str_read(const char* path);
SORTAPI void SORTCALL str_free(str_array* a);
SORTAPI void SORTCALL str_print(str_array* a);
SORTAPI int SORTCALL str_verf(str_array* a, char mode);

//MISC
SORTAPI int SORTCALL comp16(const void *i, const void *j);
SORTAPI int SORTCALL comp64(const void *i, const void *j);
SORTAPI void SORTCALL verf_print(int res);
SORTAPI int64_array* SORTCALL add_bits(int64_array* i1, int64_array* i2);
SORTAPI uint64_t SORTCALL inversion_count(int64_array* a, uint64_t lo, uint64_t hi);
