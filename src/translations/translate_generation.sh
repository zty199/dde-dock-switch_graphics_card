#!/bin/bash
# this file is used to auto-generate .qm file from .ts file.

cd $(dirname $0)

fileNames=$(ls ./*.ts)

for fileName in $fileNames ; do
    /usr/lib/qt5/bin/lrelease $fileName
done
