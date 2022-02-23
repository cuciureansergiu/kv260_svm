export ROOT_DIR JOBS NAME PART

JOBS:=2
NAME:=kv260_3d_svm
PART:=xck26-sfvc784-2LV-c
ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

include hw/hw.mk
include hls/hls.mk
include sw/sw.mk

.SILENT: test deps clean fclean
.PHONY: deps all

deps:
	./scripts/deps.sh

all: deps hls/all hw/all sw/all

clean: hw/clean sw/clean
	rm -rf .Xil

fclean: clean hw/fclean sw/fclean
	rm -rf bin/*