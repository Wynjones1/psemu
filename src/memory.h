#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>

class Memory
{
public:
	uint32_t Load(uint32_t address);
	void     Store(uint32_t address, uint32_t value);
};

#endif