#include "cpu.h"

// Computational Instructions (I-Type).
void CPU::ADDI(void)
{
	/* ADDI rt, rs, immediate
		Add 16 - bit sign - extended immediate to register rs and place 32 -
		bit result in register rt.Trap on twos complement overflow.*/
	auto rs = registers[EX.instruction.rs()];
	auto sum = rs + EX.sign_extended_data;
	auto rs_neg = extract(rs, 31, 31);
	auto imm_neg = extract(EX.sign_extended_data, 31, 31);
	auto sum_neg = extract(sum, 31, 31);

	if ((rs_neg && imm_neg && !sum_neg) || // Negative overflow.
		(!rs_neg && !imm_neg && sum_neg))  // Positive overflow.
	{
		TriggerOverflowException();
	}
	else
	{
		registers[EX.instruction.rt()] = sum;
	}
}

void CPU::ADDIU(void)
{
	/* ADDIU rt, rs, immediate
		Add 16 - bit sign - extended immediate to register rs and place 32 -
		bit result in register rt.Do not trap on overflow.*/
	auto rs = registers[EX.instruction.rs()];
	auto sum = rs + EX.sign_extended_data;
	registers[EX.instruction.rt()] = sum;
}

void CPU::SLTI(void)
{
	/*	SLTI rt, rs, immediate
		Compare 16 - bit sign - extended immediate with register rs as
		signed 32 - bit integers.Result = 1 if rs is less than immediate;
		otherwise result = 0.
		Place result in register rt.*/
	TODO("Implement");
}

void CPU::SLTIU(void)
{
	/* SLTIU rt, rs, immediate
		Compare 16 - bit sign - extended immediate with register rs as
		unsigned 32 - bit integers.Result = 1 if rs is less than immediate;
		otherwise result = 0. Place result in register rt.Do not trap on
		overflow.*/
	TODO("Implement");
}

void CPU::ANDI(void)
{
	/* ANDI rt, rs, immediate
		Zero - extend 16 - bit immediate, AND with contents of register rs
		and place result in register rt.*/
	TODO("Implement");
}

void CPU::ORI(void)
{
	/* ORI rt, rs, immediate
		Zero - extend 16 - bit immediate, OR with contents of register rs
		and place result in register rt.*/
	TODO("Implement");
}

void CPU::XORI(void)
{
	/* XORI rt, rs, immediate
		Zero - extend 16 - bit immediate, exclusive OR with contents of
		register rs and place result in register rt.*/
	TODO("Implement");
}

void CPU::LUI(void)
{
	/* LUI rt, immediate
		Shift 16 - bit immediate left 16 bits.Set least significant 16 bits
		of word to zeroes.Store result in register rt.*/
	TODO("Implement");
}
