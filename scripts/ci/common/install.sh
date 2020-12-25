#!/bin/bash

git clone --recursive https://github.com/qt/qtbase.git
cd qtbase
mkdir build && cd build
cmake .. -G Ninja
cmake --build . --parallel
sudo cmake --install .
