#ifndef GENERIC_SPECIAL_INSTRUCTION
#define GENERIC_SPECIAL_INSTRUCTION
#undef PARAM
#define PARAM std::tuple<SpecialEncoding, uint32_t, uint32_t, uint32_t, bool>
class SpecialInstructionTest : public InstructionTestFixture<PARAM>{};

TEST_P(SpecialInstructionTest, Test)
{
    auto param = GetParam();
    instruction = Instruction(OpcodeEncoding::SPECIAL,
                              Register::R1, Register::R2, Register::R3, 0, std::get<0>(param));
	cpu.registers[Register::R1] = std::get<1>(param);
	cpu.registers[Register::R2] = std::get<2>(param);
	cpu.registers[Register::R3] = 0;
	cpu.ExecuteInstruction(instruction);
    bool overflow_bit_expected = std::get<4>(param);
    ASSERT_EQ(overflow_bit_expected, cpu.debug_state.has_overflown);
	ASSERT_EQ(std::get<3>(param), cpu.registers[Register::R3]);
}

#endif
