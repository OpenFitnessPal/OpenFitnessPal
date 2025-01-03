#/bin/bash

# ICO

inkscape -w 16 -h 16 -o QFRCPal_16.png QFRCPal.svg
inkscape -w 24 -h 24 -o QFRCPal_24.png QFRCPal.svg
inkscape -w 32 -h 32 -o QFRCPal_32.png QFRCPal.svg
inkscape -w 48 -h 48 -o QFRCPal_48.png QFRCPal.svg
inkscape -w 64 -h 64 -o QFRCPal_64.png QFRCPal.svg
inkscape -w 128 -h 128 -o QFRCPal_128.png QFRCPal.svg

convert QFRCPal_128.png QFRCPal_64.png QFRCPal_48.png QFRCPal_32.png QFRCPal_24.png QFRCPal_16.png QFRCPal.ico

rm -f QFRCPal_*.png

inkscape -w 1024 -h 1024 -o QFRCPal_1024.png QFRCPal.svg

png2icns QFRCPal.icns QFRCPal_1024.png

rm -f QFRCPal_*.png
