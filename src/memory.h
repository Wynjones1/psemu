#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>
#include "bit_manipulation.h"

class VirtualAddress
{
public:
	explicit VirtualAddress(uint32_t value_)
		: value(value_)
	{}

	explicit operator uint32_t(){return value;}

	inline uint16_t offset() { return extract<uint16_t>(value, 11, 0); }
	inline uint32_t vpn()    { return extract<uint32_t>(value, 31, 12);}
	inline uint8_t  seg()    { return extract<uint8_t>(value, 31, 29); }

private:
	uint32_t value;
};

class Memory
{
public:
	uint32_t Load(uint32_t address);
	void     Store(uint32_t address, uint32_t value);
};

#endif