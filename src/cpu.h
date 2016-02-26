#ifndef CPU_H
#define CPU_H
#include <stdint.h>
#include "encoding.h"

class Memory;

class CPU
{
public:
	CPU(Memory &memory);

    void FetchInstruction(void);
    void DecodeInstruction(void);
	void ExecuteALU(void);
    void ExecuteAndAddressCalc(void);
    void AccessMemory(void);
    void Writeback(void);
	void Start(void);

	// Load Instructions.
	void LB(void);
	void LBU(void);
	void LH(void);
	void LHU(void);
	void LW(void);
	void LWL(void);
	void LWR(void);

	// Store Instructions.
	void SB(void);
	void SH(void);
	void SW(void);
	void SWL(void);
	void SWR(void);

	// Computational Instructions (I-Type).
	void ADDI(void);
	void ADDIU(void);
	void SLTI(void);
	void SLTIU(void);
	void ANDI(void);
	void ORI(void);
	void XORI(void);
	void LUI(void);

	// Computational Instructions (R-Type).
	void ADD(void);
	void ADDU(void);
	void SUB(void);
	void SUBU(void);
	void SLT(void);
	void SLTU(void);
	void AND(void);
	void OR(void);
	void XOR(void);
	void NOR(void);

	// Computational Instructions (R-Type Shifts).
	void SLL(void);
	void SRL(void);
	void SRA(void);
	void SLLV(void);
	void SRLV(void);
	void SRAV(void);

	// Multiply / Divide Instructions.
	void MULT(void);
	void MULTU(void);
	void DIV(void);
	void DIVU(void);
	void MFHI(void);
	void MFLO(void);
	void MTHI(void);
	void MTLO(void);

	// Jump Instructions (J-Type).
	void J(void);
	void JAL(void);
	void JR(void);
	void JALR(void);

	// Branch Instructions (J-Type).
	void BEQ(void);
	void BNE(void);
	void BLEZ(void);
	void BGTZ(void);
	void BLTZ(void);
	void BGEZ(void);
	void BLTZAL(void);
	void BGEZAL(void);

	// Special Instructions
	void SYSCALL(void);
	void BREAK(void);

	// Co-Processor Instructions.
	void LWCz(void);
	void SWCz(void);
	void MTCz(void);
	void MFCz(void);
	void CTCz(void);
	void CFCz(void);
	void COPz(void);
	void BCzT(void);
	void BCzF(void);

	// System Control Co-processor Instructions.
	void MTC0(void);
	void MFC0(void);
	void TLBR(void);
	void TLBWI(void);
	void TLBWR(void);
	void TLBP(void);
	void RFE(void);


public:
    uint32_t registers[32];
    uint32_t pc;
    uint32_t hi;
    uint32_t lo;

	/* These structures contains the inputs to the five output stages. */
	struct
	{
		Instruction instruction;
	}IF;
	struct
	{
		Instruction instruction;
	}ID;
	struct
	{
		Instruction     instruction;
		SpecialEncoding alu_control;
		uint32_t        read_data_0;
		uint32_t        read_data_1;
		uint32_t        sign_extended_data;
	}EX;
	struct
	{
		Instruction instruction;
		uint32_t    branch_addr;
		uint32_t    alu_out;
		uint32_t    write_data;
		MemOp       op;
	}MEM;
	struct
	{
		Instruction instruction;
		uint32_t    read_data;
		uint32_t    alu_out;
	}WB;

	uint32_t alu_in_mux;

	Memory &memory;
};

#endif
