#!/bin/sh

cmake \
-G "Unix Makefiles" \
-S . \
-B build \
-DTEST_DEBUG=OFF