#!/bin/bash
# this file is used to auto-update .ts file.

cd $(dirname $0) || true

fileNames=$(ls ./*.ts)

for fileName in $fileNames ; do
    /usr/lib/qt5/bin/lupdate ../ -recursive -no-obsolete -ts $fileName
done
