include ${ROOT_DIR}/hls/src/src.mk

HLS_WORKSPACE:=${ROOT_DIR}/hls/vitis_hls

.PHONY:hls/all
hls/all:
	mkdir -p ${HLS_WORKSPACE}
	cd ${HLS_WORKSPACE}; vitis_hls ${ROOT_DIR}/hls/build.tcl

hls/fclean:
	rm -rf ${HLS_WORKSPACE}

hls/test:
	@echo ${SRCS}