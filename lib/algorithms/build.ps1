cd D:\C\lib\;
Copy-Item "lsort.h" -Destination "C:\ProgramData\chocolatey\lib\mingw\tools\install\mingw64\x86_64-w64-mingw32\include\";
gcc -O3 -o lsort.dll lsort.c -s -shared -D LSORT_EXPORTS;
Copy-Item "lsort.dll" -Destination "C:\Windows\System32\";
Copy-Item "lsort.dll" -Destination "C:\ProgramData\chocolatey\lib\mingw\tools\install\mingw64\x86_64-w64-mingw32\lib\";
Pause;