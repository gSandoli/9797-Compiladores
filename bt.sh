#! /bin/sh

rm -r build/
mkdir build
cd build
cmake ..
make
cd ..
./sc test2.s
