#! /bin/sh

rm -r build/
mkdir build
cd build
cmake ..
make
cd ..
./sc -i test2.s
