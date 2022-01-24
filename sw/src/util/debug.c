#include <xil_printf.h>
#include "debug.h"

void err(unsigned char *msg)
{
#ifdef DEBUG_WARN
    print("\n");
#ifdef DEBUG_ALL
    print("[%s:%s:%s]", __FILE__, __FUNCTION__, __LINE__);
#endif
    print(msg);
    print("\n\r");
#endif
}

void info(unsigned char *msg)
{
#ifdef DEBUG_INFO
    print("\n");
#ifdef DEBUG_ALL
    print("[%s:%s:%s]", __FILE__, __FUNCTION__, __LINE__);
#endif
    print(msg);
    print("\n\r");
#endif
}

void debug(unsigned char *msg)
{
#ifdef DEBUG_ALL
    print("[%s:%s:%s]\n", __FILE__, __FUNCTION__, __LINE__);
    print(msg);
    print("\n\r");
#endif
}
