// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xsobel.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XSobel_CfgInitialize(XSobel *InstancePtr, XSobel_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XSobel_Start(XSobel *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSobel_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_CONTROL_ADDR_AP_CTRL) & 0x80;
    XSobel_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XSobel_IsDone(XSobel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSobel_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XSobel_IsIdle(XSobel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSobel_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XSobel_IsReady(XSobel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSobel_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XSobel_EnableAutoRestart(XSobel *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSobel_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XSobel_DisableAutoRestart(XSobel *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSobel_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_CONTROL_ADDR_AP_CTRL, 0);
}

u32 XSobel_Get_return(XSobel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSobel_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_CONTROL_ADDR_AP_RETURN);
    return Data;
}
void XSobel_InterruptGlobalEnable(XSobel *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSobel_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_CONTROL_ADDR_GIE, 1);
}

void XSobel_InterruptGlobalDisable(XSobel *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSobel_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_CONTROL_ADDR_GIE, 0);
}

void XSobel_InterruptEnable(XSobel *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XSobel_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_CONTROL_ADDR_IER);
    XSobel_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_CONTROL_ADDR_IER, Register | Mask);
}

void XSobel_InterruptDisable(XSobel *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XSobel_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_CONTROL_ADDR_IER);
    XSobel_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_CONTROL_ADDR_IER, Register & (~Mask));
}

void XSobel_InterruptClear(XSobel *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSobel_WriteReg(InstancePtr->Control_BaseAddress, XSOBEL_CONTROL_ADDR_ISR, Mask);
}

u32 XSobel_InterruptGetEnabled(XSobel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XSobel_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_CONTROL_ADDR_IER);
}

u32 XSobel_InterruptGetStatus(XSobel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XSobel_ReadReg(InstancePtr->Control_BaseAddress, XSOBEL_CONTROL_ADDR_ISR);
}

