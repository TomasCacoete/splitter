#!/bin/bash

# Function to clean, configure, and build the project
clean_build() {
    echo "Cleaning the build directory..."
    rm -rf build/*
    cmake -S . -B build -G "MinGW Makefiles"
    cmake --build build
}

# Function to only build the project
build_only() {
    echo "Building the project..."
    cmake --build build
}

# Check the user's input argument
if [ "$1" == "clean" ]; then
    clean_build
elif [ "$1" == "build" ]; then
    build_only
else
    echo "Usage: $0 {clean|build}"
    echo "  clean  - Removes the build directory and rebuilds the project"
    echo "  build  - Builds the project"
    exit 1
fi
