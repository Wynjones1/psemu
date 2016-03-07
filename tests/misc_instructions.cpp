#include "support.h"
#include "generic_special_instruction.h"

#undef PARAM
#define PARAM std::tuple<SpecialEncoding, uint32_t, uint32_t, uint32_t, bool>

INSTANTIATE_TEST_CASE_P(
SLT, SpecialInstructionTest, ::testing::Values(
    PARAM(SpecialEncoding::SLT,  0, 0, 0, false),
    PARAM(SpecialEncoding::SLT,  0,-1, 0, false),
    PARAM(SpecialEncoding::SLT,  1, 0, 0, false),
    PARAM(SpecialEncoding::SLT,  1, 1, 0, false),
    PARAM(SpecialEncoding::SLT,  1,-1, 0, false),
    PARAM(SpecialEncoding::SLT,  0, 1, 1, false),
    PARAM(SpecialEncoding::SLT, -1, 0, 1, false),
    PARAM(SpecialEncoding::SLT, -1, 1, 1, false)
));

INSTANTIATE_TEST_CASE_P(
SLTU, SpecialInstructionTest, ::testing::Values(
    PARAM(SpecialEncoding::SLTU,  0, 0, 0, false),
    PARAM(SpecialEncoding::SLTU,  1, 1, 0, false),
    PARAM(SpecialEncoding::SLTU,  1, 0, 0, false),
    PARAM(SpecialEncoding::SLTU, -1, 0, 0, false),
    PARAM(SpecialEncoding::SLTU, -1, 1, 0, false),
    PARAM(SpecialEncoding::SLTU,  0, 1, 1, false),
    PARAM(SpecialEncoding::SLTU,  0,-1, 1, false),
    PARAM(SpecialEncoding::SLTU,  1,-1, 1, false)
));

#if 1
TEST(InstructionSYSCALL, Test0)
{
	FAIL();
}

TEST(InstructionBREAK, Test0)
{
	FAIL();
}

TEST(InstructionMFHI, Test0)
{
	FAIL();
}

TEST(InstructionMTHI, Test0)
{
	FAIL();
}

TEST(InstructionMFLO, Test0)
{
	FAIL();
}

TEST(InstructionMTLO, Test0)
{
	FAIL();
}

TEST(InstructionMFC0, Test0)
{
	FAIL();
}

TEST(InstructionMTC0, Test0)
{
	FAIL();
}

TEST(InstructionBC0F, Test0)
{
	FAIL();
}

TEST(InstructionBC0T, Test0)
{
	FAIL();
}

TEST(InstructionTLBR, Test0)
{
	FAIL();
}

TEST(InstructionTLBWI, Test0)
{
	FAIL();
}

TEST(InstructionTLBWR, Test0)
{
	FAIL();
}

TEST(InstructionTLBP, Test0)
{
	FAIL();
}

TEST(InstructionRFE, Test0)
{
	FAIL();
}

TEST(InstructionSWC1, Test0)
{
	FAIL();
}

TEST(InstructionLWC1, Test0)
{
	FAIL();
}
#endif
