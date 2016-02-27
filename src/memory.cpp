#include "memory.h"

uint32_t Memory::LoadWord(uint32_t address)
{
	return data[address >> 2];
}

uint16_t Memory::LoadHalfWord(uint32_t address)
{
	return (data[address >> 2] >> (16 * ((address >> 1) & 0x1))) & 0xffff;
}

uint8_t Memory::LoadByte(uint32_t address)
{
	return (data[address >> 2] >> (8 * (address & 0x3))) & 0xff;
}

void Memory::StoreWord(uint32_t address, uint32_t value)
{
	data[address >> 2] = value;
}

void Memory::StoreHalfWord(uint32_t address, uint16_t value)
{
	union
	{
		uint32_t ui32;
		uint16_t ui16[2];
	}temp;
	temp.ui32 = data[address >> 2];
	temp.ui16[(address >> 1) & 0x1] = value;
}

void Memory::StoreByte(uint32_t address, uint8_t value)
{
	union
	{
		uint32_t ui32;
		uint8_t ui8[4];
	}temp;
	temp.ui32 = data[address >> 2];
	temp.ui8[address & 0x3] = value;
}