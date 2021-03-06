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
  g++ -std=c++2a -isystem ${GTEST_DIR}/include -I${GTEST_DIR} \
      -pthread -c ${GTEST_DIR}/src/gtest-all.cc
  ar -rv libgtest.a gtest-all.o
fi

# Build tests
echo "Building unit tests"
g++-8 -Wall -Werror -std=c++2a -fconcepts -fopenmp -isystem $GTEST_DIR/include -Iinclude \
    -pthread test/matrix_test.cpp libgtest.a -o matrix_test

# Run tests
echo "Running unit tests"
./matrix_test
