#include "../../drivers/interface/iic/iic.h"
#include "../../util/error.h"
#include "ov5640.h"
#include "ov5640_fw.h"
#include "sleep.h"

static int ov5640_iic_init()
{

    int status;
    
    status = iic_init(OV5640_IIC_DEVICE_ID, OV5640_IIC_SCLK_RATE,
                      OV5640_IIC_ADDR);
    if (IS_ERR(status)) {
        err("OV5640 not found on iic bus");
        return status;
    }

    status = iic_write_dev(OV5640_IIC_SWITCH_ADDR, OV5640_IIC_BUS);
    if (IS_ERR(status)) {
        err("Could not set the OV5640 iic switch");
        return status;
    }
    return 0;
}

int ov5640_ping()
{
    unsigned char iic_device_id;
    int status;

    info("Ping ov5640 on the iic bus");
    status = iic_write16read8(0x3100, &iic_device_id);
    if (IS_ERR(status))
        return status;

    if (iic_device_id != OV5640_DEVICE_ID) {
        err("Can't find ov5640");
        return ERROR;
    }

    info("Camera detected");
    return 0;
}

int ov5640_init()
{
    int status;

    status = ov5640_iic_init();
    if (IS_ERR(status))
        return status;

    status = ov5640_sw_reset();
    if (IS_ERR(status))
        return status;

    //TODO: check this sleep value
	usleep(1000000);

	status = ov5640_ping();
    if (IS_ERR(status))
        return status;

    status = ov5640_load_config(0);
    if (IS_ERR(status))
        return status;

    return status;
}

int ov5640_load_config(int awb)
{
    int status, i;

    for (i = 0; i < 63; i++) {
        //TODO: update the init table
        status = iic_write24(cfg_init[i][0], cfg_init[i][1]);
        if (IS_ERR(status)) {
            //TODO: update message
            err("FW: init cfg failed");
            return status;
        }
    }

    if(awb == 1)
        for (i = 0; i < 19; i++) {
            //TODO: update the init table
            status = iic_write24(cfg_simple_awb[i][0], cfg_simple_awb[i][1]);
            if (IS_ERR(status)) {
                //TODO: update message
                err("FW: awb cfg failed");
                return status;
            }
        }

    for (i = 0; i < 38; i++) {
        //TODO: update the init table
        status = iic_write24(cfg_720p_60fps[i][0], cfg_720p_60fps[i][1]);
        if (IS_ERR(status)) {
            //TODO: update message
            err("FW: res cfg failed");
            return status;
        }
    }
    return 0;
}

int ov5640_sw_reset()
{
    int status;

    //TODO: remove magic numbers
    status = iic_write24(0x3103, 0x11);
    if (IS_ERR(status))
        return status;

    status = iic_write24(0x3108, 0x82);
    if (IS_ERR(status))
        return status;

	usleep(1000000);

    return status;
}
// static int ov5640_set_resolution(enum ov5640_resolution mode) {

// }
