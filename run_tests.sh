#!/bin/bash

set -e

if [ -z "$GTEST_DIR" ]
then
  echo "Please set \$GTEST_DIR to location of googletest directory"
  exit 1
fi

# Build googletest if not available
if [ ! -f libgtest.a ]
then
  echo "Building googletest"
  g++ -std=c++11 -isystem ${GTEST_DIR}/include -I${GTEST_DIR} \
      -pthread -c ${GTEST_DIR}/src/gtest-all.cc
  ar -rv libgtest.a gtest-all.o
fi

# Build tests
echo "Building unit tests"
g++-8 -std=c++17 -isystem $GTEST_DIR/include \
    -pthread matrix_test.cpp libgtest.a -o matrix_test

# Run tests
./matrix_test
