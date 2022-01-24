#include <xiicps.h>

#include "../../../util/debug.h"
#include "../../../util/error.h"

static struct t_sys_iic {
    XIicPs_Config   *config;
    XIicPs          controller;
    unsigned char   dev_addr;
} sys_iic;

int iic_init(int device_id, int iic_rate, int addr)
{
	int status;

	sys_iic.config = XIicPs_LookupConfig(device_id);
    if (sys_iic.config == NULL) {
        err("Iic controller not found");
        return XST_FAILURE;
    }

    status = XIicPs_CfgInitialize(&sys_iic.controller, 
                                  sys_iic.config, 
                                  sys_iic.config->BaseAddress);
    if (status != XST_SUCCESS) {
        err("Failed to configure iic controller");
        return status;
    }

    status = XIicPs_SetSClk(&sys_iic.controller, iic_rate);
    if (status != XST_SUCCESS) {
        err("Iic controller settings are invalid");
        return status;
    }
    
    sys_iic.dev_addr = addr;

    return status;
}

static int iic_write(unsigned char *buff, int len)
{

    return XIicPs_MasterSendPolled(&sys_iic.controller, buff,
                                   len, sys_iic.dev_addr);

}
static int iic_read(unsigned char *buff, int len)
{

    return XIicPs_MasterRecvPolled(&sys_iic.controller, buff,
                                   len, sys_iic.dev_addr);

}

int iic_write8(unsigned char val)
{
    unsigned char buff[1] = { val };

    return iic_write(buff, 1);
}

int iic_write16(unsigned char reg, unsigned char val)
{
    unsigned char buff[2] = {
        reg,
        val
    };

    return iic_write(buff, 2);
}

int iic_write24(unsigned short reg, unsigned char val)
{
    unsigned char buff[3] = {
        ((reg >> 8) & 0xff),
        (reg & 0xff),
        val
    };

    return iic_write(buff, 3);
}

int iic_write16read8(unsigned short reg, unsigned char *val)
{
    int status;

    status = iic_write16(((reg >> 8) & 0xFF), (reg & 0xFF));
    if (status != XST_SUCCESS)
        return status;

    return iic_read(val, 1);
}

int iic_write_dev(unsigned char addr, unsigned char val)
{
    unsigned char init_addr = sys_iic.dev_addr;
    int status;

    sys_iic.dev_addr = addr;

    status = iic_write8(val);
    if (status != XST_SUCCESS)
        return status;

    sys_iic.dev_addr = init_addr;

    return status;
}
