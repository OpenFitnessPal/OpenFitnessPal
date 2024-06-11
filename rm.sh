#!/bin/sh

for i in $@
do
    rm ui/$i.ui
    rm include/$i.h
    rm src/$i.cpp
done
