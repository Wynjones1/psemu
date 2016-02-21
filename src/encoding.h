#ifndef ENCODING_H
#define ENCODING_H

constexpr uint32_t mask(uint32_t msb, uint32_t lsb)
{
    return (((1 << msb) - 1) >> lsb) << lsb;
}

constexpr uint32_t extract(uint32_t value, uint32_t msb, uint32_t lsb)
{
    return (value & mask(msb, lsb)) >> lsb;
}

enum class OpcodeEncoding : uint8_t
{
	SPECIAL = 0,
	BCOND,
	J,
	JAL,
	BEQ,
	BNE,
	BLEZ,
	BGTZ,
	ADDI = 8,
	ADDUI,
	SLTI,
	SLTIU,
	ANDI,
	ORI,
	XORI,
	LUI,
	COP0 = 16,
	COP1,
	COP2,
	COP3,
	LB = 32,
	LH,
	LWL,
	LW,
	LBU,
	LHU,
	LWR,
	SB = 40,
	SH,
	SWL,
	SW,
	SWR = 46,
	LWC0 = 48,
	LWC1,
	LWC2,
	LWC3,
	SWC0 = 56,
	SWC1,
	SWC2,
	SWC3,
};

enum class SpecialEncoding : uint8_t
{
	SLL = 0,
	SRL = 2,
	SRA,
	SLLV,
	SRLV = 6,
	SRAV,
	JR = 8,
	JALR,
	SYSCALL = 12,
	BREAK,
	MFHI = 16,
	MTHI,
	MFLO,
	MTLO,
	MULT = 24,
	MULTU,
	DIV,
	DIVU,
	ADD = 32,
	ADDU,
	SUB,
	SUBU,
	AND,
	OR,
	XOR,
	NOR,
	SLT = 42,
	SLTU,
};

enum class BCondEncoding : uint8_t
{
	BLTZ=0,
	BGEZ,
	BLTZAL=16,
	BGEZAL,
};

enum class CopZEncoding : uint8_t
{
	MF=0,
	CF=2,
	MT=4,
	CT=6,
	BC=8,
};

enum class Cop0Encoding : uint8_t
{
	TLBR=1,
	TLBWI=2,
	TLBWR=6,
	TLBP=8,
	RFE=16,
};

class ImmediateInstruction
{
public:
    ImmediateInstruction(uint32_t value_)
    : value(value_)
    {}

    explicit operator uint32_t() { return value; }

    inline uint8_t  op() { return extract(value, 31, 26);}
    inline uint8_t  rs() { return extract(value, 25, 21);}
    inline uint8_t  rt() { return extract(value, 20, 16);}
    inline uint16_t imm(){ return extract(value, 15,  0);}
    uint32_t value;
};

class JumpInstruction
{
public:
    JumpInstruction(uint32_t value_)
    : value(value_)
    {}

    explicit operator uint32_t() { return value; }

    inline uint8_t  op()    { return extract(value, 31, 26);}
    inline uint32_t target(){ return extract(value, 25,  0);}
    uint32_t value;
};

class RegisterInstruction
{
public:
    RegisterInstruction(uint32_t value_)
    : value(value_)
    {}

    explicit operator uint32_t() { return value; }

    inline uint8_t op()    { return extract(value, 31, 26);}
    inline uint8_t rs()    { return extract(value, 25, 21);}
    inline uint8_t rt()    { return extract(value, 20, 16);}
    inline uint8_t rd()    { return extract(value, 15, 11);}
    inline uint8_t shamt() { return extract(value, 10, 6);}
    inline uint8_t funct() { return extract(value,  5, 0);}
    uint32_t value;
};

#endif
