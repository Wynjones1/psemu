#include "cpu.h"

// Computational Instructions (R-Type Shifts).
void CPU::SLL(void)
{
	/* SLL rd, rt, shamt
		Shift contents of register rt left by shamt bits, inserting zeroes
		into low order bits.Place 32 - bit result in register rd.*/
	TODO("Implement");
}

void CPU::SRL(void)
{
	/* SRL rd, rt, shamt
		Shift contents of register rt right by shamt bits, inserting zeroes
		into high order bits.Place 32 - bit result in register rd.*/
	TODO("Implement");
}

void CPU::SRA(void)
{
	/* SRA rd, rt, shamt
		Shift contents of register rt right by shamt bits, sign - extending
		the high order bits.Place 32 - bit result in register rd.*/
	TODO("Implement");

}

void CPU::SLLV(void)
{
	/* SLLV rd, rt, rs
		Shift contents of register rt left.Low - order 5 bits of register rs
		specify number of bits to shift.Insert zeroes into low order bits
		of rt and place 32 - bit result in register rd.*/
	TODO("Implement");

}

void CPU::SRLV(void)
{
	/* SRLV rd, rt, rs
		Shift contents of register rt right.Low - order 5 bits of register rs
		specify number of bits to shift.Insert zeroes into high order bits
		of rt and place 32 - bit result in register rd.*/
	TODO("Implement");

}

void CPU::SRAV(void)
{
	/* SRAV rd, rt, rs
		Shift contents of register rt right.Low - order 5 bits of register rs
		specify number of bits to shift.Sign - extend the high order bits
		of rt and place 32 - bit result in register rd.*/
	TODO("Implement");
}
