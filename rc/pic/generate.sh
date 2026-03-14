#!/bin/bash

set -e -u

xsize=280
size=${xsize}x1024
x=10
rm -f vd_r*.png
rm -f vodi_r*.png

name=vodi_r2_2
convert part1.png -crop ${size}+${x}+10 +repage ${name}.png
convert ${name}.png -trim ${name}.png
let x+=${xsize}

name=vodi_r1_2
convert part1.png -crop ${size}+${x}+10 +repage ${name}.png
convert ${name}.png -trim ${name}.png
let x+=${xsize}

name=vodi_r1_2_r2_2
convert part1.png -crop ${size}+${x}+10 +repage ${name}.png
convert ${name}.png -trim ${name}.png
let x+=${xsize}

name=vodi
convert part1.png -crop ${size}+${x}+10 +repage ${name}.png
convert ${name}.png -trim ${name}.png
let x+=${xsize}

name=led
convert part1.png -crop ${size}+${x}+10 +repage ${name}.png
convert ${name}.png -trim ${name}.png
let x+=${xsize}

x=10
let x+=${xsize}*4

name=shunt
convert part2.png -crop ${size}+${x}+10 +repage ${name}.png
convert ${name}.png -trim ${name}.png
let x+=${xsize}




echo "[$0] fin.sh"

#--- Fin ----------------------------------------------------------------------
