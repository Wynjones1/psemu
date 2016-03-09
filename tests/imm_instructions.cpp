#include "support.h"

#define PARAM std::tuple<OpcodeEncoding, uint32_t, uint16_t, uint32_t, bool>
class ImmediateInstruction : public InstructionTestFixture<PARAM> {};

TEST_P(ImmediateInstruction, Test)
{
	auto param = GetParam();
	instruction = Instruction(std::get<0>(param), Register::R1, Register::R2, std::get<2>(param));
	cpu.registers[Register::R1] = std::get<1>(param);
	cpu.registers[Register::R2] = 0;
	cpu.ExecuteInstruction(instruction);

	auto result = std::get<3>(param);
	auto overflow_bit = std::get<4>(param);
	ASSERT_EQ(result, cpu.registers[Register::R2]);
	ASSERT_EQ(overflow_bit, cpu.debug_state.has_overflown);
}

INSTANTIATE_TEST_CASE_P(
	ADDI, ImmediateInstruction, ::testing::Values(
		PARAM(OpcodeEncoding::ADDI, 0, 0, 0, false),
		PARAM(OpcodeEncoding::ADDI, 1, 0, 1, false),
		PARAM(OpcodeEncoding::ADDI, 1, 1, 2, false),
		PARAM(OpcodeEncoding::ADDI, 2, 1, 3, false),
		PARAM(OpcodeEncoding::ADDI, 1, 2, 3, false),
		PARAM(OpcodeEncoding::ADDI, 0, INT16_MAX, INT16_MAX, false),
		PARAM(OpcodeEncoding::ADDI, 1, INT16_MAX, uint32_t(INT16_MAX) + 1, false),
		PARAM(OpcodeEncoding::ADDI, 1, INT16_MIN, uint32_t(INT16_MIN) + 1, false),
		PARAM(OpcodeEncoding::ADDI, -1, INT16_MIN, uint32_t(INT16_MIN) - 1, false)
));

INSTANTIATE_TEST_CASE_P(
	ADDI_PosOverflow, ImmediateInstruction, ::testing::Values(
		PARAM(OpcodeEncoding::ADDI, INT32_MAX, 1, 0, true),
		PARAM(OpcodeEncoding::ADDI, INT32_MAX, INT16_MAX, 0, true)
));

INSTANTIATE_TEST_CASE_P(
	ADDI_NegOverflow, ImmediateInstruction, ::testing::Values(
		PARAM(OpcodeEncoding::ADDI, INT32_MIN, -1, 0, true)
));

INSTANTIATE_TEST_CASE_P(
	ADDIU, ImmediateInstruction, ::testing::Values(
		PARAM(OpcodeEncoding::ADDIU, 0, 0, 0, false),
		PARAM(OpcodeEncoding::ADDIU, 1, 0, 1, false),
		PARAM(OpcodeEncoding::ADDIU, 1, 1, 2, false),
		PARAM(OpcodeEncoding::ADDIU, 1, 1, 2, false),
		PARAM(OpcodeEncoding::ADDIU, 0, INT16_MAX, INT16_MAX, false),
		PARAM(OpcodeEncoding::ADDIU, 1, INT16_MAX, uint32_t(INT16_MAX) + 1, false)
));

INSTANTIATE_TEST_CASE_P(
	ADDIU_Overflow, ImmediateInstruction, ::testing::Values(
		PARAM(OpcodeEncoding::ADDIU, UINT32_MAX, INT16_MAX, INT16_MAX - 1, false),
		PARAM(OpcodeEncoding::ADDIU, 0, INT16_MIN, INT16_MIN, false)
));

INSTANTIATE_TEST_CASE_P(
	ANDI, ImmediateInstruction, ::testing::Values(
		PARAM(OpcodeEncoding::ANDI, 0, 0, 0,       false),
		PARAM(OpcodeEncoding::ANDI, 0xf, 0xf, 0xf, false),
		PARAM(OpcodeEncoding::ANDI, 0xffff, 0xffff, 0xffff, false),
		PARAM(OpcodeEncoding::ANDI, 0xffffffff, 0xffff, 0xffff, false)
));

INSTANTIATE_TEST_CASE_P(
	ORI, ImmediateInstruction, ::testing::Values(
		PARAM(OpcodeEncoding::ORI, 0, 0, 0, false),
		PARAM(OpcodeEncoding::ORI, 0x0f, 0xf0, 0xff, false),
		PARAM(OpcodeEncoding::ORI, 0x0, 0xffff, 0xffff, false),
		PARAM(OpcodeEncoding::ORI, 0xffff0000, 0xffff, 0xffffffff, false)
));

INSTANTIATE_TEST_CASE_P(
	XORI, ImmediateInstruction, ::testing::Values(
		PARAM(OpcodeEncoding::XORI, 0, 0, 0, false),
		PARAM(OpcodeEncoding::XORI, 0xcf, 0x0f, 0xc0, false)
));

INSTANTIATE_TEST_CASE_P(
	LUI, ImmediateInstruction, ::testing::Values(
		PARAM(OpcodeEncoding::LUI, 0, 0x0, 0, false),
		PARAM(OpcodeEncoding::LUI, 0,  0xf, 0xf << 16, false),
		PARAM(OpcodeEncoding::LUI, 1,  0xf, 0xf << 16, false),
		PARAM(OpcodeEncoding::LUI, -1, 0xf, 0xf << 16, false),
		PARAM(OpcodeEncoding::LUI, 0, 0x1, 0x1 << 16, false),
		PARAM(OpcodeEncoding::LUI, 1, 0x1, 0x1 << 16, false),
		PARAM(OpcodeEncoding::LUI, -1, 0x1, 0x1 << 16, false)
));