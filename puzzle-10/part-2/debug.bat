@echo off

cmake -S . -B build -G "Ninja Multi-Config"

cd build

ninja

cd Debug

solution.exe

cd ../..