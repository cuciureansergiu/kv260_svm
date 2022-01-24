source $::env(ROOT_DIR)/scripts/boot.tcl

set proj_name $::env(NAME)
set proj_dir $::env(ROOT_DIR)/sw/vitis
set hw $proj_dir/$proj_name.xsa

set cpu psu_cortexa53_0

proc project {} {
        setws $::proj_dir

        platform create                                 \
                -name system                            \
                -hw $::hw
        
        domain create                                   \
                -name cortex_a53                        \
                -os standalone                          \
                -proc psu_cortexa53_0
        
        # domain create
        #         -name cortexr5                          \
        #         -os standalone                          \
        #         -proc psu_cortexr5_0

        app create                                      \
                -name $::proj_name                      \
                -platform system                        \
                -domain cortex_a53                      \
                -sysproj apu                            \
                -template {Empty Application(C)}

        # app create                                      \
        #         -name $::proj_name_rpu                  \
        #         -platform system                        \
        #         -domain cortexr5                        \
        #         -sysproj $::proj_name                   \
        #         -template {Empty Application(C)}
	
        app config -name $::proj_name libraries $::env(LIB)

        platform active system
        platform generate

	[exec rm -rf $::proj_dir/$::proj_name/src]
        [exec ln -s $::env(ROOT_DIR)/sw/src $::proj_dir/$::proj_name/]
        app build $::proj_name

        # app create					\
        #         -name $::proj_name			\
        #         -hw $::hw				\
        #         -proc $::cpu				\
        #         -os standalone			\
        #         -template  {Empty Application(C)}
        
        # app build $::proj_name_rpu
}

[lindex $argv 0]
