SRC_DIR:=${ROOT_DIR}/hls/src

SRCS:=	\
	convolution/convolution.cpp				\
	sobel/sobel.cpp
INCS:=	\
	convolution/convolution.h

SRCS:= $(foreach src, ${SRCS}, $(addprefix ${SRC_DIR}/, ${src}))


# add_files $::env(ROOT_DIR)/hls/src/convolution.cpp -cflags "-I/home/sergiu/Workspace/dev/adaptive-compute/Vitis_Libraries/vision/L1/include -I/home/sergiu/Workspace/dev/adaptive-compute/xil_opencv/install/include -std=c++0x"
# add_files $::env(ROOT_DIR)/hls/src/convolution.h -cflags "-I/home/sergiu/Workspace/dev/adaptive-compute/Vitis_Libraries/vision/L1/include -I/home/sergiu/Workspace/dev/adaptive-compute/xil_opencv/install/include -std=c++0x"
# # Add test bench & files
# add_files -tb $::env(ROOT_DIR)/hls/src/convolution_test.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
