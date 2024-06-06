#!/bin/sh
for i in $@
do
    mv $i.ui ui
    mv $i.h include
    mv $i.cpp src
done
