#include "gtest/gtest.h"
#include "cpu.h"
#include "memory.h"

TEST(InstructionAND, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::AND);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 0xffffffff;
	cpu.registers[Register::R2] = 0xffffffff;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 0xffffffff);
}

TEST(InstructionOR, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::OR);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 0x0f0f0f0f;
	cpu.registers[Register::R2] = 0xf0f0f0f0;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 0xffffffff);
}

TEST(InstructionXOR, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::XOR);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 0x0f0f0f0f;
	cpu.registers[Register::R2] = 0xf0f0f0f0;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], 0x0f0f0f0f ^ 0xf0f0f0f0);
}

TEST(InstructionNOR, Test0)
{
	Memory memory;
	auto instr = Instruction(OpcodeEncoding::SPECIAL, Register::R1, Register::R2, Register::R3, 0, SpecialEncoding::NOR);
	auto cpu = CPU(memory);
	cpu.registers[Register::R1] = 0xf0f0f0f0;
	cpu.registers[Register::R2] = 0xf0f0f0f0;
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instr);

	ASSERT_EQ(cpu.registers[Register::R3], ~uint32_t(0xf0f0f0f0 | 0xf0f0f0f0));
}