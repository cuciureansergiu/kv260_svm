#open_project -reset proj_2D_convolution_with_linebuffer
# setws hls/vitis
open_project -reset $::env(NAME)

# Add design files
add_files $::env(ROOT_DIR)/hls/src/convolution.cpp -cflags "-I/home/sergiu/Workspace/dev/adaptive-compute/Vitis_Libraries/vision/L1/include -I/home/sergiu/Workspace/dev/adaptive-compute/xil_opencv/install/include -std=c++0x"
add_files $::env(ROOT_DIR)/hls/src/convolution.h -cflags "-I/home/sergiu/Workspace/dev/adaptive-compute/Vitis_Libraries/vision/L1/include -I/home/sergiu/Workspace/dev/adaptive-compute/xil_opencv/install/include -std=c++0x"
# Add test bench & files
add_files -tb $::env(ROOT_DIR)/hls/src/convolution_test.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"

# Set the top-level function
set_top filter11x11_strm

# ########################################################
# Create a solution
open_solution -reset solution1
# Define technology and clock rate
# set_part {xcvu9p-flga2104-2-i}
set_part {xck26-sfvc784-2LV-c} 

create_clock -period 10 -name default

csim_design 
#-ldflags {-L/home/sergiu/Workspace/dev/adaptive-compute/xil_opencv/install/lib -lopencv_core -lopencv_imgcodecs -lopencv_imgproc}
# Set any optimization directives

csynth_design 
#-ldflags {-L/home/sergiu/Workspace/dev/adaptive-compute/xil_opencv/install/lib -lopencv_core -lopencv_imgcodecs -lopencv_imgproc}
# cosim_design
# export_design


###########3wo
# export_design -format ip_catalog
exit

# open_project loop_opts_prj

# set_top filter11x11_strm

# add_files convolution.cpp
# add_files -tb convolution_tb.cpp

# open_solution "solution1"
# set_part {$::env(PART)}
# create_clock -period 6.66 -name default

# csim_design -clean
# csynth_design
# #cosim_design -trace_level none -rtl systemc
# #export_design -format ip_catalog
# exit