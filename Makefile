export ROOT_DIR JOBS NAME

JOBS:=2
NAME:=kv260_3d_svm
ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

include hw/hw.mk
include sw/sw.mk

.SILENT: test deps clean fclean
.PHONY: deps all

deps:
	./scripts/deps.sh

all: deps hw sw

clean: hw/clean sw/clean
	rm -rf .Xil

fclean: clean hw/fclean sw/fclean
	rm -rf bin/*