#!/bin/bash

clear

echo "Building ASP Optimization Engine..."
echo

# Create artifacts directory if it doesn't exist
mkdir -p artifacts/macOS

# Set file names
MAIN_PROGRAM_NAME="src/scheduler.cpp"
DLL_NAME="artifacts/macOS/scheduler.dylib"
TEST_PROGRAM_NAME="src/tester.cpp"
EXECUTABLE_NAME="artifacts/macOS/tester"

# Compile the DLL
echo "Compiling optimization engine library..."
g++ -dynamiclib -o $DLL_NAME $MAIN_PROGRAM_NAME -std=c++17 -O2 -fPIC
if [ $? -ne 0 ]; then
    echo "ERROR: Failed to compile shared library!"
    exit 1
fi
echo "=> Library compiled successfully"

# Compile the test program
echo "Compiling test program..."
g++ -o $EXECUTABLE_NAME $TEST_PROGRAM_NAME -std=c++17 -O2 -ldl
if [ $? -ne 0 ]; then
    echo "ERROR: Failed to compile test program!"
    exit 1
fi
echo "=> Test program compiled successfully"

echo
echo "=> Build Complete"
echo
echo "-> Run './run.sh [test_number]' to test the engine."
echo "-> Example: './run.sh 1' runs test case input1.txt"
echo