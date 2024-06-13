#!/bin/sh

mv ui/$1/{$2,$3}.ui
mv include/$1/{$2,$3}.h
mv src/$1/{$2,$3}.cpp

find src include ui CMakeLists.txt -type f -exec sed -i "s/$2/$3/g" {} \;
