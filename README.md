freeglut_hiit
=============

HIIT version for freeglut with modifications for Android.

For general information about freeglut see README.


## Building
- Install the Android NDK
    - http://developer.android.com/tools/sdk/ndk/index.html
        - (assume here that NDK is installed in ~/SDK/android-ndk)

- Export a cross compiler from the NDK
    $ ~/SDK/android-ndk/build/tools/make-standalone-toolchain.sh \
         --platform=android-14 \
         --install-dir=~/SDK/ndk-standalone-14

- Switch to cross compile directory and run rebuild script
    $ cd <path to freeglut_hiit>
    $ cd cross-android-gles2
    $ ./rebuild.sh


## Usage
TODO
