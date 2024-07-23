#!/bin/sh

rm -rf build

# configure
cmake \
-G "Unix Makefiles" \
-S . \
-B build \
-DTEST_DEBUG=ON \
-DUNIT_TEST=ON

# build
cd build ; make

# run
cd build/tests ; ctest -VV