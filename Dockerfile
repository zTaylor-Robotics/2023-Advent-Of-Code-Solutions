FROM ubuntu:latest
LABEL Description="Build environment"

RUN apt update
RUN apt install -y git gnupg gpg lsb-release make ninja-build software-properties-common vim wget curl

RUN wget https://apt.llvm.org/llvm.sh
RUN chmod u+x llvm.sh
RUN ./llvm.sh 17

RUN wget https://github.com/Kitware/CMake/releases/download/v3.28.1/cmake-3.28.1-linux-x86_64.sh
RUN chmod u+x cmake-3.28.1-linux-x86_64.sh
RUN echo y | ./cmake-3.28.1-linux-x86_64.sh

RUN ln -s /cmake-3.28.1-linux-x86_64/bin/cmake /usr/bin/cmake
RUN ln -s /cmake-3.28.1-linux-x86_64/bin/ccmake /usr/bin/ccmake
RUN ln -s /cmake-3.28.1-linux-x86_64/bin/cmake-gui /usr/bin/cmake-gui
RUN ln -s /cmake-3.28.1-linux-x86_64/bin/cpack /usr/bin/cpack
RUN ln -s /cmake-3.28.1-linux-x86_64/bin/ctest /usr/bin/ctest

RUN ln -s /usr/bin/clang++-17 /usr/bin/clang++
RUN ln -s /usr/bin/clang-17 /usr/bin/clang
RUN ln -s /usr/bin/clangd-17 /usr/bin/clangd
RUN ln -s /usr/bin/clangd-cpp-17 /usr/bin/clang-cpp

RUN git clone https://SH3P-Productions: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@github.com/SH3P-Productions/get_aoc_input.git
RUN chmod u+x /get_aoc_input/get_input.sh
RUN ./get_aoc_input/get_input.sh

RUN chmod u+x /get_aoc_input/debug.sh
RUN ln -s /get_aoc_input/debug.sh /usr/bin/debug

RUN echo complete