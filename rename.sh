#!/bin/sh

mv ui/{$1,$2}.ui
mv include/{$1,$2}.h
mv src/{$1,$2}.cpp

find src include ui CMakeLists.txt -exec sed -i "s/$1/$2/g" {} \;
