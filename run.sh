#!/bin/sh

rm -f build;

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
cd build ; ./sql-studio.app/Contents/MacOS/sql-studio