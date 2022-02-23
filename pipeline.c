#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <poll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
//#include "img.h"

#define LOG 			       printf

#define TEST_SIZE		       10

#define FRAME_WIDTH		       256
#define FRAME_HEIGHT 		       256
#define FRAME_SIZE		       FRAME_HEIGHT * FRAME_WIDTH

#define STATUS_                         0
#define STATUS_OPENING_DEV_MEM_FAILED   1
#define STATUS_MAPPING_FAILED 		2
#define STATUS_UNMAPPING_FAILED		3
#define STATUS_CLOSING_DEV_MEM_FAILED	4
#define STATUS_COPYING_DATA_FAILED	5

#define I00			   	0
#define I45	   			1
#define I90	   			2
#define I135	   		3
#define KERNEL	  	 	4
#define BRAM_SIZE		sizeof(uint8_t) * 1024 * 64 //64KB BRAM block

const off_t bram_ch[] =  {0x42000000u,
                       	  0x44000000u,
                       	  0x46000000u,
                       	  0x48000000u,
                       	  0x4C000000u};
const off_t conv =  	  0x43C00000u;
const off_t vga = 	  0x43C10000u;
const off_t addr_range =  0x00010000u;

union convert {
    uint32_t word;
    uint16_t halfword[2];
    uint8_t bytes[4];
} convert;

static const char * status_codes[] = {
    "OK",
    "Failed to open /dev/mem",
    "Failed to map",
    "Failed to unmap",
    "Failed to close /dev/mem",
    "Failed to copy data",
};

const char* get_status(int status)
{
	return status_codes[status];
}

void err(int status)
{
  LOG(get_status(status));
}

int map_device(volatile void **ptr, size_t size, int port, off_t offset)
{
	int fd;

	fd = open("/dev/mem", O_RDWR);
	if(fd < 1)
	{
   		return STATUS_OPENING_DEV_MEM_FAILED;
   	}
	LOG("Mapping device \n");
	*ptr = (volatile void *) mmap(NULL, size, port, MAP_SHARED, fd, offset);
	if(*ptr == MAP_FAILED)
	{
		return STATUS_MAPPING_FAILED;
	}
	LOG("Device mapped to user space, 0x%x\n", ptr);
	if(!close(fd))
	{//we can close the file descriptor as mmap keeps it automatically open until we munmap
	   return STATUS_OK;
	}
	else
	{
	   return STATUS_CLOSING_DEV_MEM_FAILED;
	}
}

int unmap(volatile void **ptr, size_t size)
{
 	LOG("Unmapping device \n");
 	if(!(munmap(*((void **)ptr), size) == 0))
 	{
     	return STATUS_UNMAPPING_FAILED;
 	}
 	*ptr = NULL;
 	LOG("Device unmapped");

 	return STATUS_OK;
}

int bind_bram(volatile uint32_t **ptr, uint8_t ch)
{
	LOG("Binding BRAM ch[%d] with physical address = 0x%x\n", ch, bram_ch[ch]);
	return map_device((volatile void **)ptr, BRAM_SIZE, PROT_READ|PROT_WRITE, bram_ch[ch]);
}

int unbind_bram(volatile uint32_t **ptr)
{
	LOG("Unbinding BRAM ch with physical address = 0x%x\n", ptr);
   	return unmap((volatile void **) ptr, BRAM_SIZE);
}

int bind_conv(volatile uint32_t **ptr)
{
	LOG("Binding device with physical address = 0x%x\n", conv);
	return map_device((volatile void **)ptr, addr_range, PROT_READ|PROT_WRITE, conv);
}

int bind_vga(volatile uint32_t **ptr)
{
	LOG("Binding device with physical address = 0x%x\n", vga);
	return map_device((volatile void **)ptr, addr_range, PROT_READ|PROT_WRITE, vga);
}

int unbind_device(volatile uint32_t **ptr)
{
	LOG("Unbinding device with physical address = 0x%x\n", ptr);
   	return unmap((volatile void **) ptr, addr_range);
}

void soft_device(volatile uint32_t *input, volatile uint32_t* kernel, volatile uint32_t* output)
{
  int idx;

  for(idx = 0; idx < FRAME_SIZE; idx++)
  {
    // Split in bytes and multiply
    *(output + idx) =(((*(input + idx)        & 0xFF) *  (*(kernel + idx)        & 0xFF))           |
                    ((((*(input + idx) >> 8 ) & 0xFF) * ((*(kernel + idx) >> 8 ) & 0xFF )) << 8 )   |
                    ((((*(input + idx) >> 16) & 0xFF) * ((*(kernel + idx) >> 16) & 0xFF )) << 16)   |
                    ((((*(input + idx) >> 24) & 0xFF) * ((*(kernel + idx) >> 24) & 0xFF )) << 24)   );
  }
}

// This function eables the device once
void start_device(volatile uint32_t**  device)
{
	// Start the device
	*((uint32_t *)(device)) = (*((uint32_t *)(device)) & 0x80) | 0x01;
	// Wait to finish
	while(!((*((uint32_t *)(device)) >> 1) & 0x1));
}

// This functions sets the device in auto-restart mode
void loop_device(volatile uint32_t** device)
{
	// Set autorestart
	*((uint32_t *)(device)) = (*((uint32_t *)(device)) & 0x80);
}

