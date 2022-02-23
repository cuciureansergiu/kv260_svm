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
#include <math.h>


#define STATUS_OK                       0
#define STATUS_OPENING_DEV_MEM_FAILED   1
#define STATUS_MAPPING_FAILED 		2
#define STATUS_UNMAPPING_FAILED		3
#define STATUS_CLOSING_DEV_MEM_FAILED	4
#define STATUS_COPYING_DATA_FAILED	5

#define LOG     printf
const off_t vdma_base = 0xA0020000u;
const off_t demosaic_base = 0xA0030000u;
const off_t gamma_base = 0xA0040000u;
const off_t addr_range =  0x00010000u;

void axi_write(uint32_t baseaddr, uint32_t reg, uint32_t val)
{
        *(volatile uint32_t*)(baseaddr + reg) = val;
}
uint32_t axi_read(uint32_t baseaddr, uint32_t reg)
{
        return *(volatile uint32_t*)(baseaddr + reg);
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

int bind_device(volatile uint32_t **ptr, const off_t base)
{
	LOG("Binding device with physical address = 0x%x\n", base);
	return map_device((volatile void **)ptr, addr_range, PROT_READ|PROT_WRITE, base);
}

int unbind_device(volatile uint32_t **ptr)
{
	LOG("Unbinding device with physical address = 0x%x\n", ptr);
   	return unmap((volatile void **) ptr, addr_range);
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

void demosaic_init(uint32_t baseaddr)
{
        uint32_t temp;

        axi_write(baseaddr, 0x10, 1280);
        axi_write(baseaddr, 0x18, 720);
        axi_write(baseaddr, 0x28, 3);
        axi_write(baseaddr, 0x00, 0x80);
        temp = axi_read(baseaddr, 0x00);
        temp &= 0x80;
        axi_write(baseaddr, 0x00, temp | 0x01);

}

unsigned short gamma_reg[1024];

void gamma_calc(float gamma_val)
{
	int i;
	for (i = 0; i < 256; i++)
	{
		gamma_reg[i] = (pow((i / 256.0), (1 / gamma_val)) * 256.0);
	}
}
void gama_init(uint32_t baseaddr)
{
        uint32_t temp;
        int i;

	gamma_calc(1.2);
        axi_write(baseaddr, 0x10, 1280);
        axi_write(baseaddr, 0x18, 720);
        axi_write(baseaddr, 0x20, 0);
        for (i = 0; i < 512; i++) {
                axi_write(baseaddr, 0x800 + i, gamma_reg[i]);
        }
        for (i = 0; i < 512; i++) {
                axi_write(baseaddr, 0x1000 + i, gamma_reg[i]);
        }
        for (i = 0; i < 512; i++) {
                axi_write(baseaddr, 0x1800 + i, gamma_reg[i]);
        }
        axi_write(baseaddr, 0x00, 0x80);
        temp = axi_read(baseaddr, 0x00);
        temp &= 0x80;
        axi_write(baseaddr, 0x00, temp | 0x01);
}

int main(void)
{
        volatile uint32_t *demosaic, gamma;

        bind_device(&demosaic, demosaic_base);
        bind_device(&gamma, gamma_base);
        demosaic_init(demosaic);
        gama_init(gamma);
        // unbind_device(&demosaic);
        // unbind_device(&gamma);
}