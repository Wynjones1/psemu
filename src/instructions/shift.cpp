#include "cpu.h"

// Computational Instructions (R-Type Shifts).
void CPU::SLL(void)
{
	/* SLL rd, rt, shamt
		Shift contents of register rt left by shamt bits, inserting zeroes
		into low order bits.Place 32 - bit result in register rd.*/
	auto rt = registers[EX.instruction.rt()];
	auto sa = EX.instruction.shamt();
	registers[EX.instruction.rd()] = rt << sa;
}

void CPU::SRL(void)
{
	/* SRL rd, rt, shamt
		Shift contents of register rt right by shamt bits, inserting zeroes
		into high order bits.Place 32 - bit result in register rd.*/
	auto rt = registers[EX.instruction.rt()];
	auto sa = EX.instruction.shamt();
	registers[EX.instruction.rd()] = rt >> sa;
}

void CPU::SRA(void)
{
	/* SRA rd, rt, shamt
		Shift contents of register rt right by shamt bits, sign - extending
		the high order bits.Place 32 - bit result in register rd.*/
	auto rt  = registers[EX.instruction.rt()];
	auto sa  = EX.instruction.shamt();
	auto out = rt >> sa;
	auto sign_bit = extract(rt, 31, 31);
	if (sign_bit && sa) // sign extend.
	{
		out |= mask(31, 31 - (sa - 1));
	}
	registers[EX.instruction.rd()] = out;
}

void CPU::SLLV(void)
{
	/* SLLV rd, rt, rs
		Shift contents of register rt left.Low - order 5 bits of register rs
		specify number of bits to shift.Insert zeroes into low order bits
		of rt and place 32 - bit result in register rd.*/
	auto rt = registers[EX.instruction.rt()];
	auto rs = registers[EX.instruction.rs()] & mask(4, 0);
	registers[EX.instruction.rd()] = rt << rs;

}

void CPU::SRLV(void)
{
	/* SRLV rd, rt, rs
		Shift contents of register rt right.Low - order 5 bits of register rs
		specify number of bits to shift.Insert zeroes into high order bits
		of rt and place 32 - bit result in register rd.*/
	auto rt = registers[EX.instruction.rt()];
	auto rs = registers[EX.instruction.rs()] & mask(4, 0);
	registers[EX.instruction.rd()] = rt >> rs;
}

void CPU::SRAV(void)
{
	/* SRAV rd, rt, rs
		Shift contents of register rt right.Low - order 5 bits of register rs
		specify number of bits to shift.Sign - extend the high order bits
		of rt and place 32 - bit result in register rd.*/
	auto rt = registers[EX.instruction.rt()];
	auto rs = registers[EX.instruction.rs()] & mask(4, 0);
	auto out = rt >> rs;
	auto sign_bit = extract(rt, 31, 31);
	if (sign_bit && rs) // sign extend.
	{
		out |= mask<uint32_t>(31, 31 - (rs - 1));
	}
	registers[EX.instruction.rd()] = out;
}
