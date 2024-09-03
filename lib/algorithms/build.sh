#!/bin/bash
sudo cp lsort.h /usr/include
gcc -O3 -o liblsort.so lsort.c -I/usr/include -s -shared -D LSORT_EXPORTS -g
sudo cp liblsort.so /usr/lib