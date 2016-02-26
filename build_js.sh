#!/bin/bash

# configure the JS build
source /Users/djbutler/software/emsdk_portable/emsdk_env.sh
mkdir -p build/js
cd build/js
emconfigure cmake -DEMBIND=ON -DCMAKE_BUILD_TYPE=Release -DCeres_DIR=/Users/djbutler/software/ceres-js/share/Ceres ../..
emmake make
#emmake make VERBOSE=1 

