VIVADO_SCRIPT:=${ROOT_DIR}/hw/project.tcl

.SILENT: hw hw/project hw/clean hw/fclean

hw: deps
	mkdir -p ${ROOT_DIR}/hw/vivado
	vivado -mode batch -notrace -source ${VIVADO_SCRIPT}
	cp ${ROOT_DIR}/hw/vivado/${NAME}.xsa bin/

hw/debug:
	vivado ${ROOT_DIR}/hw/vivado/${NAME}/.xpr

hw/clean:
	rm -rf vivado*.jou vivado*.log vivado.log .Xil *.xpe

hw/fclean:
	rm -rf ${ROOT_DIR}/hw/vivado