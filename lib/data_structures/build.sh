#!/bin/bash
sudo cp lds.hpp /usr/include
g++ -std=c++20 -O3 -o liblds.so lds.cpp -I/usr/include -s -shared -g
sudo cp liblds.so /usr/lib