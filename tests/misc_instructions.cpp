#include "gtest/gtest.h"
#include "cpu.h"
#include "memory.h"

#if 0
INSTANTIATE_TEST_CASE_P(
SLT, ShiftImmediateInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SLT, 0, 0, 0)
));

INSTANTIATE_TEST_CASE_P(
SLTU, ShiftImmediateInstruction, ::testing::Values(
    PARAM(SpecialEncoding::SLTU, 0, 0, 0)
));
#endif

#if 0
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
