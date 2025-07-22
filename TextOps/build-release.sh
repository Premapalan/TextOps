#!/bin/bash

BUILD_DIR="out/Release"

mkdir -p $BUILD_DIR
cd $BUILD_DIR

cmake -DCMAKE_BUILD_TYPE=Release ../..
echo "Building the Project...."
cmake --build .

cd ../..