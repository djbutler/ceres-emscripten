#!/bin/bash

# configure the JS build
mkdir -p build/js
cd build/js
emconfigure cmake -DCMAKE_BUILD_TYPE=Release -DCeres_DIR=/Users/djbutler/software/ceres-js/share/Ceres ../..
emmake make
# emmake make VERBOSE=1 

# configure the OSX build
mkdir -p build/osx
cd build/osx
cmake -DCMAKE_BUILD_TYPE=Release -DCeres_DIR=/usr/local/share/Ceres -DGLOG_LIBRARY=/usr/local/lib/libglog.a ../..
make

