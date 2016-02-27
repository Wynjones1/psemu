#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>
#include <map>
#include "bit_manipulation.h"

class VirtualAddress
{
public:
	explicit VirtualAddress(uint32_t value_)
		: value(value_)
	{}

	explicit operator uint32_t(){return value;}

	inline uint16_t offset() { return extract<11,0, uint16_t>(value); }
	inline uint32_t vpn()    { return extract<31,12, uint32_t>(value);}
	inline uint8_t  seg()    { return extract<31,29, uint8_t>(value); }

private:
	uint32_t value;
};

class Memory
{
public:
	uint32_t LoadWord(uint32_t address);
	uint16_t LoadHalfWord(uint32_t address);
	uint8_t  LoadByte(uint32_t address);
	void     StoreWord(uint32_t address, uint32_t value);
	void     StoreHalfWord(uint32_t address, uint16_t value);
	void     StoreByte(uint32_t address, uint8_t value);

	std::map<uint32_t, uint32_t> data;
};

#endif