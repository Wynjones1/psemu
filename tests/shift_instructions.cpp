#include "gtest/gtest.h"
#include "cpu.h"
#include "memory.h"


TEST(InstructionSLT, True0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 5, SpecialEncoding::SLT);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 10;
	cpu.registers[Register::R2] = 11;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 1);
}

TEST(InstructionSLT, False0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 5, SpecialEncoding::SLT);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 11;
	cpu.registers[Register::R2] = 10;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 0);
}

TEST(InstructionSLTU, True0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 5, SpecialEncoding::SLTU);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 10;
	cpu.registers[Register::R2] = 11;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 1);
}

TEST(InstructionSLTU, False0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 5, SpecialEncoding::SLTU);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 11;
	cpu.registers[Register::R2] = 10;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 0);
}

TEST(InstructionSLTU, True1)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 5, SpecialEncoding::SLTU);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = conv_to_unsigned(-10);
	cpu.registers[Register::R2] = 10;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 1);
}

TEST(InstructionSLTU, False1)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 5, SpecialEncoding::SLTU);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 10;
	cpu.registers[Register::R2] = conv_to_unsigned(-10);;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 0);
}

TEST(InstructionSLL, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::ZERO, Register::R2, Register::R3, 5, SpecialEncoding::SLL);
	auto cpu = CPU(memory);
	cpu.registers[Register::R2] = 0xf0f0f0f0;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 0xf0f0f0f0 << 5);
}

TEST(InstructionSRL, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::ZERO, Register::R2, Register::R3, 5, SpecialEncoding::SRL);
	auto cpu = CPU(memory);
	cpu.registers[Register::R2] = 0xf0f0f0f0;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 0xf0f0f0f0 >> 5);
}

TEST(InstructionSRA, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::ZERO, Register::R2, Register::R3, 5, SpecialEncoding::SRA);
	auto cpu = CPU(memory);
	cpu.registers[Register::R2] = 0x00f0f0f0;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 0x00f0f0f0 >> 5);
}

TEST(InstructionSRA, Test1)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::ZERO, Register::R2, Register::R3, 5, SpecialEncoding::SRA);
	auto cpu = CPU(memory);
	cpu.registers[Register::R2] = 0xffffffff;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	// Sign bit should be preserved.
	ASSERT_EQ(cpu.registers[Register::R3], 0xffffffff);
}

TEST(InstructionSLLV, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::SLLV);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 7;
	cpu.registers[Register::R2] = 0xf0f0f0f0;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 0xf0f0f0f0 << 7);
}

TEST(InstructionSLLV, MaxShift)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::SLLV);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = (1 << 5) - 1;
	cpu.registers[Register::R2] = 0xf0f0f0f0;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 0xf0f0f0f0 << ((1 << 5) - 1));
}

TEST(InstructionSRLV, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::SRLV);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 7;
	cpu.registers[Register::R2] = 0xf0f0f0f0;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 0xf0f0f0f0 >> 7);
}

TEST(InstructionSRAV, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::SRAV);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 7;
	cpu.registers[Register::R2] = 0x00f0f0f0;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	// Sign bit should be preserved.
	ASSERT_EQ(cpu.registers[Register::R3], 0x00f0f0f0 >> 7);
}

TEST(InstructionSRAV, Test1)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::SRAV);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 7;
	cpu.registers[Register::R2] = 0xf0f0f0f0;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	// Sign bit should be preserved.
	ASSERT_EQ(cpu.registers[Register::R3], 0xf0f0f0f0 >> 7 | mask(31, 31 - 6));
}