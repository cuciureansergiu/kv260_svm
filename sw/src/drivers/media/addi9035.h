#include "../../drivers/interface/iic/iic.h"

#define ARRAY_SIZE(x) sizeof x / sizeof x[0]

struct addi9035_regmap {
        unsigned short reg;
        unsigned short val;
};

const struct addi9035_regmap stream_on[] = {
        { 0xC4C0, 0x001C },
        { 0xC4C3, 0x001C },
        { 0xC4D7, 0x0000 },
        { 0xC4D5, 0x0002 },
        { 0xC4DA, 0x0001 },
        { 0xC4F0, 0x0000 },
        { 0xC427, 0x0003 },
        { 0xC427, 0x0001 },
        { 0xC427, 0x0000 },
        { 0xC426, 0x0030 },
        { 0xC426, 0x0010 },
        { 0xC426, 0x0000 },
        { 0xC423, 0x0080 },
        { 0xC431, 0x0080 },
        { 0x4001, 0x0007 },
        { 0x7c22, 0x0004 },
};

const struct addi9035_regmap stream_off[] = {
        { 0x4001, 0x0006 },
        { 0x7c22, 0x0004 },
        { 0xC431, 0x0082 },
        { 0xC423, 0x0000 },
        { 0xC426, 0x0020 },
        { 0xC427, 0x0002 },
        { 0xC4C0, 0x003C },
        { 0xC4C3, 0x003C },
        { 0xC4D5, 0x0003 },
        { 0xC4DA, 0x0000 },
        { 0xC4D7, 0x0001 },
        { 0xC4F0, 0x0001 },
};

const struct addi9035_regmap mode_0[] = {
        { 0x4000, 0x0000 },
        { 0x4001, 0x0004 },
        { 0x7c22, 0x0004 }
};

const struct addi9035_regmap mode_1[] = {
        { 0x4000, 0x0000 },
        { 0x4001, 0x0004 },
        { 0x7c22, 0x0004 }
};

int addi9035_init();
int addi9035_remove();
