from pynq.lib.iic import *
from pynq import Overlay, allocate
from time import sleep
import numpy as np
import cffi

#TODO replace axi_iic_0 with axi_iic
class ov5640:
        
        __iic_device_addr = 0x3C
        __cam_device_id = 0x78
        
        __cfg_table = [
                [
                        [0x3008, 0x42],
                        [0x3103, 0x03],
                        [0x3017, 0x00],
                        [0x3018, 0x00],
                        [0x3034, 0x18],
                        [0x3035, 0x11],
                        [0x3036, 0x38],
                        [0x3037, 0x11],
                        [0x3108, 0x01],
                        [0x303D, 0x10],
                        [0x303B, 0x19],
                        [0x3630, 0x2e],
                        [0x3631, 0x0e],
                        [0x3632, 0xe2],
                        [0x3633, 0x23],
                        [0x3621, 0xe0],
                        [0x3704, 0xa0],
                        [0x3703, 0x5a],
                        [0x3715, 0x78],
                        [0x3717, 0x01],
                        [0x370b, 0x60],
                        [0x3705, 0x1a],
                        [0x3905, 0x02],
                        [0x3906, 0x10],
                        [0x3901, 0x0a],
                        [0x3731, 0x02],
                        [0x3600, 0x37],
                        [0x3601, 0x33],
                        [0x302d, 0x60],
                        [0x3620, 0x52],
                        [0x371b, 0x20],
                        [0x471c, 0x50],
                        [0x3a13, 0x43],
                        [0x3a18, 0x00],
                        [0x3a19, 0xf8],
                        [0x3635, 0x13],
                        [0x3636, 0x06],
                        [0x3634, 0x44],
                        [0x3622, 0x01],
                        [0x3c01, 0x34],
                        [0x3c04, 0x28],
                        [0x3c05, 0x98],
                        [0x3c06, 0x00],
                        [0x3c07, 0x08],
                        [0x3c08, 0x00],
                        [0x3c09, 0x1c],
                        [0x3c0a, 0x9c],
                        [0x3c0b, 0x40],
                        [0x503d, 0x00],
                        [0x3820, 0x46],
                        [0x300e, 0x45],
                        [0x4800, 0x14],
                        [0x302e, 0x08],
                        [0x4300, 0x6f],
                        [0x501f, 0x01],
                        [0x4713, 0x03],
                        [0x4407, 0x04],
                        [0x440e, 0x00],
                        [0x460b, 0x35],
                        [0x460c, 0x20],
                        [0x3824, 0x01],
                        [0x5000, 0x07],
                        [0x5001, 0x00]
                ],[
                        [0x518d ,0x00],
                        [0x518f ,0x20],
                        [0x518e ,0x00],
                        [0x5190 ,0x20],
                        [0x518b ,0x00],
                        [0x518c ,0x00],
                        [0x5187 ,0x10],
                        [0x5188 ,0x10],
                        [0x5189 ,0x40],
                        [0x518a ,0x40],
                        [0x5186 ,0x10],
                        [0x5181 ,0x58],
                        [0x5184 ,0x25],
                        [0x5182 ,0x11],
                        [0x3406 ,0x00],
                        [0x5183 ,0x80],
                        [0x5191 ,0xff],
                        [0x5192 ,0x00],
                        [0x5001 ,0x03]
                ],[
                        [0x3008, 0x42],
                        [0x3035, 0x21],
                        [0x3036, 0x46],
                        [0x3037, 0x05],
                        [0x3108, 0x11],
                        [0x3034, 0x1A],
                        [0x3800, 0x00],
                        [0x3801, 0x00],
                        [0x3802, 0x00],
                        [0x3803, 0x08],
                        [0x3804, 0x0A],
                        [0x3805, 0x3B],
                        [0x3806, 0x07],
                        [0x3807, 0x9B],
                        [0x3810, 0x00],
                        [0x3811, 0x00],
                        [0x3812, 0x00],
                        [0x3813, 0x00],
                        [0x3808, 0x05],
                        [0x3809, 0x00],
                        [0x380a, 0x02],
                        [0x380b, 0xD0],
                        [0x380c, 0x07],
                        [0x380d, 0x68],
                        [0x380e, 0x03],
                        [0x380f, 0xD8],
                        [0x3814, 0x31],
                        [0x3815, 0x31],
                        [0x3821, 0x01],
                        [0x4837, 0x24],
                        [0x3618, 0x00],
                        [0x3612, 0x59],
                        [0x3708, 0x64],
                        [0x3709, 0x52],
                        [0x370c, 0x03],
                        [0x4300, 0x00],
                        [0x501f, 0x03],
                        [0x3008, 0x02]
                ]
        ]
        
        class axi_iic:
                _ffi = cffi.FFI()
                
                def __init__(self, axi_iic, dev_addr):
                        self._iic_dev = AxiIIC(axi_iic)
                        self._iic_dev_addr = dev_addr
                        
                def set_device_addr(self, addr):
                        self._iic_dev_addr = addr

                def write(self, reg, data):
                        buf = _ffi.new("unsigned char [3]")
                        buf[0] = reg & 0xFF
                        buf[1] = (reg >> 8) & 0xFF
                        buf[2] = data
                        self._iic_dev.send(self._iic_dev_addr, buf, 3, option=0)
                        
                def read(self, reg):
                        buf = _ffi.new("unsigned char [2]")
                        buf[0] = reg & 0xFF
                        buf[1] = (reg >> 8) & 0xFF
                        self._iic_dev.send(self._iic_dev_addr, buf, 2, option=0)
                        self._iic_dev.receive(self._iic_dev_addr, buf, 1, option=0)

                        return buf[0]
        
        def __init__(self, device):
                self._iic = self.axi_iic(device, self.__iic_device_addr)
                self.__reset()
                self.__ping()
                self.set_mode(0)
                
                pass
        
        def __reset(self):
                self._iic.write(0x3103, 0x11)
                self._iic.write(0x3108, 0x82)
                sleep(0.01)
                
        def __ping(self):
                
                iic_device_id = self._iic.read(0x3100)
                
                if (iic_device_id != self.__cam_device_id):
                        print("Can't find ov5640")
        
        def set_mode(self, mode):
                if (mode == 0):
                        print("a")
                for config in self.__cfg_table:
                        for regmap in config:
                                self._iic.write(regmap[0], regmap[1])
          
