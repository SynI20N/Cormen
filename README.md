<p>In order to build code from chapters:</p>
<h2>library</h2>
<code>cd lib && bash build.sh</code>
<h2>.c files</h2>
<code>gcc -O3 -o myprog source.c -L/usr/lib -llsort -llds -lm</code>
<h2>.cpp files</h2>
<code>g++ -std=c++20 -O3 -o 10_0.out 10_0.cpp -L/usr/lib -llsort -llds -lm</code>