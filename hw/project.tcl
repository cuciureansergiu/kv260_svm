set jobs $::env(JOBS)
set ip_repo_path $::env(ROOT_DIR)/hw/ip_repo/
set constraints [exec ls -d $::env(ROOT_DIR)/hw/constraints/]
set proj_name $::env(NAME)
set proj_dir hw/vivado

create_project -name $proj_name -force -dir $::env(ROOT_DIR)/hw/vivado -part $::env(PART)
set_property BOARD_PART [get_board_parts "*:kv260:*" -latest_file_version] [current_project]


# set_property ip_repo_paths $ip_repo_path [current_project]
import_files -fileset constrs_1 $constraints
update_ip_catalog

set design_name $proj_name
create_bd_design $proj_name
current_bd_design $proj_name
set parentCell [get_bd_cells /]
set parentObj [get_bd_cells $parentCell]
current_bd_instance $parentObj
source $::env(ROOT_DIR)/hw/design.tcl
save_bd_design

make_wrapper -files [get_files $proj_dir/${proj_name}.srcs/sources_1/bd/$proj_name/${proj_name}.bd] -top
import_files -force -norecurse $proj_dir/${proj_name}.srcs/sources_1/bd/$proj_name/hdl/${proj_name}_wrapper.v
update_compile_order
set_property top ${proj_name}_wrapper [current_fileset]
update_compile_order -fileset sources_1

save_bd_design
validate_bd_design
update_compile_order -fileset sources_1

launch_runs impl_1 -to_step write_bitstream -jobs $jobs
wait_on_run impl_1

write_hw_platform -fixed -include_bit -force -file $::env(ROOT_DIR)/hw/vivado/$::env(NAME).xsa
