#ifndef ENCODING_H
#define ENCODING_H
#include <stdint.h>
#include "bit_manipulation.h"

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

class Instruction
{
public:
    Instruction(uint32_t value_ = 0)
    : value(value_)
    {}

    explicit operator uint32_t() { return value; }

	// Common
    inline OpcodeEncoding  op() { return extract<OpcodeEncoding>(value, 31, 26);}
    inline uint8_t  rs() { return extract(value, 25, 21);}
    inline uint8_t  rt() { return extract(value, 20, 16);}

	// Immediate Instruction
    inline uint16_t imm(){ return extract(value, 15,  0);}

	// Jump Instruction
	inline uint32_t target() { return extract(value, 25, 0); }

	// Register Instruction
	inline uint8_t rd()    { return extract(value, 15, 11); }
	inline uint8_t shamt() { return extract(value, 10, 6); }
	inline uint8_t funct() { return extract(value, 5, 0); }
private:
	uint32_t value;
};

#endif
