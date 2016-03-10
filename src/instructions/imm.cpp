#include "cpu.h"

// Computational Instructions (I-Type).
void CPU::ADDI(void)
{
	/* ADDI rt, rs, immediate
		Add 16 - bit sign - extended immediate to register rs and place 32 -
		bit result in register rt.Trap on twos complement overflow.*/
	auto rs = registers[EX.instruction.rs()];
	auto &imm = EX.sign_extended_data;
	auto sum = rs + imm;
	auto rs_neg = extract(rs, 31, 31);
	auto imm_neg = extract(imm, 31, 31);
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
	auto rs   = to_signed(registers[EX.instruction.rs()]);
	auto data = to_signed(EX.sign_extended_data);
    if(rs < data)
    {
        registers[EX.instruction.rt()] = 1;
    }
    else
    {
        registers[EX.instruction.rt()] = 0;
    }
}

void CPU::SLTIU(void)
{
	/* SLTIU rt, rs, immediate
		Compare 16 - bit sign - extended immediate with register rs as
		unsigned 32 - bit integers.Result = 1 if rs is less than immediate;
		otherwise result = 0. Place result in register rt.Do not trap on
		overflow.*/
	auto rs   = registers[EX.instruction.rs()];
	auto data = EX.sign_extended_data;
    if(rs < data)
    {
        registers[EX.instruction.rt()] = 1;
    }
    else
    {
        registers[EX.instruction.rt()] = 0;
    }
}

void CPU::ANDI(void)
{
	/* ANDI rt, rs, immediate
		Zero - extend 16 - bit immediate, AND with contents of register rs
		and place result in register rt.*/
	auto rs  = registers[EX.instruction.rs()];
	auto imm = EX.instruction.imm();
	registers[EX.instruction.rt()] = rs & imm;
}

void CPU::ORI(void)
{
	/* ORI rt, rs, immediate
		Zero - extend 16 - bit immediate, OR with contents of register rs
		and place result in register rt.*/
	auto rs = registers[EX.instruction.rs()];
	auto imm = EX.instruction.imm();
	registers[EX.instruction.rt()] = rs | imm;
}

void CPU::XORI(void)
{
	/* XORI rt, rs, immediate
		Zero - extend 16 - bit immediate, exclusive OR with contents of
		register rs and place result in register rt.*/
	auto rs = registers[EX.instruction.rs()];
	auto imm = EX.instruction.imm();
	registers[EX.instruction.rt()] = rs ^ imm;
}

void CPU::LUI(void)
{
	/* LUI rt, immediate
		Shift 16 - bit immediate left 16 bits.Set least significant 16 bits
		of word to zeroes.Store result in register rt.*/
	auto imm = EX.instruction.imm();
	registers[EX.instruction.rt()] = imm << 16;
}
