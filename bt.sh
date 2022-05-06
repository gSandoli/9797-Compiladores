#! /bin/sh

rm -r build/
mkdir build
cd build
cmake ..
make
cd ..
# ./sc tests/test2.s