// Read 4 32-bit pixels and save them at once
void load_frame(const uint8_t* img, uint32_t height, uint32_t width, volatile uint32_t *dest)
{
	int idx, temp_idx = 0;

	for(idx = 0; idx < height * width / 4; idx++)
	{
		*(dest + idx) = (volatile uint32_t) (*(img + temp_idx) 		     |
											 *(img + temp_idx + 1) << 8  |
											 *(img + temp_idx + 2) << 16 |
											 *(img + temp_idx + 3) << 24);
		temp_idx += 4;
	}
}

void write_color_bars(volatile uint32_t** dest)
{
	for(int idx = 0; idx < FRAME_SIZE; idx++)
	{
    	*(dest + idx) = 	  0xD3D3D3D3;
	}
    for(int idx = FRAME_SIZE/4; idx <FRAME_SIZE/2 ; idx++)
	{
    	*(dest + idx) = 	  0x70707070;
	}
    for(int idx = FRAME_SIZE/2; idx <FRAME_SIZE*3/4 ; idx++)
	{
    	*(dest + idx) = 	  0x40404040;
	}
    for(int idx = FRAME_SIZE*3/4; idx <FRAME_SIZE ; idx++)
	{
    	*(dest + idx) = 	  0x10101010;
	}
}

int main(void)
{
	struct timespec start, stop;
	double diff;
	int fd, idx;
	volatile uint32_t *surface,
					  *vga_ctrl,
					  *mem_i0,
					  *mem_i45,
					  *mem_i90,
					  *mem_i135,
					  *mem_kernel;

  	bind_bram(&mem_i0,  I00);
	bind_bram(&mem_i45, I45);
	bind_bram(&mem_i90, I90);
	bind_bram(&mem_i135, I135);
	bind_bram(&mem_kernel, KERNEL);
	bind_conv(&surface);
	bind_vga(&vga_ctrl);


	LOG("\r\nStarting device test\n");

	for(int idx = 0; idx < FRAME_SIZE; idx++)
	{
    	*(mem_i0 + idx) = (uint32_t) 0xD3D3D3D3;
	}
	LOG("%x",*(mem_i0));
	LOG("%x",*(mem_i0 + 1));
	LOG("%x",*(mem_i45));

	LOG("\r\nLooping devices\n");
	// Set autorestart
	int jdx = 0;
	  /*XBram_read_EnableAutoRestart(&bramVidInstance);
	  XBram_read_Start(&bramVidInstance);*/
	  //*((uint32_t *)(vga)) = (*((uint32_t *)(vga)) & 0x80) | 0x01;
	*(vga_ctrl) = (uint32_t) 0x81;

    	LOG("test");
	/**((uint32_t *)(conv)) = (uint32_t) 0x80;*/
    while(1)
    {

        for(int idx = 0; idx < FRAME_SIZE; idx++)
    	{
        	*(mem_i0 + idx) = 	 jdx;
    	}
        jdx++;
    	/*XGradient_Start(&gradientInstance);
    	while(!XGradient_IsDone(&gradientInstance));*/

    	*((uint32_t *)(surface)) = (*((uint32_t *)(surface)) & 0x80) | 0x01;
    	// Wait to finish
    	while(!((*((uint32_t *)(surface)) >> 1) & 0x1));
    	LOG("test");
    }

	/*
 	// Prepare the buffers
	for(idx = 0; idx < TEST_SIZE; idx++)
	{
		*(input + idx)  = (uint32_t) 0x02020202;
		*(kernel + idx) = (uint32_t) 0x03030303;
		*(output + idx) = (uint32_t) 0x00000000;
	}
  	// Get start time
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

	// Start the device
	*((uint32_t *)(device)) = (*((uint32_t *)(device)) & 0x80) | 0x01;
	// Wait to finish
	while(!((*((uint32_t *)(device)) >> 1) & 0x1));

	// Get end time
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
	for(idx = 0; idx < TEST_SIZE; idx++)
	{
		if(*(output + idx) != (uint32_t) 0x06060606)
		{
			LOG("Corrupted data : i:%X k:%X o:%X\n",*(input + idx), *(kernel + idx), *(output + idx));
			break;
		}
	}
	diff = (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3;
	LOG("\r\nSWtest took %f  microseconds\n\n",diff);

  	// Prepare the buffer
  	for(idx = 0; idx < TEST_SIZE; idx++)
  	{
    	*(output + idx) = (uint32_t) 0x00000000;
  	}
  	// Get start time
  	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
  	// Start sw process
  	soft_device(input, kernel, output);
  	// Get end time
  	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
  	for(idx = 0; idx < TEST_SIZE; idx++)
  	{
    	if(*(output + idx) != (uint32_t) 0x06060606)
    	{
      	LOG("Corrupted data : i:%X k:%X o:%X\n",*(input + idx), *(kernel + idx), *(output + idx));
      	break;
    	}
  	}
  	diff = (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3;
  	LOG("\r\nHWtest took %f  microseconds\n\n",diff);
	*/

  	unbind_bram(&mem_i0);
	unbind_bram(&mem_i45);
	unbind_bram(&mem_i90);
	unbind_bram(&mem_i135);
	unbind_bram(&mem_kernel);
	unbind_device(&surface);
	unbind_device(&vga_ctrl);

	LOG("\nEnd of test\n");

	return 0;
}