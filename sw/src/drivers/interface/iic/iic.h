
int iic_init(int device_id, int iic_rate, int addr);
int iic_write8(unsigned char val);
int iic_write16(unsigned char reg, unsigned char val);
int iic_write16read8(unsigned short reg, unsigned char *val);
int iic_write24(unsigned short reg, unsigned char val);
int iic_write32(unsigned short reg, unsigned char val);
int iic_set_switch(unsigned char addr);