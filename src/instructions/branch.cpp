#include "cpu.h"

// Branch Instructions (J-Type).
void CPU::BEQ(void)
{
	/* BEQ rs, rt, offset
		Branch to target address if register rs equal to rt*/
	TODO("Implement");

}

void CPU::BNE(void)
{
	/* BNE rs, rt, offset
		Branch to target address if register rs not equal to rt.*/
	TODO("Implement");

}

void CPU::BLEZ(void)
{
	/* BLEZ rs, offset
		Branch to target address if register rs less than or equal to 0.*/
	TODO("Implement");

}

void CPU::BGTZ(void)
{
	/* BGTZ rs, offset
		Branch to target address if register rs greater than 0.*/
	TODO("Implement");

}

void CPU::BLTZ(void)
{
	/* BLTZ rs, offset
		Branch to target address if register rs less than 0.*/
	TODO("Implement");

}

void CPU::BGEZ(void)
{
	/* BGEZ rs, offset
		Branch to target address if register rs greater than or equal to 0.*/
	TODO("Implement");

}

void CPU::BLTZAL(void)
{
	/* BLTZAL rs, offset
		Place address of instruction following delay slot in register r31
		(link register).Branch to target address if register rs less than 0.*/
	TODO("Implement");

}

void CPU::BGEZAL(void)
{
	/* BGEZAL rs, offset
		Place address of instruction following delay slot in register r31
		(link register).Branch to target address if register rs is greater
		than or equal to 0.*/
	TODO("Implement");
}
