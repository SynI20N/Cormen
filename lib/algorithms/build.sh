#!/bin/bash
sudo cp lsort.hpp /usr/include
g++ -O3 -o liblsort.so lsort.cpp -I/usr/include -s -shared -D LSORT_EXPORTS -g
sudo cp liblsort.so /usr/lib