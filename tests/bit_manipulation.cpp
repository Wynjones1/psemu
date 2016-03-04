#include "support.h"

#undef PARAM
#define PARAM std::tuple<uint64_t, uint32_t, uint32_t, uint32_t>

struct ExtractTest : public ::testing::TestWithParam<PARAM> {};

TEST_P(ExtractTest, Test)
{
    auto param  = GetParam();
    auto result = extract(std::get<0>(param), std::get<1>(param), std::get<2>(param));
    auto expected = std::get<3>(param);
    EXPECT_EQ(result, expected);
}

INSTANTIATE_TEST_CASE_P(
Simple, ExtractTest, ::testing::Values(
    PARAM(0x0,        0,   0, 0x0),
    PARAM(0x1,        0,   0, 0x1),
    PARAM(0xffffffff, 31, 31, 0x1),
    PARAM(0x0,        31, 31, 0x0)
));

INSTANTIATE_TEST_CASE_P(
AllNibbles, ExtractTest, ::testing::Values(
    PARAM(0xf0,               7,   4, 0xf),
    PARAM(0xf00,              11,  8, 0xf),
    PARAM(0xf000,             15, 12, 0xf),
    PARAM(0xf0000,            19, 16, 0xf),
    PARAM(0xf00000,           23, 20, 0xf),
    PARAM(0xf000000,          27, 24, 0xf),
    PARAM(0xf0000000,         31, 28, 0xf),
    PARAM(0xf00000000,        35, 32, 0xf),
    PARAM(0xf000000000,       39, 36, 0xf),
    PARAM(0xf0000000000,      43, 40, 0xf),
    PARAM(0xf00000000000,     47, 44, 0xf),
    PARAM(0xf000000000000,    51, 48, 0xf),
    PARAM(0xf0000000000000,   55, 52, 0xf),
    PARAM(0xf00000000000000,  59, 56, 0xf),
    PARAM(0xf000000000000000, 63, 60, 0xf)
));

#undef PARAM
#define PARAM std::tuple<uint32_t, uint32_t, uint64_t>

struct MaskTest : public ::testing::TestWithParam<PARAM> {};

TEST_P(MaskTest, Test)
{
    auto param = GetParam();
    auto result = mask(std::get<0>(param), std::get<1>(param));
    ASSERT_EQ(std::get<2>(param), result);
}

INSTANTIATE_TEST_CASE_P(
AllBitsLessThan32, MaskTest, ::testing::Values(
    PARAM( 0,  0, uint64_t(1) <<  0),
    PARAM( 1,  1, uint64_t(1) <<  1),
    PARAM( 2,  2, uint64_t(1) <<  2),
    PARAM( 3,  3, uint64_t(1) <<  3),
    PARAM( 4,  4, uint64_t(1) <<  4),
    PARAM( 5,  5, uint64_t(1) <<  5),
    PARAM( 6,  6, uint64_t(1) <<  6),
    PARAM( 7,  7, uint64_t(1) <<  7),
    PARAM( 8,  8, uint64_t(1) <<  8),
    PARAM( 9,  9, uint64_t(1) <<  9),
    PARAM(10, 10, uint64_t(1) << 10),
    PARAM(11, 11, uint64_t(1) << 11),
    PARAM(12, 12, uint64_t(1) << 12),
    PARAM(13, 13, uint64_t(1) << 13),
    PARAM(14, 14, uint64_t(1) << 14),
    PARAM(15, 15, uint64_t(1) << 15),
    PARAM(16, 16, uint64_t(1) << 16),
    PARAM(17, 17, uint64_t(1) << 17),
    PARAM(18, 18, uint64_t(1) << 18),
    PARAM(19, 19, uint64_t(1) << 19),
    PARAM(20, 20, uint64_t(1) << 20),
    PARAM(21, 21, uint64_t(1) << 21),
    PARAM(22, 22, uint64_t(1) << 22),
    PARAM(23, 23, uint64_t(1) << 23),
    PARAM(24, 24, uint64_t(1) << 24),
    PARAM(25, 25, uint64_t(1) << 25),
    PARAM(26, 26, uint64_t(1) << 26),
    PARAM(27, 27, uint64_t(1) << 27),
    PARAM(28, 28, uint64_t(1) << 28),
    PARAM(29, 29, uint64_t(1) << 29),
    PARAM(30, 30, uint64_t(1) << 30),
    PARAM(31, 31, uint64_t(1) << 31)
));

INSTANTIATE_TEST_CASE_P(
AllBitsMoreThan32, MaskTest, ::testing::Values(
    PARAM(32, 32, uint64_t(1) << 32),
    PARAM(33, 33, uint64_t(1) << 33),
    PARAM(34, 34, uint64_t(1) << 34),
    PARAM(35, 35, uint64_t(1) << 35),
    PARAM(36, 36, uint64_t(1) << 36),
    PARAM(37, 37, uint64_t(1) << 37),
    PARAM(38, 38, uint64_t(1) << 38),
    PARAM(39, 39, uint64_t(1) << 39),
    PARAM(40, 40, uint64_t(1) << 40),
    PARAM(41, 41, uint64_t(1) << 41),
    PARAM(42, 42, uint64_t(1) << 42),
    PARAM(43, 43, uint64_t(1) << 43),
    PARAM(44, 44, uint64_t(1) << 44),
    PARAM(45, 45, uint64_t(1) << 45),
    PARAM(46, 46, uint64_t(1) << 46),
    PARAM(47, 47, uint64_t(1) << 47),
    PARAM(48, 48, uint64_t(1) << 48),
    PARAM(49, 49, uint64_t(1) << 49),
    PARAM(50, 50, uint64_t(1) << 50),
    PARAM(51, 51, uint64_t(1) << 51),
    PARAM(52, 52, uint64_t(1) << 52),
    PARAM(53, 53, uint64_t(1) << 53),
    PARAM(54, 54, uint64_t(1) << 54),
    PARAM(55, 55, uint64_t(1) << 55),
    PARAM(56, 56, uint64_t(1) << 56),
    PARAM(57, 57, uint64_t(1) << 57),
    PARAM(58, 58, uint64_t(1) << 58),
    PARAM(59, 59, uint64_t(1) << 59),
    PARAM(60, 60, uint64_t(1) << 60),
    PARAM(61, 61, uint64_t(1) << 61),
    PARAM(62, 62, uint64_t(1) << 62),
    PARAM(63, 63, uint64_t(1) << 63)
));
