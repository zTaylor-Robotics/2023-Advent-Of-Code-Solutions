@echo off

cmake -DCMAKE_CXX_FLAGS="-isystem C:\ProgramData\chocolatey\lib\curl\tools\curl-8.5.0_1-win64-mingw\include" -S . -B build -G "Ninja Multi-Config" -DCURL_INCLUDE_DIR="C:\ProgramData\chocolatey\lib\curl\tools\curl-8.5.0_1-win64-mingw\include" -DCURL_LIBRARY="C:\ProgramData\chocolatey\lib\curl\tools\curl-8.5.0_1-win64-mingw\lib"

cd build

ninja -f build-Release.ninja

cd ..