#include "cpu.h"
#include "memory.h"
#include "encoding.h"

CPU::CPU(Memory &memory_) : memory(memory_)
{}

void CPU::FetchInstruction(void)
{
	// Move the previously fetched instruction to the decode stage.
	decode_instruction = fetch_instruction;
	// Fetch the next instruction.
	fetch_instruction  = memory.Load(pc);
}

void CPU::DecodeInstruction(void)
{
	OpcodeEncoding opcode = decode_instruction.op();
}

void CPU::ExecuteALU(void)
{
}

void CPU::AccessMemory(void)
{
}

void CPU::Writeback(void)
{
}

void CPU::Start(void)
{
	while (1)
	{
		FetchInstruction();
		DecodeInstruction();
		ExecuteALU();
		AccessMemory();
		Writeback();
	}
}

// Load Instructions.
void CPU::LB(void)
{
}

void CPU::LBU(void)
{
}

void CPU::LH(void)
{
}

void CPU::LHU(void)
{
}

void CPU::LW(void)
{
}

void CPU::LWL(void)
{
}

void CPU::LWR(void)
{
}

// Store Instructions.
void CPU::SB(void)
{
}

void CPU::SH(void)
{
}

void CPU::SW(void)
{
}

void CPU::SWL(void)
{
}

void CPU::SWR(void)
{
}

// Computational Instructions (I-Type).
void CPU::ADDI(void)
{
}

void CPU::ADDIU(void)
{
}

void CPU::SLTI(void)
{
}

void CPU::SLTIU(void)
{
}

void CPU::ANDI(void)
{
}

void CPU::ORI(void)
{
}

void CPU::XORI(void)
{
}

void CPU::LUI(void)
{
}

// Computational Instructions (R-Type).
void CPU::ADD(void)
{
}

void CPU::ADDU(void)
{
}

void CPU::SUB(void)
{
}

void CPU::SUBU(void)
{
}

void CPU::SLT(void)
{
}

void CPU::SLTU(void)
{
}

void CPU::AND(void)
{
}

void CPU::OR(void)
{
}

void CPU::XOR(void)
{
}

void CPU::NOR(void)
{
}

// Computational Instructions (R-Type Shifts).
void CPU::SLL(void)
{
}

void CPU::SRL(void)
{
}

void CPU::SRA(void)
{
}

void CPU::SLLV(void)
{
}

void CPU::SRLV(void)
{
}

void CPU::SRAV(void)
{
}

// Multiply / Divide Instructions.
void CPU::MULT(void)
{
}

void CPU::MULTU(void)
{
}

void CPU::DIV(void)
{
}

void CPU::DIVU(void)
{
}

void CPU::MFHI(void)
{
}

void CPU::MFLO(void)
{
}

void CPU::MTHI(void)
{
}

void CPU::MTLO(void)
{
}

// Jump Instructions (J-Type).
void CPU::J(void)
{
}

void CPU::JAL(void)
{
}

void CPU::JR(void)
{
}

void CPU::JALR(void)
{
}

// Branch Instructions (J-Type).
void CPU::BEQ(void)
{
}

void CPU::BNE(void)
{
}

void CPU::BLEZ(void)
{
}

void CPU::BGTZ(void)
{
}

void CPU::BLTZ(void)
{
}

void CPU::BGEZ(void)
{
}

void CPU::BLTZAL(void)
{
}

void CPU::BGEZAL(void)
{
}

// Special Instructions
void CPU::SYSCALL(void)
{
}

void CPU::BREAK(void)
{
}

// Co-Processor Instructions.
void CPU::LWCz(void)
{
}

void CPU::SWCz(void)
{
}

void CPU::MTCz(void)
{
}

void CPU::MFCz(void)
{
}

void CPU::CTCz(void)
{
}

void CPU::CFCz(void)
{
}

void CPU::COPz(void)
{
}

void CPU::BCzT(void)
{
}

void CPU::BCzF(void)
{
}

// System Control Co-processor Instructions.
void CPU::MTC0(void)
{
}

void CPU::MFC0(void)
{
}

void CPU::TLBR(void)
{
}

void CPU::TLBWI(void)
{
}

void CPU::TLBWR(void)
{
}

void CPU::TLBP(void)
{
}

void CPU::RFE(void)
{
}
