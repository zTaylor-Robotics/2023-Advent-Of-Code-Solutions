#!/bin/bash

cmake -S . -B build

make -C build

cd build/Debug
./solution
cd ../..