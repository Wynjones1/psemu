#include "cpu.h"

// System Control Co-processor Instructions.
void CPU::MTC0(void)
{
	/* MTC0 rt, rd
		Store contents of CPU register rt into register rd of CP0.This
		follows the convention of store operations.*/
	TODO("Implement");

}

void CPU::MFC0(void)
{
	/* MFC0 rt, rd
		Load CPU register rt with contents of CP0 register rd.*/
	TODO("Implement");

}

void CPU::TLBR(void)
{
	/* TLBR
		Load EntryHi and EntryLo registers with TLB entry pointed at by
		Index register.*/
	TODO("Implement");

}

void CPU::TLBWI(void)
{
	/* TLBWI
		Load TLB entry pointed at by Index register with contents of
		EntryHi and EntryLo registers.*/
	TODO("Implement");

}

void CPU::TLBWR(void)
{
	/* TLBWR
		Load TLB entry pointed at by Random register with contents of
		EntryHi and EntryLo registers.*/
	TODO("Implement");

}

void CPU::TLBP(void)
{
	/* TLBP
		Load Index register with address of TLB entry whose contents
		match EntryHi and EntryLo.If no TLB entry matches, set highorder
		bit of Index register.*/
	TODO("Implement");

}

void CPU::RFE(void)
{
	/* RFE
		Restore previous interrupt mask and mode bits of status register
		into current status bits.Restore old status bits into previous
		status bits.*/
	TODO("Implement");
}

void CPU::MFHI(void)
{
	/* MFHI rd
		Move contents of special register HI to register rd.*/
	TODO("Implement");

}

void CPU::MFLO(void)
{
	/* MFLO rd
		Move contents of special register LO to register rd.*/
	TODO("Implement");

}

void CPU::MTHI(void)
{
	/* MTHI rd
		Move contents of special register rd to special register HI.*/
	TODO("Implement");

}

void CPU::MTLO(void)
{
	/* MTLO rd
		Move contents of register rd to special register LO.*/
	TODO("Implement");
}



// Special Instructions
void CPU::SYSCALL(void)
{
	/* SYSCALL
		Initiates system call trap, immediately transferring control to
		exception handler.*/
	TODO("Implement");

}

void CPU::BREAK(void)
{
	/* BREAK
		Initiates breakpoint trap, immediately transferring control to
		exception handler.*/
	TODO("Implement");
}

// Co-Processor Instructions.
void CPU::LWCz(void)
{
	/* LWCz rt, offset(base)
		Sign - extend 16 - bit offset and add to base to form address.Load
		contents of addressed word into co - processor register rt of coprocessor
		unit z.*/
	TODO("Implement");

}

void CPU::SWCz(void)
{
	/* SWCz rt, offset(base)
		Sign - extend 16 - bit offset and add to base to form address.Store
		contents of co - processor register rt from co - processor unit z at
		addressed memory word.*/
	TODO("Implement");

}

void CPU::MTCz(void)
{
	/* MTCz rt, rd
		Move contents of CPU register rt into co - processor register rd of
		co - processor unit z.*/
	TODO("Implement");

}

void CPU::MFCz(void)
{
	/* MFCz rt, rd
		Move contents of co - processor register rd from co - processor unit
		z to CPU register rt.*/
	TODO("Implement");

}

void CPU::CTCz(void)
{
	/* CTCz rt, rd
		Move contents of CPU register rt into co - processor control register
		rd of co - processor unit z.*/
	TODO("Implement");

}

void CPU::CFCz(void)
{
	/* CFCz rt, rd
		Move contents of control register rd of co - processor unit z into
		CPU register rt.*/
	TODO("Implement");

}

void CPU::COPz(void)
{
	/* COPz cofun
		Co - processor z performs an operation.The state of the R3051 /
		52 is not modified by a co - processor operation.*/
	TODO("Implement");

}

void CPU::BCzT(void)
{
	/* BCzT offset
		Compute a branch target address by adding address of
		instruction in the 16 - bit offset(shifted left two bits and signextended
		to 32 - bits).Branch to the target address(with a delay
		of one instruction) if co - processor zs condition line is true.*/
	TODO("Implement");

}

void CPU::BCzF(void)
{
	/* BCzF offset
		Compute a branch target address by adding address of
		instruction in the 16 - bit offset(shifted left two bits and signextended
		to 32 - bits).Branch to the target address(with a delay
		of one instruction) if co - processor zs condition line is false.*/
	TODO("Implement");
}

