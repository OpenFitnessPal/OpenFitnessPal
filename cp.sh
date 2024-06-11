#!/bin/sh

cp ui/{$1,$2}.ui
cp include/{$1,$2}.h
cp src/{$1,$2}.cpp

for i in ui/$2.ui include/$2.h src/$2.cpp
do
    sed -i "s/$1/$2/g" $i
done
