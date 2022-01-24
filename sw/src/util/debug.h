#ifndef _DEBUG_H_
#define _DEBUG_H_

// #define DEBUG_NONE      0
// #define DEBUG_WARN      1
// #define DEBUG_INFO      2
// #define DEBUG_ALL       3

// #ifndef DEBUG_ERR_LEVEL
//     #define DEBUG_ERR_LEVEL DEBUG_INFO
// #endif

// #define _debug_fun (none, warn, info, debug)

// #define _debug(level) level != 0 ? ##level() : {} ;

#define DEBUG_INFO          1

#ifndef DEBUG_NONE
    #define DEBUG_WARN
#endif

#ifdef DEBUG_ALL
    #define DEBUG_INFO
#endif

#ifdef DEBUG_INFO
    #define DEBUG_WARN
#endif

void err(unsigned char *msg);
void info(unsigned char *msg);
void debug(unsigned char *msg); 

#endif