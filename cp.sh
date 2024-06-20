#!/bin/sh

cp ui/$1/{$2,$3}.ui
cp include/$1/{$2,$3}.h
cp src/$1/{$2,$3}.cpp

for i in ui/$1/$3.ui include/$1/$3.h src/$1/$3.cpp
do
    sed -i "s/$2/$3/g" $i
done
