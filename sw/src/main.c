#include "drivers/media/ov5640.h"
#include "drivers/media/vtc.h"
#include "drivers/dma/vdma.h"

#include "sleep.h"
#include "math.h"

#include "xil_cache.h"
#include "xv_demosaic.h"
#include "xv_gamma_lut.h"

#define DEMO_MAX_FRAME (720*1280)
#define DEMO_STRIDE (1280*3)
#define DISPLAY_NUM_FRAMES 1

XV_demosaic cfa;
XV_gamma_lut gamma_inst;

extern u32 frameBuf[DISPLAY_NUM_FRAMES][DEMO_MAX_FRAME];
unsigned short gamma_reg[1024];

void gamma_calc(float gamma_val)
{
	int i;
	for (i = 0; i < 256; i++)
	{
		gamma_reg[i] = (pow((i / 256.0), (1 / gamma_val)) * 256.0);
	}
}

int main()
{
	int status;

	status = ov5640_init();
	if (status < 0)
		return status;


	status = vdma_init(0, video_modes[v_1280x720].height, video_modes[v_1280x720].width);
	if (status < 0)
		return status;

	status = XV_demosaic_Initialize(&cfa, XPAR_V_DEMOSAIC_0_DEVICE_ID);
	//	 XV_demosaic_Set_HwReg_width(&cfa, video_modes[v_1280x720].width);
	//	 XV_demosaic_Set_HwReg_height(&cfa, video_modes[v_1280x720].height);
	 XV_demosaic_Set_HwReg_width(&cfa, 1280);
	 XV_demosaic_Set_HwReg_height(&cfa, 720);
	 XV_demosaic_Set_HwReg_bayer_phase(&cfa, 0x03);
	 XV_demosaic_EnableAutoRestart(&cfa);
	 XV_demosaic_Start(&cfa);

	 gamma_calc(1.2);
	 XV_gamma_lut_Initialize(&gamma_inst, XPAR_V_GAMMA_LUT_0_DEVICE_ID);
	 XV_gamma_lut_Set_HwReg_width(&gamma_inst, 1280);
	 XV_gamma_lut_Set_HwReg_height(&gamma_inst, 720);
	 XV_gamma_lut_Set_HwReg_video_format(&gamma_inst, 0x00);
	 XV_gamma_lut_Write_HwReg_gamma_lut_0_Bytes(&gamma_inst, 0, (int *)gamma_reg, 512);
	 XV_gamma_lut_Write_HwReg_gamma_lut_1_Bytes(&gamma_inst, 0, (int *)gamma_reg, 512);
	 XV_gamma_lut_Write_HwReg_gamma_lut_2_Bytes(&gamma_inst, 0, (int *)gamma_reg, 512);
	 XV_gamma_lut_Start(&gamma_inst);
	 XV_gamma_lut_EnableAutoRestart(&gamma_inst);

	ov5640_ping();
//	ov5640_sw_reset();
//	usleep(1000000);
//	ov5640_load_config(1);

	vdma_start();
	Xil_DCacheFlush();
	int a;
	while (1)
	{
		a = 1;
	}

	cleanup_platform();
	return 0;
}
