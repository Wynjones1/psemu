#include "support.h"

#define PARAM std::tuple<SpecialEncoding, uint32_t, uint8_t, uint32_t>
class ShiftImmediateInstruction : public InstructionTestFixture<PARAM>{};

TEST_P(ShiftImmediateInstruction, Test)
{
    auto param = GetParam();
	instruction = Instruction(OpcodeEncoding::SPECIAL,
                              Register::ZERO, Register::R1, Register::R3,
                              std::get<2>(param), std::get<0>(param));
	cpu.registers[Register::R1] = std::get<1>(param);
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instruction);

    auto result = std::get<3>(param);
	ASSERT_EQ(cpu.registers[Register::R3], result);
}

INSTANTIATE_TEST_CASE_P(
SLL, ShiftImmediateInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SLL, 0x0, 0,  0x00),
    PARAM(SpecialEncoding::SLL, 0x1, 0,  0x01),
    PARAM(SpecialEncoding::SLL, 0x1, 1,  0x02),
    PARAM(SpecialEncoding::SLL, 0x1, 2,  0x04),
    PARAM(SpecialEncoding::SLL, 0xf, 4,  0xf0)
));

INSTANTIATE_TEST_CASE_P(
SLL_MaxShift, ShiftImmediateInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SLL, 0x1, 31, 1 << 31),
    PARAM(SpecialEncoding::SLL, -1,  31, 1 << 31)
));


INSTANTIATE_TEST_CASE_P(
SRA, ShiftImmediateInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SRA,  0, 0,  0),
    PARAM(SpecialEncoding::SRA,  0, 1,  0),
    PARAM(SpecialEncoding::SRA,  1, 1,  0),
    PARAM(SpecialEncoding::SRA, -1, 1, -1),
    PARAM(SpecialEncoding::SRA, -2, 1, -1),
    PARAM(SpecialEncoding::SRA,  2, 1,  1),
    PARAM(SpecialEncoding::SRA,  3, 1,  1),
    PARAM(SpecialEncoding::SRA,  4, 1,  2)
));

INSTANTIATE_TEST_CASE_P(
SRA_MaxShift, ShiftImmediateInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SRA, -1,          31, -1),
    PARAM(SpecialEncoding::SRA,  0,          31,  0),
    PARAM(SpecialEncoding::SRA,  1,          31,  0),
    PARAM(SpecialEncoding::SRA,  0xefffffff, 31,  0)
));

INSTANTIATE_TEST_CASE_P(
SRL, ShiftImmediateInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SRA,  0, 0,  0),
    PARAM(SpecialEncoding::SRA,  0, 1,  0),
    PARAM(SpecialEncoding::SRA,  1, 1,  0),
    PARAM(SpecialEncoding::SRA, -1, 1, -1),
    PARAM(SpecialEncoding::SRA, -2, 1, -1),
    PARAM(SpecialEncoding::SRA,  2, 1,  1),
    PARAM(SpecialEncoding::SRA,  3, 1,  1),
    PARAM(SpecialEncoding::SRA,  4, 1,  2)
));

INSTANTIATE_TEST_CASE_P(
SRL_MaxShift, ShiftImmediateInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SRA, -1, 31, 0),
    PARAM(SpecialEncoding::SRA,  0, 31, 0)
));

#include "generic_special_instruction.h"
class ShiftRegisterInstruction: public SpecialInstructionTest{};

/* TEST_P(ShiftRegisterInstruction, Test) */
/* TEST_P(SpecialInstructionTest,   Test) */

INSTANTIATE_TEST_CASE_P(
SLLV, ShiftRegisterInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SLLV, 0x0, 0,  0x00, false),
    PARAM(SpecialEncoding::SLLV, 0x1, 0,  0x01, false),
    PARAM(SpecialEncoding::SLLV, 0x1, 1,  0x02, false),
    PARAM(SpecialEncoding::SLLV, 0x1, 2,  0x04, false),
    PARAM(SpecialEncoding::SLLV, 0xf, 4,  0xf0, false)
));

INSTANTIATE_TEST_CASE_P(
SLLV_MaxShift, ShiftRegisterInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SLLV, 0x1, 31, 1 << 31, false),
    PARAM(SpecialEncoding::SLLV, -1,  31, 1 << 31, false)
));


INSTANTIATE_TEST_CASE_P(
SRAV, ShiftRegisterInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SRAV, 0, 0, 0, false)
));

INSTANTIATE_TEST_CASE_P(
SRLV, ShiftRegisterInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SRLV, 0, 0, 0, false)
));
