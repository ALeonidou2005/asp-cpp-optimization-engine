#!/bin/bash

clear

# Check if built
EXECUTABLE_NAME="artifacts/macOS/tester"
if [ ! -f "$EXECUTABLE_NAME" ]; then
    echo "ERROR: Built not found."
    echo "-> Run './build.sh' first to compile the project."
    exit 1
fi

# Run the test program
echo "Running ASP Optimization Engine..."
echo
run_command="${EXECUTABLE_NAME} ${1}"
./$run_command

echo
echo