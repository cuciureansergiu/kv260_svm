ARCH?=arm64
LOADADDR?=0x8000
CROSS_COMPILE?=aarch64-linux-gnu-

linux/kernel:
	make -C linux-xlnx xilinx_zynqmp_defconfig


#gcc pipeline.c -lm