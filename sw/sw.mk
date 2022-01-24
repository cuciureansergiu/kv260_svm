export LIBS

LIBS:=m
VITIS_SCRIPT:=${ROOT_DIR}/sw/project.tcl

define cmd
	xsct $(VITIS_SCRIPT)$(1)
endef

.PHONY: sw
.SILENT: sw sw/clean sw/fclean

sw: deps
	mkdir -p ${ROOT_DIR}/sw/vitis
	cp ${ROOT_DIR}/hw/vivado/${NAME}.xsa ${ROOT_DIR}/sw/vitis/
	$(call cmd, project)
	cp ${ROOT_DIR}/sw/vitis/${NAME}/Debug/*.elf ${ROOT_DIR}/bin/debug.elf

sw/build:
	make -C ${ROOT_DIR}/sw/vitis/${NAME}/Debug all

sw/apuinit:
	xsdb ${ROOT_DIR}/scripts/debug.tcl


sw/clean: 
	rm -rf IDE.log .analytics .Xil

sw/fclean:
	rm -rf ${ROOT_DIR}/sw/vitis 