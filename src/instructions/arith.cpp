#include "cpu.h"

// Computational Instructions (R-Type).
void CPU::ADD(void)
{
    /* ADD rd, rs, rt
        Add contents of registers rs and rt and place 32 - bit result in
        register rd.Trap on twos complement overflow.*/
    auto rs = to_signed(registers[EX.instruction.rs()]);
    auto rt = to_signed(registers[EX.instruction.rt()]);
#if HAVE_BUILTIN_OVERFLOW
    int32_t sum;
    if(__builtin_add_overflow(rs, rt, &sum))
    {
        TriggerOverflowException();
    }
    else
    {
        registers[EX.instruction.rd()] = sum;
    }
#else
    auto sum = rs + rt;
    if (sum < rs)
    {
        TriggerOverflowException();
    }
    else
    {
        registers[EX.instruction.rd()] = sum;
    }
#endif
}

void CPU::ADDU(void)
{
    /* ADDU rd, rs, rt
        Add contents of registers rs and rt and place 32 - bit result in
        register rd.Do not trap on overflow.*/
    auto &rs = registers[EX.instruction.rs()];
    auto &rt = registers[EX.instruction.rt()];
    registers[EX.instruction.rd()] = rs + rt;
}

void CPU::SUB(void)
{
    /* SUB rd, rs, rt
        Subtract contents of registers rt and rs and place 32 - bit result
        in register rd.Trap on twos complement overflow.*/
    auto rs      = to_signed(registers[EX.instruction.rs()]);
    auto rt      = to_signed(registers[EX.instruction.rt()]);
#if HAVE_BUILTIN_OVERFLOW 
    int32_t res;
    if(__builtin_sub_overflow(rs, rt, &res))
    {
        TriggerOverflowException();
    }
    else
    {
        registers[EX.instruction.rd()] = res;
    }
#else
    auto sum     = to_unsigned(rs - rt);
    auto rs_neg  = sign_bit(rs);
    auto rt_neg  = sign_bit(rt);;
    auto sum_neg = sign_bit(sum);
    /* Overflow conditions.
        +ve - -ve = -ve
        -ve - +ve = +ve
    */
    if(rs_neg != rt_neg && rt_neg == sum_neg)
    {
        TriggerOverflowException();
    }
    else
    {
        registers[EX.instruction.rd()] = sum;
    }
#endif
}

void CPU::SUBU(void)
{
    /* SUBU rd, rs, rt
        Subtract contents of registers rt and rs and place 32 - bit result
        in register rd.Do not trap on overflow.*/
    auto rs      = registers[EX.instruction.rs()];
    auto rt      = registers[EX.instruction.rt()];
    registers[EX.instruction.rd()] = rs - rt;
}

// Multiply / Divide Instructions.
void CPU::MULT(void)
{
	/* MULT rs, rt
		Multiply contents of registers rs and rt as twos complement
		values.Place 64 - bit result in special registers HI / LO*/
    int64_t rs = to_signed(registers[EX.instruction.rs()]);
    int64_t rt = to_signed(registers[EX.instruction.rt()]);
    auto result = rs * rt;
    lo = result & 0xffffffff;
    hi = result >> 32;
}

void CPU::MULTU(void)
{
	/* MULTU rs, rt
		Multiply contents of registers rs and rt as unsigned values.Place
		64 - bit result in special registers HI / LO*/
    auto rs = uint64_t(registers[EX.instruction.rs()]);
    auto rt = uint64_t(registers[EX.instruction.rt()]);
    auto result = rs * rt;
    lo = result & 0xffffffff;
    hi = result >> 32;
}

void CPU::DIV(void)
{
	/* DIV rs, rt
		Divide contents of register rs by rt treating operands as twos
		complements values.Place 32 - bit quotient in special register
		LO, and 32 - bit remainder in HI.*/
    auto rs = to_signed(registers[EX.instruction.rs()]);
    auto rt = to_signed(registers[EX.instruction.rt()]);
    if(rt == 0)
    {
        debug_state.divide_by_zero = true;
        hi = lo = 0;
    }
    else
    {
        lo = rs / rt;
        hi = rs % rt;
    }
}

void CPU::DIVU(void)
{
	/* DIVU rs, rt
		Divide contents of register rs by rt treating operands as unsigned
		values.Place 32 - bit quotient in special register LO, and 32 - bit
		remainder in HI.*/
    auto rs = registers[EX.instruction.rs()];
    auto rt = registers[EX.instruction.rt()];
    if(rt == 0)
    {
        debug_state.divide_by_zero = true;
        hi = lo = 0;
    }
    else
    {
        lo = rs / rt;
        hi = rs % rt;
    }
}
