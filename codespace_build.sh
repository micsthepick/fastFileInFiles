#!/bin/bash -e

# Define project root directory
PROJECT_ROOT=$(pwd)

echo "Project root directory: ${PROJECT_ROOT}"

# Function to build a specific architecture
build_arch() {
  ARCH=$1
  BUILD_DIR="${PROJECT_ROOT}/build_${ARCH}"

  echo "Attempting to build for ${ARCH} in directory ${BUILD_DIR}..."

  # Ensure the build directory is clean and start from scratch
  echo "Removing existing build directory..."
  rm -rf "${BUILD_DIR}"

  echo "Creating new build directory..."
  mkdir -p "${BUILD_DIR}"

  # Enter the build directory
  echo "Entering build directory..."
  cd "${BUILD_DIR}"

  # Configure CMake for the specific architecture
  echo "Configuring CMake for ${ARCH}..."
  cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw.cmake -DTARGET_ARCH="${ARCH}"

  # Build the project
  echo "Building..."
  cmake --build . --config Release

  # Return to the project root directory
  echo "Returning to project root directory..."
  cd "${PROJECT_ROOT}"
  echo "Build for ${ARCH} completed."
}

# Build for x86 (32-bit)
build_arch x86_32

# Build for x64 (64-bit)
build_arch x86_64

echo "All builds completed."
