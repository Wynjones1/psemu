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
	ASSERT_EQ(result, cpu.registers[Register::R3]);
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
    PARAM(SpecialEncoding::SRA,  INT32_MAX,  31,  0)
));

INSTANTIATE_TEST_CASE_P(
SRL, ShiftImmediateInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SRL,  0, 0,  0),
    PARAM(SpecialEncoding::SRL,  0, 1,  0),
    PARAM(SpecialEncoding::SRL,  1, 1,  0),
    PARAM(SpecialEncoding::SRL, -1, 1, to_unsigned(-1) >> 1),
    PARAM(SpecialEncoding::SRL, -2, 1, to_unsigned(-2) >> 1),
    PARAM(SpecialEncoding::SRL,  2, 1,  1),
    PARAM(SpecialEncoding::SRL,  3, 1,  1),
    PARAM(SpecialEncoding::SRL,  4, 1,  2)
));

INSTANTIATE_TEST_CASE_P(
SRL_MaxShift, ShiftImmediateInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SRL, -1, 31, 1),
    PARAM(SpecialEncoding::SRL,  0, 31, 0)
));

#include "generic_special_instruction.h"

INSTANTIATE_TEST_CASE_P(
SLLV, SpecialInstructionTest, ::testing::Values(
    PARAM(SpecialEncoding::SLLV, 0, 0x0, 0x00, false),
    PARAM(SpecialEncoding::SLLV, 0, 0x1, 0x01, false),
    PARAM(SpecialEncoding::SLLV, 1, 0x1, 0x02, false),
    PARAM(SpecialEncoding::SLLV, 2, 0x1, 0x04, false),
    PARAM(SpecialEncoding::SLLV, 4, 0xf, 0xf0, false)
));

INSTANTIATE_TEST_CASE_P(
SLLV_MaxShift, SpecialInstructionTest, ::testing::Values(
    PARAM(SpecialEncoding::SLLV, 31, 0x1, 1 << 31, false),
    PARAM(SpecialEncoding::SLLV, 31, -1,  1 << 31, false)
));


INSTANTIATE_TEST_CASE_P(
SRAV, SpecialInstructionTest, ::testing::Values(
    PARAM(SpecialEncoding::SRAV, 0,  0,          0,          false),
    PARAM(SpecialEncoding::SRAV, 1,  0x80000000, 0xc0000000, false),
    PARAM(SpecialEncoding::SRAV, 1,  0xffffffff, 0xffffffff, false),
    PARAM(SpecialEncoding::SRAV, 4,  0x0fffffff, 0x00ffffff, false),
    PARAM(SpecialEncoding::SRAV, 32, 0x0fffffff, 0x0fffffff, false),
    PARAM(SpecialEncoding::SRAV, 36, 0x0fffffff, 0x00ffffff, false)
));

INSTANTIATE_TEST_CASE_P(
SRLV, SpecialInstructionTest, ::testing::Values(
    PARAM(SpecialEncoding::SRLV, 0,  0,          0,          false),
    PARAM(SpecialEncoding::SRLV, 1,  0x80000000, 0x40000000, false),
    PARAM(SpecialEncoding::SRLV, 1,  0xffffffff, 0x7fffffff, false),
    PARAM(SpecialEncoding::SRLV, 4,  0x0fffffff, 0x00ffffff, false),
    PARAM(SpecialEncoding::SRLV, 32, 0x0fffffff, 0x0fffffff, false),
    PARAM(SpecialEncoding::SRLV, 36, 0x0fffffff, 0x00ffffff, false)
));
