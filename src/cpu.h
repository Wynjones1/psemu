#ifndef CPU_H
#define CPU_H
#include <stdint.h>
#include "encoding.h"


class CPU
{
public:
    uint32_t registers[32];
    uint32_t pc;
    // Mul / Div result
    uint32_t lo;
    uint32_t hi;
};

#endif