class video_pipeline:
        
        class demosaic:
                def __init__(self, device):
                        self._device = device
                        self._device.write(0x10, 1280)
                        self._device.write(0x18, 720)
                        self._device.write(0x28, 3)
                        self._device.write(0x00, 0x80)
                        temp = self._device.read(0x00)
                        temp &= 0x80;
                        self._device.write(0x00, temp | 0x01)
        
        class gamma:
                __gamma_reg=[]
                
                def gamma_calc(self, gamma_val):
                        for i in range(0,512):
                                self.__gamma_reg.append((int)((pow(i/256.0, 1 / gamma_val) * 256.0)))
                                
                def __init__(self, device):
                        self.gamma_calc(1.2)
                        self._device = device
                        self._device.write(0x18, 720)
                        self._device.write(0x10, 1280)
                        self._device.write(0x20, 0)
                        for i in range(0,512):
                                self._device.write((int)(0x800 + i*4), self._gamma_reg[i])
                        for i in range(0,512):
                                self._device.write(0x1000 + i*4, self._gamma_reg[i])
                        for i in range(0,512):
                                self._device.write(0x1800 + i*4, self._gamma_reg[i])
                        self._device.write(0x00, 0x80)
                        temp = self._device.read(0x00)
                        temp &= 0x80
                        self._device.write(0x00, temp | 0x01)
        
        class vdma:
                def __init__(self, device):
                        self._device = device
                        self._buffer = allocate(shape=(720, 1280, 3), dtype=np.uint8, cacheable=1)
                        self._device.write(0x30, 0x93)
                        self._device.write(0xAC, self._buffer.device_address)
                        self._device.write(0xA8, 1280 * 3)
                        self._device.write(0xA4, 1280 * 3)
                        self._device.write(0xA0, 720 * 3)
                        
                def get_frame(self):
                        return Image.fromarray(self._buffer)

        
        def __init__(self, overlay):
                self._demosaic = self.demosaic(overlay.ip_dict['mipi/v_demosaic_0'])
                self._gamma = self.gamma(overlay.ip_dict['mipi/v_gamma_lut_0'])
                self._vdma = self.vdma(overlay.ip_dict['mipi/axi_vdma_0'])
                          

from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
      
overlay = Overlay("./bit/kv260_3d_svm.bit", ignore_version=True)
camera = ov5640(overlay.ip_dict['processing_system/axi_iic_0'])
vp = video_pipeline(overlay)

image = vp.vdma.get_frame
canvas = plt.gcf()
size = canvas.get_size_inches()
canvas.set_size_inches(size*2)
plt.imshow(image)
