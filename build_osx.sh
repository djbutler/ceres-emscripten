#!/bin/bash

# configure the OSX build
mkdir -p build/osx
cd build/osx
cmake -DCMAKE_BUILD_TYPE=Release -DCeres_DIR=/usr/local/share/Ceres -DGLOG_LIBRARY=/usr/local/lib/libglog.a ../..
make

