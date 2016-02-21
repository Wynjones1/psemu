#ifndef CPU_H
#define CPU_H
#include <stdint.h>
#include "encoding.h"


class CPU
{
public:
    void FetchInstruction(void);
    void DecodeInstruction(void);
    void ExecuteALU(void);
    void AccessMemory(void);
    void Writeback(void);
public:
    uint32_t registers[32];
    uint32_t pc;
    uint32_t hi;
    uint32_t lo;
};

#endif
