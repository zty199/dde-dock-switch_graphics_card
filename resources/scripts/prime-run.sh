#!/bin/sh

FILE=$1

if [ "${FILE##*.}"x = "desktop"x ]; then
	__NV_PRIME_RENDER_OFFLOAD=1 __VK_LAYER_NV_optimus=NVIDIA_only __GLX_VENDOR_LIBRARY_NAME=nvidia $(cat $FILE | grep "Exec=" | sed "s/^Exec=//" | sed "s/%.//" | sed "s/^\"//g" | sed "s/\" *$//g" | head -n 1)
else
	__NV_PRIME_RENDER_OFFLOAD=1 __VK_LAYER_NV_optimus=NVIDIA_only __GLX_VENDOR_LIBRARY_NAME=nvidia $FILE
fi
