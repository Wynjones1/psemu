#include "gtest/gtest.h"
#include "cpu.h"
#include "memory.h"
#if 1

TEST(InstructionADDI, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::ADDI, Register::R1, Register::R2, 10);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 10;
	cpu.registers[Register::R2] = 0;
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
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::ADDIU, Register::R1, Register::R2, 10);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 10;
	cpu.registers[Register::R2] = 0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R2], 20);
	ASSERT_FALSE(cpu.debug_state.has_overflown);
}

TEST(InstructionADDIU, Test1)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::ADDIU, Register::R1, Register::R2, INT16_MAX);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = UINT32_MAX;
	cpu.registers[Register::R2] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R2], uint32_t(INT16_MAX) + UINT32_MAX);
	ASSERT_FALSE(cpu.debug_state.has_overflown);
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
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::ANDI, Register::R1, Register::R2, UINT16_MAX);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = UINT32_MAX;
	cpu.registers[Register::R2] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R2], UINT16_MAX);
}

TEST(InstructionORI, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::ORI, Register::R1, Register::R2, 0x0f0f);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 0x1234f0f0;
	cpu.registers[Register::R2] = 0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R2], 0x1234ffff);
}

TEST(InstructionXORI, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::XORI, Register::R1, Register::R2, 0x0f0f);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 0x1234f0f0;
	cpu.registers[Register::R2] = 0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R2], 0x0000f0f0 ^ 0x0f0f);
}

TEST(InstructionLUI, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::LUI, Register::ZERO, Register::R2, UINT16_MAX);
	auto cpu = CPU(memory);
	cpu.registers[Register::R2] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R2], uint32_t(UINT16_MAX) << 16);
}
#endif
