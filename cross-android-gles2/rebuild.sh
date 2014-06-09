#!/bin/bash

# cd to here
cd "$(dirname "$0")"

PATH=~/SDK/ndk-standalone-14/bin:$PATH
cmake \
    -D CMAKE_TOOLCHAIN_FILE=../android_toolchain.cmake \
    -D CMAKE_INSTALL_PREFIX=~/SDK/ndk-standalone-14/sysroot/usr \
    -D CMAKE_BUILD_TYPE=Debug \
    -D FREEGLUT_GLES=ON \
    -D FREEGLUT_BUILD_DEMOS=NO \
    .. \
 && make -j4 && make install && rm -f ~/SDK/ndk-standalone-14/sysroot/usr/lib/libfreeglut-gles?.so*

cd -
