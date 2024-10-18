#!/bin/bash

echo "Setting up the environment..."

# Bağımlılıkları indir (V8, libuv gibi)
# Örnek: V8 veya libuv indirmek için buraya kod eklenebilir

# Projeyi derleme
cd ../my-runtime/build
cmake ..
make

echo "Build complete!"
