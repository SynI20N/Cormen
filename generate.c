#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

char V_FLAG = 0;
int16_t A_DEF = 1;
int16_t B_DEF = 10;
uint64_t COUNT_DEF = 10000;

void generate(int16_t A, int16_t B, uint64_t count){
	FILE* f = fopen("array.txt", "w");
	for(uint64_t i = 0; i < count; i++){
		fprintf(f, "%d ", rand() % (B - A + 1) + A);
	}
	fclose(f);
}

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
			fprintf(f, "%c", rand() % 26 + 97);
		}			
		fprintf(f, " ");
		sum += size;
	}
	fclose(f);
}

int strcompare(char* s1, const char* s2){
	for(int i = 0; s2[i] != '\0'; i++){
		if(s1[i] != s2[i]){
			return 0;
		}
	}
	return 1;
}

int main(int argc, char** argv){
	srand(time(0));
	if(argc == 2){
		COUNT_DEF = atoi(argv[1]);
	}
	else if(argc == 3){
		if(strcompare(argv[1], "-v")){
			if(argv[1][2] == 's' || argv[1][2] == 'i'){
				V_FLAG = argv[1][2];
			}
			else{
				printf("usage: -v[s, i] [COUNT] s - string, i - int64 variable generation\n");
				exit(-1);
			}
			COUNT_DEF = atoi(argv[2]);
		}
		else {
			A_DEF = atoi(argv[1]);
			B_DEF = atoi(argv[2]);
		}
	}
	else if(argc >= 4){
		A_DEF = atoi(argv[1]);
		B_DEF = atoi(argv[2]);
		COUNT_DEF = atoi(argv[3]);
		if(argc == 5){
			srand(atoi(argv[4]));
		}
	}
	if(V_FLAG){
		if(V_FLAG == 's'){
			gen_random_str(COUNT_DEF, "str_array.txt");
		}
		else if(V_FLAG == 'i'){
			gen_random_int(COUNT_DEF, "int_array.txt");
		}
	}
	else {
		generate(A_DEF, B_DEF, COUNT_DEF);
	}
	
	return 0;
}
