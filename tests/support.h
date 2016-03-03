#ifndef SUPPORT_H
#define SUPPORT_H
#include "gtest/gtest.h"
#include "cpu.h"
#include "memory.h"
#include <random>
#include <tuple>

auto mt = std::mt19937(0);
/*
    returns T in range [min, max]
*/
template<typename T>
T rand_int(T min, T max)
{
    return std::uniform_int_distribution<T>(min, max)(mt);
}

template<typename ParamType>
struct InstructionTestFixture
    : public ::testing::Test
    , public ::testing::WithParamInterface<ParamType>
{
    template<typename... Args>
    InstructionTestFixture(Args&&... args)
    : cpu(memory)
    , instruction(std::forward<Args>(args)...)
    {}

    void SetUp()
    {}

    void TearDown()
    {}

    Memory      memory;
    CPU         cpu;
    Instruction instruction; 
};

#endif
