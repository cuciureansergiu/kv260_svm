############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
open_project kv260_3d_svm
set_top sobel
add_files ../src/data/image.h -cflags "-std=c++14"
add_files ../src/filters/sobel/sobel.h -cflags "-std=c++14"
add_files ../src/filters/sobel/sobel.cpp -cflags "-std=c++14"
add_files -tb ../src/tb_sobel.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xck26-sfvc784-2LV-c}
create_clock -period 10 -name default
#source "./kv260_3d_svm/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
