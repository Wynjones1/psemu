#include "cpu.h"

// Jump Instructions (J-Type).
void CPU::J(void)
{
	/* J target
		Shift 26 - bit target address left two bits, combine with highorder
		4 bits of PC and jump to address with a one instruction
		delay.*/
	TODO("Implement");

}

void CPU::JAL(void)
{
	/* JAL target
		Shift 26 - bit target address left two bits, combine with highorder
		4 bits of PC and jump to address with a one instruction
		delay.Place address of instruction following delay slot in r31
		(link register).*/
	TODO("Implement");

}

void CPU::JR(void)
{
	/* JR rs
		Jump to address contained in register rs with a one instruction
		delay.*/
	TODO("Implement");

}

void CPU::JALR(void)
{
	/* JALR rs, rd
		Jump to address contained in register rs with a one instruction
		delay.Place address of instruction following delay slot in rd.*/
	TODO("Implement");
}
