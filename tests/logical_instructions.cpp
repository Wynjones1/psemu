#include "support.h"
#include "generic_special_instruction.h"

INSTANTIATE_TEST_CASE_P(
	SLTU, SpecialInstructionTest, ::testing::Values(
		PARAM(SpecialEncoding::SLTU, 0, 0, 0, false),
		PARAM(SpecialEncoding::SLTU, 0, 1, 1, false),
		PARAM(SpecialEncoding::SLTU, 1, 0, 0, false),
		PARAM(SpecialEncoding::SLTU, 0xffffffff, 0, 0, false),
		PARAM(SpecialEncoding::SLTU, 0, 0xffffffff, 1, false)
));

INSTANTIATE_TEST_CASE_P(
	SLT, SpecialInstructionTest, ::testing::Values(
		PARAM(SpecialEncoding::SLT, 0, 0, 0, false),
		PARAM(SpecialEncoding::SLT, 0, 1, 1, false),
		PARAM(SpecialEncoding::SLT, 1, 0, 0, false),
		PARAM(SpecialEncoding::SLT, -1, 1, 1, false),
		PARAM(SpecialEncoding::SLT, -2, -1, 1, false),
		PARAM(SpecialEncoding::SLT, -2, 0, 1, false),
		PARAM(SpecialEncoding::SLT, INT32_MIN, INT32_MAX, 1, false),
		PARAM(SpecialEncoding::SLT, INT32_MAX, INT32_MIN, 0, false)
));

INSTANTIATE_TEST_CASE_P(
	AND, SpecialInstructionTest, ::testing::Values(
		PARAM(SpecialEncoding::AND, 0, 0, 0, false),
		PARAM(SpecialEncoding::AND, 0xff, 0xff, 0xff, false),
		PARAM(SpecialEncoding::AND, 0xf0, 0xf0, 0xf0, false),
		PARAM(SpecialEncoding::AND, 0x0f, 0xf0, 0x00, false),
		PARAM(SpecialEncoding::AND, 0xffffffff, 0xf0f0f0f0, 0xf0f0f0f0, false),
		PARAM(SpecialEncoding::AND, 0xf0f0f0f0, 0xffffffff, 0xf0f0f0f0, false)
));

INSTANTIATE_TEST_CASE_P(
	OR, SpecialInstructionTest, ::testing::Values(
		PARAM(SpecialEncoding::OR, 0, 0, 0, false),
		PARAM(SpecialEncoding::OR, 0xf, 0xf, 0xf, false),
		PARAM(SpecialEncoding::OR, 0xf0, 0x0f, 0xff, false),
		PARAM(SpecialEncoding::OR, 0xffffffff, 0xffffffff, 0xffffffff, false),
		PARAM(SpecialEncoding::OR, 0xffff0000, 0x0000ffff, 0xffffffff, false),
		PARAM(SpecialEncoding::OR, 1 << 31, 1 << 17, (1 << 31) | (1 << 17), false)
));

INSTANTIATE_TEST_CASE_P(
	XOR, SpecialInstructionTest, ::testing::Values(
		PARAM(SpecialEncoding::XOR, 0, 0, 0, false),
		PARAM(SpecialEncoding::XOR, 0xf0, 0x0f, 0xff, false),
		PARAM(SpecialEncoding::XOR, 0xf0, 0xff, 0x0f, false),
		PARAM(SpecialEncoding::XOR, 0xffff0000, 0xfffff0f0, 0xf0f0, false),
		PARAM(SpecialEncoding::XOR, 1 << 31, 1 << 17, (1 << 31) | (1 << 17), false)
));

INSTANTIATE_TEST_CASE_P(
	NOR, SpecialInstructionTest, ::testing::Values(
		PARAM(SpecialEncoding::NOR, 0, 0,       0xffffffff, false),
		PARAM(SpecialEncoding::NOR, 0xf, 0xf,   0xfffffff0, false),
		PARAM(SpecialEncoding::NOR, 0xf0, 0x0f, 0xffffff00, false),
		PARAM(SpecialEncoding::NOR, 0xffffffff, 0xffffffff, 0x0, false),
		PARAM(SpecialEncoding::NOR, 0xffff0000, 0x0000ffff, 0x0, false),
		PARAM(SpecialEncoding::NOR, 1 << 31, 1 << 17, ~((1 << 31) | (1 << 17)), false)
));