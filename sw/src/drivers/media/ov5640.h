#include <xparameters.h>

#define OV5640_IIC_DEVICE_ID    XPAR_XIICPS_0_DEVICE_ID
#define OV5640_IIC_SCLK_RATE    (100 * 1000) // 100 KHz
#define OV5640_IIC_ADDR         0x3C
#define OV5640_IIC_SWITCH_ADDR  0x74
#define OV5640_IIC_BUS          0x04

#define OV5640_DEVICE_ID        0x78

int ov5640_init();
int ov5640_load_config(int awb);
int ov5640_ping();
int ov5640_sw_reset();
