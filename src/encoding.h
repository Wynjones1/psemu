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
	ADDIU,
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

inline bool is_special(OpcodeEncoding encoding)
{
	return (encoding == OpcodeEncoding::SPECIAL);
};

inline bool is_branch(OpcodeEncoding encoding)
{
	return (OpcodeEncoding::J <= encoding && encoding <= OpcodeEncoding::BGTZ);
}

inline bool is_memory_access(OpcodeEncoding encoding)
{
	return (OpcodeEncoding::LB <= encoding && encoding <= OpcodeEncoding::SWR);
}

inline bool is_load(OpcodeEncoding encoding)
{
	return (OpcodeEncoding::LB <= encoding && encoding <= OpcodeEncoding::LWR);
}

inline bool is_store(OpcodeEncoding encoding)
{
	return (OpcodeEncoding::SB <= encoding && encoding <= OpcodeEncoding::SWR);
}

inline bool is_immediate(OpcodeEncoding encoding)
{
	return (OpcodeEncoding::ADDI <= encoding && encoding <= OpcodeEncoding::LUI);
}

inline bool is_cop(OpcodeEncoding encoding)
{
	return (OpcodeEncoding::COP0 <= encoding && encoding <= OpcodeEncoding::COP3);
}

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

enum class Register : uint8_t
{
	R0 , ZERO = R0,
	R1 , AT = R1,
	R2 , V0 = R2,
	R3 , V1 = R3,
	R4 , A0 = R4,
	R5 , A1 = R5,
	R6 , A2 = R6,
	R7 , A3 = R7,
	R8 , T0 = R8,
	R9 , T1 = R9,
	R10, T2 = R10,
	R11, T3 = R11,
	R12, T4 = R12,
	R13, T5 = R13,
	R14, T6 = R14,
	R15, T7 = R15,
	R16, S0 = R16,
	R17, S1 = R17,
	R18, S2 = R18,
	R19, S3 = R19,
	R20, S4 = R20,
	R21, S5 = R21,
	R22, S6 = R22,
	R23, S7 = R23,
	R24, T8 = R24,
	R25, T9 = R25,
	R26, K0 = R26,
	R27, K1 = R27,
	R28, GP = R28,
	R29, SP = R29,
	R30, S8 = R30, FP = R30,
	R31, RA = R31,
	NUM_REGISTERS,
};

class Instruction
{
public:
    Instruction(uint32_t value_ = 0)
    : value(value_)
    {}

	Instruction(OpcodeEncoding  opcode_,
				Register        rs_,
				Register        rt_,
				Register        rd_,
				uint8_t         sa_,
				SpecialEncoding funct_)
	: value(0)
	{
		encode(value, (uint32_t) opcode_, 31, 26);
		encode(value, (uint32_t) rs_,     25, 21);
		encode(value, (uint32_t) rt_,     20, 16);
		encode(value, (uint32_t) rd_,     15, 11);
		encode(value, (uint32_t) sa_,     10,  6);
		encode(value, (uint32_t) funct_,   5,  0);
	}

	Instruction(OpcodeEncoding opcode_,
			    uint32_t       target_)
		: value(0)
	{
		encode(value, (uint32_t)opcode_, 31, 26);
		encode(value, (uint32_t)target_, 25,  0);
	}

	Instruction(OpcodeEncoding  opcode_,
				Register        rs_,
				Register        rt_,
				uint16_t        imm_)
		: value(0)
	{
		encode(value, (uint32_t)opcode_, 31, 26);
		encode(value, (uint32_t)rs_,     25, 21);
		encode(value, (uint32_t)rt_,     20, 16);
		encode(value, (uint32_t)imm_,    15,  0);
	}

    explicit operator uint32_t() { return value; }

	// Common
    inline OpcodeEncoding  op() { return extract<OpcodeEncoding>(value, 31, 26);}
    inline Register        rs() { return extract<Register>(value, 25, 21);}
    inline Register        rt() { return extract<Register>(value, 20, 16);}

	// Immediate Instruction
    inline uint16_t imm(){ return extract(value, 15, 0);}

	// Jump Instruction
	inline uint32_t target() { return extract(value, 25, 0); }

	// Register Instruction
	inline Register        rd()    { return extract<Register>(value, 15, 11); }
	inline uint8_t         shamt() { return extract(value, 10, 6); }
	inline SpecialEncoding funct() { return extract<SpecialEncoding>(value, 5, 0); }


	inline bool is_special()
	{
		return (op() == OpcodeEncoding::SPECIAL);
	};

	inline bool is_branch()
	{
		return (OpcodeEncoding::J <= op() && op() <= OpcodeEncoding::BGTZ);
	}

	inline bool is_memory_access()
	{
		return (OpcodeEncoding::LB <= op() && op() <= OpcodeEncoding::SWR);
	}

	inline bool is_load()
	{
		return (OpcodeEncoding::LB <= op() && op() <= OpcodeEncoding::LWR);
	}

	inline bool is_store()
	{
		return (OpcodeEncoding::SB <= op() && op() <= OpcodeEncoding::SWR);
	}

	inline bool is_immediate()
	{
		return (OpcodeEncoding::ADDI <= op() && op() <= OpcodeEncoding::LUI);
	}

	inline bool is_cop()
	{
		return (OpcodeEncoding::COP0 <= op() && op() <= OpcodeEncoding::COP3);
	}
private:
	uint32_t value;
};

#endif
