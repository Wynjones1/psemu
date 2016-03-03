#include "support.h"
#include <tuple>

#define PARAM std::tuple<SpecialEncoding, uint32_t, uint32_t, uint64_t>

class MultDivInstruction : public InstructionTestFixture<PARAM>{};

TEST_P(MultDivInstruction, Test)
{
    auto param = GetParam();
    instruction = Instruction(OpcodeEncoding::SPECIAL,
                              Register::R1, Register::R2, Register::ZERO, 0, std::get<0>(param));
	cpu.registers[Register::R1] = std::get<1>(param);
	cpu.registers[Register::R2] = std::get<2>(param);
	cpu.registers[Register::R3] = 0;
	cpu.ExecuteInstruction(instruction);
	ASSERT_EQ(cpu.lo, std::get<3>(param) & 0xffffffff);
	ASSERT_EQ(cpu.hi, (std::get<3>(param) >> 32) & 0xffffffff);
}

INSTANTIATE_TEST_CASE_P(
MULT, MultDivInstruction, ::testing::Values(
    PARAM(SpecialEncoding::MULT, 0, 0, 0),
    PARAM(SpecialEncoding::MULT, 1, 1, 1)
));

INSTANTIATE_TEST_CASE_P(
MULTU, MultDivInstruction, ::testing::Values(
    PARAM(SpecialEncoding::MULTU, 0, 0, 0),
    PARAM(SpecialEncoding::MULTU, 1, 1, 1)
));

INSTANTIATE_TEST_CASE_P(
DIV, MultDivInstruction, ::testing::Values(
    PARAM(SpecialEncoding::DIV, 0, 0, 0),
    PARAM(SpecialEncoding::DIV, 1, 1, 1)
));

INSTANTIATE_TEST_CASE_P(
DIVU, MultDivInstruction, ::testing::Values(
    PARAM(SpecialEncoding::DIVU, 0, 0, 0),
    PARAM(SpecialEncoding::DIVU, 1, 1, 1)
));

#undef PARAM
#define PARAM std::tuple<SpecialEncoding, uint32_t, uint32_t, uint32_t, bool>
class AddSubInstruction : public InstructionTestFixture<PARAM>{};

TEST_P(AddSubInstruction, Test)
{
    auto param = GetParam();
    instruction = Instruction(OpcodeEncoding::SPECIAL,
                              Register::R1, Register::R2, Register::R3, 0, std::get<0>(param));
	cpu.registers[Register::R1] = std::get<1>(param);
	cpu.registers[Register::R2] = std::get<2>(param);
	cpu.registers[Register::R3] = 0;
	cpu.ExecuteInstruction(instruction);
	ASSERT_EQ(cpu.registers[Register::R3], std::get<3>(param));
    ASSERT_EQ(cpu.debug_state.has_overflown, std::get<4>(param));
}

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
    PARAM(SpecialEncoding::SUB, 0, 0, 0, false),
    PARAM(SpecialEncoding::SUB, 1, 1, 0, false)
));

INSTANTIATE_TEST_CASE_P(
SUBU, AddSubInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SUBU, 0, 0, 0, false),
    PARAM(SpecialEncoding::SUBU, 1, 1, 0, false)
));

INSTANTIATE_TEST_CASE_P(
ADD_Overflow, AddSubInstruction, ::testing::Values(
    PARAM(SpecialEncoding::ADD, 1, UINT32_MAX, 0, true),
    PARAM(SpecialEncoding::ADD, UINT32_MAX, 1, 0, true)
));

INSTANTIATE_TEST_CASE_P(
SUB_Overflow, AddSubInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SUB, 1,          2, 0, true),
    PARAM(SpecialEncoding::SUB, INT32_MAX, -1, 0, true),
    PARAM(SpecialEncoding::SUB, INT32_MIN,  1, 0, true)
));

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
