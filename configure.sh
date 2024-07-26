#!/bin/sh

# configure
cmake \
  -G "Unix Makefiles" \
  -S . \
  -B build \
  -DTEST_DEBUG=ON \
  -DUNIT_TEST=ON