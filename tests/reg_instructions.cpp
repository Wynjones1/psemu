#include "gtest/gtest.h"
#include "cpu.h"
#include "memory.h"

TEST(InstructionSLL, Test0)
{
	FAIL();
}

TEST(InstructionSRL, Test0)
{
	FAIL();
}

TEST(InstructionSRA, Test0)
{
	FAIL();
}

TEST(InstructionSLLV, Test0)
{
	FAIL();
}

TEST(InstructionSRLV, Test0)
{
	FAIL();
}

TEST(InstructionSRAV, Test0)
{
	FAIL();
}

TEST(InstructionJR, Test0)
{
	FAIL();
}

TEST(InstructionJALR, Test0)
{
	FAIL();
}

TEST(InstructionSYSCALL, Test0)
{
	FAIL();
}

TEST(InstructionBREAK, Test0)
{
	FAIL();
}

TEST(InstructionMFHI, Test0)
{
	FAIL();
}

TEST(InstructionMTHI, Test0)
{
	FAIL();
}

TEST(InstructionMFLO, Test0)
{
	FAIL();
}

TEST(InstructionMTLO, Test0)
{
	FAIL();
}

TEST(InstructionMULT, Test0)
{
	FAIL();
}

TEST(InstructionMULTU, Test0)
{
	FAIL();
}

TEST(InstructionDIV, Test0)
{
	FAIL();
}

TEST(InstructionDIVU, Test0)
{
	FAIL();
}

TEST(InstructionADD, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::ADD);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 10;
	cpu.registers[Register::R2] = 10;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 20);
	ASSERT_FALSE(cpu.debug_state.has_overflown);
}

TEST(InstructionADD, Overflow0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::ADD);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 0xffffffff;
	cpu.registers[Register::R2] = 0xffffffff;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	/* The value in the register should be unchanged due to the overflow. */
	ASSERT_EQ(cpu.registers[Register::R3], 0);
	ASSERT_TRUE(cpu.debug_state.has_overflown);
}

TEST(InstructionADDU, Test0)
{
	FAIL();
}

TEST(InstructionSUB, Test0)
{
	FAIL();
}

TEST(InstructionSUBU, Test0)
{
	FAIL();
}

TEST(InstructionAND, Test0)
{
	FAIL();
}

TEST(InstructionOR, Test0)
{
	FAIL();
}

TEST(InstructionXOR, Test0)
{
	FAIL();
}

TEST(InstructionNOR, Test0)
{
	FAIL();
}

TEST(InstructionSLT, Test0)
{
	FAIL();
}

TEST(InstructionSLTU, Test0)
{
	FAIL();
}

TEST(InstructionBLTZ, Test0)
{
	FAIL();
}

TEST(InstructionBGEZ, Test0)
{
	FAIL();
}

TEST(InstructionBLTZAL, Test0)
{
	FAIL();
}

TEST(InstructionBGEZAL, Test0)
{
	FAIL();
}

TEST(InstructionJ, Test0)
{
	FAIL();
}

TEST(InstructionJAL, Test0)
{
	FAIL();
}

TEST(InstructionBEQ, Test0)
{
	FAIL();
}

TEST(InstructionBNE, Test0)
{
	FAIL();
}

TEST(InstructionBLEZ, Test0)
{
	FAIL();
}

TEST(InstructionBGTZ, Test0)
{
	FAIL();
}

TEST(InstructionADDI, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::ADDI, Register::R1, Register::R2, 10);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 0x10;
	cpu.registers[Register::R2] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R2], 20);
}

TEST(InstructionADDI, PosOverflow0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::ADDI, Register::R1, Register::R2, 1);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = INT32_MAX;
	cpu.registers[Register::R2] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R2], 0);
	ASSERT_TRUE(cpu.debug_state.has_overflown);
}

TEST(InstructionADDI, PosOverflow1)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::ADDI, Register::R1, Register::R2, INT16_MAX);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = INT32_MAX - INT16_MAX + 1;
	cpu.registers[Register::R2] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R2], 0);
	ASSERT_TRUE(cpu.debug_state.has_overflown);
}

TEST(InstructionADDI, NegOverflow0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::ADDI, Register::R1, Register::R2, INT16_MIN);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = INT32_MIN;
	cpu.registers[Register::R2] = 0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R2], 0);
	ASSERT_TRUE(cpu.debug_state.has_overflown);
}

TEST(InstructionADDIU, Test0)
{
	FAIL();
}

TEST(InstructionSUBI, Test0)
{
	FAIL();
}

TEST(InstructionSUBIU, Test0)
{
	FAIL();
}

TEST(InstructionANDI, Test0)
{
	FAIL();
}

TEST(InstructionORI, Test0)
{
	FAIL();
}

TEST(InstructionXORI, Test0)
{
	FAIL();
}

TEST(InstructionLUI, Test0)
{
	FAIL();
}

TEST(InstructionMFC0, Test0)
{
	FAIL();
}

TEST(InstructionMTC0, Test0)
{
	FAIL();
}

TEST(InstructionBC0F, Test0)
{
	FAIL();
}

TEST(InstructionBC0T, Test0)
{
	FAIL();
}

TEST(InstructionTLBR, Test0)
{
	FAIL();
}

TEST(InstructionTLBWI, Test0)
{
	FAIL();
}

TEST(InstructionTLBWR, Test0)
{
	FAIL();
}

TEST(InstructionTLBP, Test0)
{
	FAIL();
}

TEST(InstructionRFE, Test0)
{
	FAIL();
}

TEST(InstructionLB, Test0)
{
	FAIL();
}

TEST(InstructionLH, Test0)
{
	FAIL();
}

TEST(InstructionLWL, Test0)
{
	FAIL();
}

TEST(InstructionLW, Test0)
{
	FAIL();
}

TEST(InstructionLBU, Test0)
{
	FAIL();
}

TEST(InstructionLHU, Test0)
{
	FAIL();
}

TEST(InstructionLWR, Test0)
{
	FAIL();
}

TEST(InstructionSB, Test0)
{
	FAIL();
}

TEST(InstructionSH, Test0)
{
	FAIL();
}

TEST(InstructionSWL, Test0)
{
	FAIL();
}

TEST(InstructionSW, Test0)
{
	FAIL();
}

TEST(InstructionSWR, Test0)
{
	FAIL();
}

TEST(InstructionSWC1, Test0)
{
	FAIL();
}

TEST(InstructionLWC1, Test0)
{
	FAIL();
}


/*
SLL
SRL
SRA
SLLV
SRLV
SRAV
JR
JALR
SYSCALL
BREAK
MFHI
MTHI
MFLO
MTLO
MULT
MULTU
DIV
DIVU
ADD
ADDU
SUB
SUBU
AND
OR
XOR
NOR
SLT
SLTU
BLTZ
BGEZ
BLTZAL
BGEZAL
J
JAL
BEQ
BNE
BLEZ
BGTZ
ADDI
ADDIU
SUBI
SUBIU
ANDI
ORI
XORI
LUI
MFC0
MTC0
BC0F
BC0T
TLBR
TLBWI
TLBWR
TLBP
RFE
LB
LH
LWL
LW
LBU
LHU
LWR
SB
SH
SWL
SW
SWR
SWC1
LWC1
*/