// #include <xvtc.h>

// #include "../../util/debug.h"
// #include "../../util/error.h"
// #include "vtc.h"

// static struct t_sys_vtc {
//     XVtc                controller;
//     XVtc_Timing         timing;
//     XVtc_Config         *config;
//     XVtc_SourceSelect   source;
// } sys_vtc;

// int vtc_init(int device_id, enum vtc_modes mode)
// {
// 	int status;

//     sys_vtc.config = XVtc_LookupConfig(device_id);
//     if (sys_vtc.config == NULL) {
//         err("Video timing controller not found");
//         return XST_FAILURE;
//     }

//     status = XVtc_CfgInitialize(&sys_vtc.controller,
//                                 sys_vtc.config,
//                                 sys_vtc.config->BaseAddress);
//     if (IS_ERR(status)) {
//         err("Failed to convigure video timing controller");
//         return status;
//     }

//     status = vtc_set_mode(mode);
//     if (IS_ERR(status)) {
//         err("Video timing controller can't set the requested mode");
//         return status;
//     }

//     return XST_SUCCESS;
// }

// int vtc_set_mode(enum vtc_modes mode)
// {
//     struct vtc_mode vmode = video_modes[mode];
    
//     //TODO: set the mode using a xvtc structure directly
// 	sys_vtc.timing.HActiveVideo = vmode.width;	/**< Horizontal Active Video Size */
// 	sys_vtc.timing.HFrontPorch = vmode.hps - vmode.width;	/**< Horizontal Front Porch Size */
// 	sys_vtc.timing.HSyncWidth = vmode.hpe - vmode.hps;		/**< Horizontal Sync Width */
// 	sys_vtc.timing.HBackPorch = vmode.hmax - vmode.hpe + 1;		/**< Horizontal Back Porch Size */
// 	sys_vtc.timing.HSyncPolarity = vmode.hpol;	/**< Horizontal Sync Polarity */
// 	sys_vtc.timing.VActiveVideo = vmode.height;	/**< Vertical Active Video Size */
// 	sys_vtc.timing.V0FrontPorch = vmode.vps - vmode.height;	/**< Vertical Front Porch Size */
// 	sys_vtc.timing.V0SyncWidth = vmode.vpe - vmode.vps;	/**< Vertical Sync Width */
// 	sys_vtc.timing.V0BackPorch = vmode.vmax - vmode.vpe + 1;;	/**< Horizontal Back Porch Size */
// 	sys_vtc.timing.V1FrontPorch = vmode.vps - vmode.height;	/**< Vertical Front Porch Size */
// 	sys_vtc.timing.V1SyncWidth = vmode.vpe - vmode.vps;	/**< Vertical Sync Width */
// 	sys_vtc.timing.V1BackPorch = vmode.vmax - vmode.vpe + 1;;	/**< Horizontal Back Porch Size */
// 	sys_vtc.timing.VSyncPolarity = vmode.vpol;	/**< Vertical Sync Polarity */
// 	sys_vtc.timing.Interlaced = 0;

//     sys_vtc.source.VBlankPolSrc = 1;
// 	sys_vtc.source.VSyncPolSrc = 1;
// 	sys_vtc.source.HBlankPolSrc = 1;
// 	sys_vtc.source.HSyncPolSrc = 1;
// 	sys_vtc.source.ActiveVideoPolSrc = 1;
// 	sys_vtc.source.ActiveChromaPolSrc= 1;
// 	sys_vtc.source.VChromaSrc = 1;
// 	sys_vtc.source.VActiveSrc = 1;
// 	sys_vtc.source.VBackPorchSrc = 1;
// 	sys_vtc.source.VSyncSrc = 1;
// 	sys_vtc.source.VFrontPorchSrc = 1;
// 	sys_vtc.source.VTotalSrc = 1;
// 	sys_vtc.source.HActiveSrc = 1;
// 	sys_vtc.source.HBackPorchSrc = 1;
// 	sys_vtc.source.HSyncSrc = 1;
// 	sys_vtc.source.HFrontPorchSrc = 1;
// 	sys_vtc.source.HTotalSrc = 1;

// 	XVtc_RegUpdateEnable(&sys_vtc.controller);
// 	XVtc_SetGeneratorTiming(&sys_vtc.controller, &sys_vtc.timing);
// 	XVtc_SetSource(&sys_vtc.controller, &sys_vtc.source);
// 	XVtc_EnableGenerator(&sys_vtc.controller);
// 	XVtc_Enable(&sys_vtc.controller);

// }