#! /bin/sh

cd build
cmake ..
make
cd ..
./sc test.s