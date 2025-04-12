#!/bin/bash
set -e

echo "Starting build..."

# Go to the project folder
cd /project/dragon-tiger

# Create a test Tiger file with a simple print statement
echo 'print("Hello World!\n")' > hello.tig

echo "Running compiler..."

# Compile the Tiger file to an object file
src/driver/dtiger -o hello.o hello.tig

echo "Linking..."

# Link the object file with the runtime library to create an executable
clang++ hello.o src/runtime/posix/libruntime.a -o hello -no-pie

echo "Running compiled program:"

# Run the compiled program
./hello
