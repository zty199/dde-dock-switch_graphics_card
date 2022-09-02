#!/bin/bash
# this file is used to auto-update .ts file.

cd $(dirname $0)

ts_list=$(ls ./*.ts)

for ts in "${ts_list[@]}"
do
#    printf "\nprocess ${ts}\n"
    lupdate ./src -recursive -no-obsolete -ts "${ts}"
done
