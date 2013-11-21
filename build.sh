#!/bin/bash

BUILD_DIR="$(pwd)/build"

cd "$BUILD_DIR"

# remove previous build file except .giignore
ls ./* | grep -v .gitignore | xargs rm -rf

#cmake .. && make all
