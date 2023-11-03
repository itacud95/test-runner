#!/bin/bash

# add any argument to clean builddir
if [ $# -gt 0 ]; then 
    if [ -d build ]; then
        rm -r build
    fi
fi

cmake -Bbuild && \
cmake --build build -j8 && \
./build/main
