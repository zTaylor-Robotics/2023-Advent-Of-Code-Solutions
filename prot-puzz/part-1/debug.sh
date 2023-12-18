#!/bin/bash

cmake -S . -B build -G "Ninja Multi-COnfig"

cd build

ninja

cd Debug

./solution

cd ../..