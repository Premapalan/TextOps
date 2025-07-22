#!/bin/bash
set -e

BUILD_DIR="out/Release"

# Check for required tools
command -v cmake >/dev/null || { echo "CMake not found"; exit 1; }
command -v ninja >/dev/null || { echo "Ninja not found"; exit 1; }

# Create and enter build dir
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Configure with CMake
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ../..

# Build
echo "🔨 Building the project..."
cmake --build .

# Go back
cd -