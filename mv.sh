#!/bin/sh

mv ui/{.,$2}/$1.ui
mv include/{.,$2}/$1.h
mv src/{.,$2}/$1.cpp

sed -i "s/$1/$2\/$1/g" CMakeLists.txt
find src include ui -type f -exec sed -i "s/$1.h/$2\/$1.h/g" {} \;
