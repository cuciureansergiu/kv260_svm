#!/bin/bash

cmd_list=("vivado" "vitis")
not_found=0

check_deps() {
        for cmd in ${cmd_list[@]}; do
                if ! command -v $cmd &> /dev/null ; then
                        echo "Program $cmd is not in \$PATH"
                        not_found=1
                fi
        done
        return $not_found
}

check_deps
