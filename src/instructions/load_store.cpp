#include "cpu.h"

// Load Instructions.
void CPU::LB(void)
{
	/* LB rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Sign - extend contents of addressed byte and load into rt. */
	TODO("Implement");
}

void CPU::LBU(void)
{
	/* LBU rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Zero - extend contents of addressed byte and load into rt.*/
	TODO("Implement");
}

void CPU::LH(void)
{
	/* LH rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Sign - extend contents of addressed byte and load into rt.*/
	TODO("Implement");
}

void CPU::LHU(void)
{
	/* LHU rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Zero - extend contents of addressed byte and load into rt.*/
	TODO("Implement");
}

void CPU::LW(void)
{
	/* LW rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Load contents of addressed word into register rt.*/
	TODO("Implement");
}

void CPU::LWL(void)
{
	/* LWL rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Shift addressed word left so that addressed byte is leftmost byte
		of a word.
		Merge bytes from memory with contents of register rt and load
		result into register rt.*/
	TODO("Implement");
}

void CPU::LWR(void)
{
	/* LWR rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Shift addressed word right so that addressed byte is rightmost
		byte of a word.
		Merge bytes from memory with contents of register rt and load
		result into register rt.*/
	TODO("Implement");
}

// Store Instructions.
void CPU::SB(void)
{
	/* SB rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Store least significant byte of register rt at addressed location.*/
	TODO("Implement");
}

void CPU::SH(void)
{
	/* SH rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Store least significant halfword of register rt at addressed location.*/
	TODO("Implement");
}

void CPU::SW(void)
{
	/* SW rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Store least significant word of register rt at addressed location.*/
	TODO("Implement");
}

void CPU::SWL(void)
{
	/* SWL rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Shift contents of register rt right so that leftmost byte of the word
		is in position of addressed byte.Store bytes containing original
		data into corresponding bytes at addressed byte.*/
	TODO("Implement");
}

void CPU::SWR(void)
{
	/* SWR rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Shift contents of register rt left so that rightmost byte of the word
		is in position of addressed byte.Store bytes containing original
		data into corresponding bytes at addressed byte.*/
	TODO("Implement");
}
