#!/bin/sh
mkdir -p {ui,include,src}/$1

for i in ${@:2}
do
    mv $i.ui ui/$1
    mv $i.h include/$1
    mv $i.cpp src/$1
done
