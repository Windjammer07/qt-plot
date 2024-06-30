#!/bin/sh

[ ! -f src/qt-plot.pro ] && echo "File \"./src/qt-plot.pro\" not fount. Call build script from project root" && exit 1

mkdir bin
cd bin

qmake ../src/qt-plot.pro

make

make clean

rm Makefile
rm .qmake.stash

cd ..

