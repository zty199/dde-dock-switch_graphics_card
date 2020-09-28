#!/bin/sh

# 获取系统语言环境 | Get system locale
LANG=$(locale | grep LANGUAGE | cut -d '=' -f 2 | cut -d '_' -f 1)
if [ "$LANG" != "zh" ] ; then
    LANG="en"
fi

echo $LANG
