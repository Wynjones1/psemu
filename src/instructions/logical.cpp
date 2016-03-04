#include "cpu.h"

void CPU::SLT(void)
{
	/* SLT rd, rs, rt
		Compare contents of register rt to register rs(as signed 32 - bit integers).
		If register rs is less than rt, result = 1; otherwise, result = 0.*/
    auto rs = to_unsigned(registers[EX.instruction.rs()]);
    auto rt = to_unsigned(registers[EX.instruction.rt()]);
    if(rs < rt)
    {
        registers[EX.instruction.rd()] = 1;
    }
    else
    {
        registers[EX.instruction.rd()] = 0;
    }
}

void CPU::SLTU(void)
{
	/* SLTU rd, rs, rt
		Compare contents of register rt to register rs(as unsigned 32 - bit integers).
        If register rs is less than rt, result = 1; otherwise, result = 0.*/
	TODO("Implement");
}

void CPU::AND(void)
{
	/* AND rd, rs, rt
		Bit - wise AND contents of registers rs and rt and place result in
		register rd.*/
	TODO("Implement");
}

void CPU::OR(void)
{
	/* OR rd, rs, rt
		Bit - wise OR contents of registers rs and rt and place result in
		register rd.*/
	TODO("Implement");
}

void CPU::XOR(void)
{
	/* XOR rd, rs, rt
		Bit - wise Exclusive OR contents of registers rs and rt and place
		result in register rd.*/
	TODO("Implement");
}

void CPU::NOR(void)
{
	/* NOR rd, rs, rt
		Bit - wise NOR contents of registers rs and rt and place result in
		register rd.*/
	TODO("Implement");
}
