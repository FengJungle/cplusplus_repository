mkdir build
cd build
cmake -G "MinGW Makefiles" ..
make main
move main.exe ../
cd ..
