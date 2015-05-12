#!/bin/bash

# cd to here
cd "$(dirname "$0")"

export PREFERRED_STANDALONE=~/SDK/ndk-standalone-19-tadp

PATH=$PREFERRED_STANDALONE/bin:$PATH

cmake \
    -D CMAKE_TOOLCHAIN_FILE=../android_toolchain.cmake \
    -D CMAKE_INSTALL_PREFIX=$PREFERRED_STANDALONE/sysroot/usr \
    -D CMAKE_BUILD_TYPE=Debug \
    -D FREEGLUT_GLES3=ON \
    -D FREEGLUT_BUILD_DEMOS=NO \
    .. \
 && make -j4 && make install && rm -f $PREFERRED_STANDALONE/sysroot/usr/lib/libfreeglut-gles?.so*


