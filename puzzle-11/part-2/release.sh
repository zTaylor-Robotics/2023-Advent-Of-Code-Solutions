#!/bin/bash

cmake -S . -B build -G "Ninja Multi-Config"

cd build

ninja -f build-Release.ninja

cd Release

./solution

cd ../..