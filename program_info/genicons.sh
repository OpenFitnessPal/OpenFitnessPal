#/bin/bash

# ICO

inkscape -w 16 -h 16 -o OpenFitnessPal_16.png OpenFitnessPal.svg
inkscape -w 24 -h 24 -o OpenFitnessPal_24.png OpenFitnessPal.svg
inkscape -w 32 -h 32 -o OpenFitnessPal_32.png OpenFitnessPal.svg
inkscape -w 48 -h 48 -o OpenFitnessPal_48.png OpenFitnessPal.svg
inkscape -w 64 -h 64 -o OpenFitnessPal_64.png OpenFitnessPal.svg
inkscape -w 128 -h 128 -o OpenFitnessPal_128.png OpenFitnessPal.svg

convert OpenFitnessPal_128.png OpenFitnessPal_64.png OpenFitnessPal_48.png OpenFitnessPal_32.png OpenFitnessPal_24.png OpenFitnessPal_16.png OpenFitnessPal.ico

rm -f OpenFitnessPal_*.png

inkscape -w 1024 -h 1024 -o OpenFitnessPal_1024.png OpenFitnessPal.svg

png2icns OpenFitnessPal.icns OpenFitnessPal_1024.png

rm -f OpenFitnessPal_*.png
