VIVADO_SCRIPT:=${ROOT_DIR}/hw/project.tcl
XSA:=${ROOT_DIR}/hw/vivado/${NAME}.xsa 

.SILENT: hw/all hw/project hw/clean hw/fclean
.PHONY: hw/all hw/debug

hw/all: ${XSA}

${XSA}: deps	
	mkdir -p ${ROOT_DIR}/hw/vivado
	vivado -mode batch -notrace -source ${VIVADO_SCRIPT}
	cp ${XSA} bin/

hw/debug:
	vivado ${ROOT_DIR}/hw/vivado/${NAME}/.xpr

hw/clean:
	rm -rf vivado*.jou vivado*.log vivado.log .Xil *.xpe

hw/fclean:
	rm -rf ${ROOT_DIR}/hw/vivado
