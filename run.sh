#! /bin/sh

rm -r output/
make build
./sc -i -s tests/test2.s
