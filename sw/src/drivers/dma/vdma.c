#include <xaxivdma.h>
#include <xaxivdma_i.h>

#include "../../util/debug.h"
#include "../../util/error.h"

#define DEMO_MAX_FRAME (720*1280)
#define DEMO_STRIDE (1280*3)
#define DISPLAY_NUM_FRAMES 1

u32 frameBuf[DISPLAY_NUM_FRAMES][DEMO_MAX_FRAME];
u32 *pFrames[DISPLAY_NUM_FRAMES];

static struct t_sys_vdma {
    XAxiVdma            controller;
    XAxiVdma_Config     *config;
    XAxiVdma_DmaSetup   options;
} sys_vdma;

int vdma_init(int device_id, int height, int width)
{

    int status;

    pFrames[0] = frameBuf[0];

    sys_vdma.config = XAxiVdma_LookupConfig(device_id);
    if (sys_vdma.config == NULL) {
        err("VDMA not found");
        return XST_FAILURE;
    }
    
	status = XAxiVdma_CfgInitialize(&sys_vdma.controller,
                                    sys_vdma.config,
                                    sys_vdma.config->BaseAddress);
	//video = VMODE_1280x720;
	sys_vdma.options.FrameDelay = 0;
	sys_vdma.options.EnableCircularBuf = 1;
	sys_vdma.options.EnableSync = 0;
	sys_vdma.options.PointNum = 0;
	sys_vdma.options.EnableFrameCounter = 0;

	sys_vdma.options.VertSizeInput = height;
	sys_vdma.options.HoriSizeInput = width *3;
	sys_vdma.options.FixedFrameStoreAddr = 0;
	sys_vdma.options.FrameStoreStartAddr[0] = (u32)  pFrames[0];
	sys_vdma.options.Stride = width*3;

	XAxiVdma_DmaConfig(&sys_vdma.controller, XAXIVDMA_WRITE, &sys_vdma.options);
	status = XAxiVdma_DmaSetBufferAddr(&sys_vdma.controller, XAXIVDMA_WRITE,
                                       sys_vdma.options.FrameStoreStartAddr);
    if (IS_ERR(status)) {
        err("Can't setup vdma write channel");
        return XST_FAILURE;
    }

	// XAxiVdma_DmaConfig(&sys_vdma.controller, XAXIVDMA_READ, &sys_vdma.options);
	// status = XAxiVdma_DmaSetBufferAddr(&sys_vdma.controller, XAXIVDMA_READ,
    //                                    sys_vdma.options.FrameStoreStartAddr);
    // if (IS_ERR(status)) {
    //     err("Can't setup vdma read channel");
    //     return status;
    // }

	xil_printf("frame addr %x\n\r",sys_vdma.options.FrameStoreStartAddr[0]);

    return status;
}

// int vdma_start(enum vdma_chan channels)
int vdma_start()
{
    int status;

	status = XAxiVdma_DmaStart(&sys_vdma.controller, XAXIVDMA_WRITE);
    if (IS_ERR(status))
        return status;
	status = XAxiVdma_StartParking(&sys_vdma.controller, 0, XAXIVDMA_WRITE);
    if (IS_ERR(status))
        return status;
	// status = XAxiVdma_DmaStart(&sys_vdma.controller, XAXIVDMA_READ);
    // if (IS_ERR(status))
    //     return status;
	// status = XAxiVdma_StartParking(&sys_vdma.controller, 0, XAXIVDMA_READ);
    // if (IS_ERR(status))
    //     return status;

    return status;
}