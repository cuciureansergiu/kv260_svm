source $::env(ROOT_DIR)/sw/vitis/$::env(NAME)/_ide/psinit/psu_init.tcl
source $::env(ROOT_DIR)/scripts/boot.tcl

set proj_name $::env(NAME)
set proj_dir $::env(ROOT_DIR)/sw/vitis
set hw $proj_dir/$proj_name.xsa
set bitstream $::proj_dir/system/hw/$::proj_name.bit
set fsbl $::proj_dir/system/export/system/sw/system/boot/fsbl.elf
set app $::proj_dir/$proj_name/Debug/$proj_name.elf

proc _uplaod_app {} {
        targets -set -nocase -filter {name =~ "*A53*#0"}
        rst -processor
        dow $::app
        configparams force-mem-access 0
}

proc _set_fsbl {} {
        targets -set -nocase -filter {name =~ "*A53*#0"}
        rst -processor
        dow $::fsbl
        set bp_7_10_fsbl_bp [bpadd -addr &XFsbl_Exit]
        con -block -timeout 60
        bpremove $bp_7_10_fsbl_bp
}


proc _init_cpua {} {
        targets -set -nocase -filter {name =~ "PSU"}
        psu_init
        psu_post_config
        psu_ps_pl_reset_config
        psu_ps_pl_isolation_removal
}

proc _upload_bitstream {} {
	targets -set -filter {name =~ "PSU"}
	fpga -file [file normalize $::bitstream]
}

proc _cpu_reset {} {
        targets -set -nocase -filter {name =~"APU*"}
        rst -system
        after 3000
}

connect

boot_jtag
_cpu_reset
_upload_bitstream
_init_cpua
_set_fsbl
_uplaod_app
targets -set -nocase -filter {name =~ "*A53*#0"}
bpadd -addr &main
con
