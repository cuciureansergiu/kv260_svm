#include "addi9035.h"

int addi9035_init()
{
        for (int i = 0; i < ARRAY_SIZE(stream_on); i++) {
                iic_write32(stream_on[i].reg, stream_on[i].val);
        }
        for (int i = 0; i < ARRAY_SIZE(mode_0); i++) {
                iic_write32(mode_0[i].reg, mode_0[i].val);
        }
        return 0;
}

int addi9035_remove()
{
        for (int i = 0; i < ARRAY_SIZE(stream_off); i++) {
                iic_write32(stream_off[i].reg, stream_off[i].val);
        }
        return 0;

}
