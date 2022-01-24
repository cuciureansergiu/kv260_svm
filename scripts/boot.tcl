proc boot_jtag { } {
    ############################
    # Switch to JTAG boot mode #
    ############################
    targets -set -filter {name =~ "PSU"}
    # update multiboot to ZERO
    mwr 0xffca0010 0x0
    # change boot mode to JTAG
    mwr 0xff5e0200 0x0100
    # reset
    rst -system
}

proc boot_sd { } {
    ############################
    # Switch to SD boot mode #
    ############################
    targets -set -filter {name =~ "PSU"}
    # update multiboot to ZERO
    mwr 0xffca0010 0x0
    # change boot mode to SD
    mwr 0xff5e0200 0xE100
    # reset
    rst -system
    #A53 may be held in reset catch, start it with "con"
    after 2000
    con
}

proc boot_qspi { } {
    ############################
    # Switch to QSPI boot mode #
    ############################
    targets -set -filter {name =~ "PSU"}
    # update multiboot to ZERO
    mwr 0xffca0010 0x0
    # change boot mode to QSPI
    mwr 0xff5e0200 0x2100
    # reset
    rst -system
    #A53 may be held in reset catch, start it with "con"
    after 2000
    con
}

proc boot_emmc { } {
    ############################
    # Switch to emmc boot mode #
    ############################
    targets -set -nocase -filter {name =~ "PSU"}
    stop
    # update multiboot to ZERO
    mwr 0xffca0010 0x0
    # change boot mode to EMMC
    mwr 0xff5e0200 0x6100
    # reset
    rst -system
    #A53 may be held in reset catch, start it with "con"
    after 2000
    con
}

proc boot_usb { } {
    ############################
    # Switch to usb0 boot mode #
    ############################
    targets -set -nocase -filter {name =~ "PSU"}
    stop
    # update multiboot to ZERO
    mwr 0xffca0010 0x0
    # change boot mode to EMMC
    mwr 0xff5e0200 0x7100
    # reset
    rst -system
    #A53 may be held in reset catch, start it with "con"
    after 2000
    con
}