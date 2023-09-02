sudo cp lsort.h /usr/lib/gcc/x86_64-linux-gnu/11/include &&
gcc -O3 -o liblsort.so lsort.c -s -shared -D LSORT_EXPORTS  &&
sudo cp liblsort.so /usr/lib/gcc/x86_64-linux-gnu/11 &&
sudo cp liblsort.so /usr/lib
