#include "support.h"
#include <tuple>

#undef PARAM
#define PARAM std::tuple<SpecialEncoding, uint32_t, uint32_t, uint64_t>

class MultInstructionTest : public InstructionTestFixture<PARAM>{};

TEST_P(MultInstructionTest, Test)
{
    auto param = GetParam();
    instruction = Instruction(OpcodeEncoding::SPECIAL,
                              Register::R1, Register::R2, Register::ZERO, 0, std::get<0>(param));
	cpu.registers[Register::R1] = std::get<1>(param);
	cpu.registers[Register::R2] = std::get<2>(param);
	cpu.registers[Register::R3] = 0;
	cpu.ExecuteInstruction(instruction);
	ASSERT_EQ(std::get<3>(param)         & 0xffffffff, cpu.lo);
	ASSERT_EQ((std::get<3>(param) >> 32) & 0xffffffff, cpu.hi);
}

INSTANTIATE_TEST_CASE_P(
MULT, MultInstructionTest, ::testing::Values(
	PARAM(SpecialEncoding::MULT, -1, -1, 1),
    PARAM(SpecialEncoding::MULT,  0,  0,  0),
    PARAM(SpecialEncoding::MULT,  1,  1,  1),
    PARAM(SpecialEncoding::MULT,  1,  0,  0),
    PARAM(SpecialEncoding::MULT,  0,  1,  0),
    PARAM(SpecialEncoding::MULT,  1, -1, -1),
    PARAM(SpecialEncoding::MULT, -1,  1, -1),
    PARAM(SpecialEncoding::MULT,  2,  2,  4),
    PARAM(SpecialEncoding::MULT, -2,  2, -4),
    PARAM(SpecialEncoding::MULT, INT32_MIN, INT32_MIN, to_unsigned(int64_t(INT32_MIN) * INT32_MIN))
));

INSTANTIATE_TEST_CASE_P(
MULTU, MultInstructionTest, ::testing::Values(
    PARAM(SpecialEncoding::MULTU,  0,  0,  0),
    PARAM(SpecialEncoding::MULTU,  1,  1,  1),
    PARAM(SpecialEncoding::MULTU,  1,  0,  0),
    PARAM(SpecialEncoding::MULTU,  0,  1,  0),
    PARAM(SpecialEncoding::MULTU,  0,  1,  0),
    PARAM(SpecialEncoding::MULTU,  UINT32_MAX, UINT32_MAX,  uint64_t(UINT32_MAX) * UINT32_MAX)
));

#undef PARAM
#define PARAM std::tuple<SpecialEncoding, uint32_t, uint32_t, uint32_t, uint32_t>

class DivInstructionTest : public InstructionTestFixture<PARAM>{};

TEST_P(DivInstructionTest, Test)
{
    auto param = GetParam();
    instruction = Instruction(OpcodeEncoding::SPECIAL,
                              Register::R1, Register::R2, Register::ZERO, 0, std::get<0>(param));
	cpu.registers[Register::R1] = std::get<1>(param);
	cpu.registers[Register::R2] = std::get<2>(param);
	cpu.registers[Register::R3] = 0;
	cpu.ExecuteInstruction(instruction);
	ASSERT_EQ(cpu.lo, std::get<3>(param));
	ASSERT_EQ(cpu.hi, std::get<4>(param));
}

INSTANTIATE_TEST_CASE_P(
DIV, DivInstructionTest, ::testing::Values(
    PARAM(SpecialEncoding::DIV, 0, 0, 0, 0),
    PARAM(SpecialEncoding::DIV, 1, 1, 1, 0),
    PARAM(SpecialEncoding::DIV, 3, 2, 1, 1)
));

INSTANTIATE_TEST_CASE_P(
DIVU, DivInstructionTest, ::testing::Values(
    PARAM(SpecialEncoding::DIVU, 0, 0, 0, 0),
    PARAM(SpecialEncoding::DIVU, 1, 1, 1, 0),
	PARAM(SpecialEncoding::DIVU, 3, 2, 1, 1)
));

#include "generic_special_instruction.h"
class AddSubInstruction : public SpecialInstructionTest {};

INSTANTIATE_TEST_CASE_P(
ADD, AddSubInstruction, ::testing::Values(
    PARAM(SpecialEncoding::ADD, 0, 0, 0, false),
    PARAM(SpecialEncoding::ADD, 1, 1, 2, false)
));

INSTANTIATE_TEST_CASE_P(
ADDU, AddSubInstruction, ::testing::Values(
    PARAM(SpecialEncoding::ADDU, 0,          0, 0, false),
    PARAM(SpecialEncoding::ADDU, 1,          0, 1, false),
    PARAM(SpecialEncoding::ADDU, 1,          1, 2, false),
    PARAM(SpecialEncoding::ADDU, UINT32_MAX, 1, 0, false),
    PARAM(SpecialEncoding::ADDU, 1, UINT32_MAX, 0, false)
));

INSTANTIATE_TEST_CASE_P(
SUB, AddSubInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SUB,  0, 0, 0,  false),
    PARAM(SpecialEncoding::SUB,  1, 1, 0,  false),
    PARAM(SpecialEncoding::SUBU, 1, 2, -1, false),
    PARAM(SpecialEncoding::SUBU, 2, 1,  1, false)
));

INSTANTIATE_TEST_CASE_P(
SUBU, AddSubInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SUBU, 0, 0,  0, false),
    PARAM(SpecialEncoding::SUBU, 1, 1,  0, false),
    PARAM(SpecialEncoding::SUBU, 1, 2, -1, false),
    PARAM(SpecialEncoding::SUBU, 2, 1,  1, false)
));

INSTANTIATE_TEST_CASE_P(
ADD_Overflow, AddSubInstruction, ::testing::Values(
    PARAM(SpecialEncoding::ADD, 1, UINT32_MAX, 0, true),
    PARAM(SpecialEncoding::ADD, UINT32_MAX, 1, 0, true)
));

INSTANTIATE_TEST_CASE_P(
SUB_Overflow, AddSubInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SUB, INT32_MIN,  2, 0, true),
    PARAM(SpecialEncoding::SUB, INT32_MAX, -1, 0, true),
    PARAM(SpecialEncoding::SUB, INT32_MIN,  1, 0, true)
));

