#!/bin/bash

BUILD_DIR="out/Release"

mkdir -p $BUILD_DIR
cd $BUILD_DIR

cmake -DCMAKE_BUILD_TYPE=Release ../..
echo "Building the Project...."
cmake --build .

cd ../..

echo "Script has finished. Press Enter to exit..."
read  # waits for Enter key press