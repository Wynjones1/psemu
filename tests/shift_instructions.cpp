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
    PARAM(SpecialEncoding::SLL, 0, 0, 0)
));



INSTANTIATE_TEST_CASE_P(
SRA, ShiftImmediateInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SRA, 0, 0, 0)
));

INSTANTIATE_TEST_CASE_P(
SRL, ShiftImmediateInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SRL, 0, 0, 0)
));

#undef PARAM
#define PARAM std::tuple<SpecialEncoding, uint32_t, uint8_t, uint32_t>
class ShiftRegisterInstruction: public InstructionTestFixture<PARAM>{};

TEST_P(ShiftRegisterInstruction, Test)
{
    auto param = GetParam();
	instruction = Instruction(OpcodeEncoding::SPECIAL,
                              Register::R1, Register::R2, Register::R3, std::get<2>(param), std::get<0>(param));
	cpu.registers[Register::R1] = std::get<2>(param);
	cpu.registers[Register::R2] = std::get<1>(param);
	cpu.registers[Register::R3] = 0x0;
	cpu.ExecuteInstruction(instruction);

    auto result = std::get<3>(param);
	ASSERT_EQ(cpu.registers[Register::R3], result);
}

INSTANTIATE_TEST_CASE_P(
SLLV, ShiftRegisterInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SLLV, 0, 0, 0)
));

INSTANTIATE_TEST_CASE_P(
SRAV, ShiftRegisterInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SRAV, 0, 0, 0)
));

INSTANTIATE_TEST_CASE_P(
SRLV, ShiftRegisterInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SRLV, 0, 0, 0)
));
