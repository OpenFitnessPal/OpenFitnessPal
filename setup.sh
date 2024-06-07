#!/bin/sh
for i in $@
do
    mv $i.ui ui/setup
    mv $i.h include/setup
    mv $i.cpp src/setup
done
