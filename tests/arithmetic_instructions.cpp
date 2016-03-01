#include "gtest/gtest.h"
#include "cpu.h"
#include "memory.h"

TEST(InstructionMULT, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::ZERO, 0, SpecialEncoding::MULT);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 100;
	cpu.registers[Register::R2] = 10;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.lo, 1000);
	ASSERT_EQ(cpu.hi, 0);
}

TEST(InstructionMULT, Test1)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::ZERO, 0, SpecialEncoding::MULT);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = conv_to_unsigned(-100);
	cpu.registers[Register::R2] = 10;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.lo, conv_to_unsigned(-1000));
	ASSERT_EQ(cpu.hi, 0);
}

TEST(InstructionMULT, LargestMult0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::ZERO, 0, SpecialEncoding::MULT);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = INT32_MAX;
	cpu.registers[Register::R2] = INT32_MAX;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	uint64_t temp = uint64_t(INT32_MAX) * INT32_MAX;
	ASSERT_EQ(cpu.lo, temp & 0xffffffff);
	ASSERT_EQ(cpu.hi, (temp >> 32) & 0xffffffff);
}

TEST(InstructionMULT, LargestMult1)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::ZERO, 0, SpecialEncoding::MULT);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = INT32_MIN;
	cpu.registers[Register::R2] = INT32_MAX;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	int64_t temp = int64_t(INT32_MAX) * INT32_MIN;
	ASSERT_EQ(cpu.lo, conv_to_unsigned(temp) & 0xffffffff);
	ASSERT_EQ(cpu.hi, (conv_to_unsigned(temp) >> 32) & 0xffffffff);
}

TEST(InstructionMULT, LargestMult2)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::ZERO, 0, SpecialEncoding::MULT);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = INT32_MIN;
	cpu.registers[Register::R2] = INT32_MIN;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	int64_t temp = int64_t(INT32_MIN) * INT32_MIN;
	ASSERT_EQ(cpu.lo, conv_to_unsigned(temp) & 0xffffffff);
	ASSERT_EQ(cpu.hi, (conv_to_unsigned(temp) >> 32) & 0xffffffff);
}

TEST(InstructionMULTU, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::ZERO, 0, SpecialEncoding::MULTU);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 100;
	cpu.registers[Register::R2] = 10;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.lo, 1000);
	ASSERT_EQ(cpu.hi, 0);
}

TEST(InstructionMULTU, LargestMult)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::ZERO, 0, SpecialEncoding::MULTU);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = UINT32_MAX;
	cpu.registers[Register::R2] = UINT32_MAX;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	uint64_t temp = uint64_t(UINT32_MAX) * UINT32_MAX;
	ASSERT_EQ(cpu.lo, temp & 0xffffffff);
	ASSERT_EQ(cpu.hi, (temp >> 32) & 0xffffffff);
}

TEST(InstructionMULTU, WaitTwoClocks)
{
	FAIL();
}

TEST(InstructionDIVU, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::ZERO, 0, SpecialEncoding::DIVU);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 100;
	cpu.registers[Register::R2] = 10;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.lo, 10);
	ASSERT_EQ(cpu.hi, 0);
}

TEST(InstructionDIVU, Test1)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::ZERO, 0, SpecialEncoding::DIVU);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 100;
	cpu.registers[Register::R2] = 11;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.lo, 100 / 11);
	ASSERT_EQ(cpu.hi, 100 % 11);
}

TEST(InstructionDIV, WaitTwoClockCycles)
{
	FAIL();
}

TEST(InstructionDIV, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::ZERO, 0, SpecialEncoding::DIV);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 100;
	cpu.registers[Register::R2] = 10;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.lo, 10);
	ASSERT_EQ(cpu.hi, 0);
}

TEST(InstructionDIV, Test1)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::ZERO, 0, SpecialEncoding::DIV);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = conv_to_unsigned(-100);
	cpu.registers[Register::R2] = 10;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.lo, conv_to_unsigned(-10));
	ASSERT_EQ(cpu.hi, 0);
}

TEST(InstructionDIVU, WaitTwoClockCycles)
{
	FAIL();
}

TEST(InstructionADD, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::ADD);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 10;
	cpu.registers[Register::R2] = 11;
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
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::ADDU);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 10;
	cpu.registers[Register::R2] = 10;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 20);
	ASSERT_FALSE(cpu.debug_state.has_overflown);
}

TEST(InstructionADDU, Overflow0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::ADDU);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 0xffffffff;
	cpu.registers[Register::R2] = 0xffffffff;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 0xfffffffe);
	ASSERT_FALSE(cpu.debug_state.has_overflown);
}

TEST(InstructionSUB, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::SUB);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 10;
	cpu.registers[Register::R2] = 10;
	cpu.registers[Register::R3] = 1123;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 0);
	ASSERT_FALSE(cpu.debug_state.has_overflown);
}

TEST(InstructionSUB, Test1)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::SUB);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 10;
	cpu.registers[Register::R2] = conv_to_unsigned(-10);
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 20);
	ASSERT_FALSE(cpu.debug_state.has_overflown);
}

TEST(InstructionSUB, Test2)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::SUB);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = conv_to_unsigned(-10);
	cpu.registers[Register::R2] = 10;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], conv_to_unsigned(-20));
	ASSERT_FALSE(cpu.debug_state.has_overflown);
}

TEST(InstructionSUBU, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::SUBU);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 10;
	cpu.registers[Register::R2] = 10;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 0);
	ASSERT_FALSE(cpu.debug_state.has_overflown);
}

TEST(InstructionSUBU, Test1)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::SUBU);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 10;
	cpu.registers[Register::R2] = conv_to_unsigned(-10);
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 20);
	ASSERT_FALSE(cpu.debug_state.has_overflown);
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