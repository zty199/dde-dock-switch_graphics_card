#!/bin/sh

file=$1

if [ "${file##*.}"x = "desktop"x ]
then
    __NV_PRIME_RENDER_OFFLOAD=1 __VK_LAYER_NV_optimus=NVIDIA_only __GLX_VENDOR_LIBRARY_NAME=nvidia $(cat $file | grep "Exec=" | sed "s/^Exec=//" | sed "s/%.//" | sed "s/^\"//g" | sed "s/\" *$//g" | head -n 1)
else
    __NV_PRIME_RENDER_OFFLOAD=1 __VK_LAYER_NV_optimus=NVIDIA_only __GLX_VENDOR_LIBRARY_NAME=nvidia $file
fi
