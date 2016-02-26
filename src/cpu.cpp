#include "cpu.h"
#include "memory.h"
#include "encoding.h"

CPU::CPU(Memory &memory_) : memory(memory_)
{}

void CPU::FetchInstruction(void)
{
	// Move the previously fetched instruction to the decode stage.
	ID.instruction = IF.instruction;
	IF.instruction = memory.Load(pc);
}

void CPU::DecodeInstruction(void)
{
	EX.instruction        = ID.instruction;
	EX.read_data_0        = registers[ID.instruction.rs()];
	EX.read_data_1        = registers[ID.instruction.rt()];
	EX.sign_extended_data = sign_extend(ID.instruction.imm());
	EX.alu_control        = ID.instruction.funct();
}

void CPU::ExecuteALU(void)
{
	switch (EX.alu_control)
	{
	case SpecialEncoding::SLL:
		break;
	case SpecialEncoding::SRL:
		break;
	case SpecialEncoding::SRA:
		break;
	case SpecialEncoding::SLLV:
		break;
	case SpecialEncoding::SRLV:
		break;
	case SpecialEncoding::SRAV:
		break;
	case SpecialEncoding::JR:
		break;
	case SpecialEncoding::JALR:
		break;
	case SpecialEncoding::SYSCALL:
		break;
	case SpecialEncoding::BREAK:
		break;
	case SpecialEncoding::MFHI:
		break;
	case SpecialEncoding::MTHI:
		break;
	case SpecialEncoding::MFLO:
		break;
	case SpecialEncoding::MTLO:
		break;
	case SpecialEncoding::MULT:
		break;
	case SpecialEncoding::MULTU:
		break;
	case SpecialEncoding::DIV:
		break;
	case SpecialEncoding::DIVU:
		break;
	case SpecialEncoding::ADD:
		break;
	case SpecialEncoding::ADDU:
		break;
	case SpecialEncoding::SUB:
		break;
	case SpecialEncoding::SUBU:
		break;
	case SpecialEncoding::AND:
		break;
	case SpecialEncoding::OR:
		break;
	case SpecialEncoding::XOR:
		break;
	case SpecialEncoding::NOR:
		break;
	case SpecialEncoding::SLT:
		break;
	case SpecialEncoding::SLTU:
		break;
	}
}

void CPU::ExecuteAndAddressCalc(void)
{
	MEM.instruction = EX.instruction;
	MEM.branch_addr = ((EX.sign_extended_data & mask<31,31>()) | (EX.sign_extended_data << 2)) + pc;
	MEM.write_data  = EX.read_data_1;
	MEM.op          = MemOp::NOP;
	if (EX.instruction.op() == OpcodeEncoding::SPECIAL)
	{
		alu_in_mux = EX.read_data_1;
	}
	else
	{
		alu_in_mux = EX.sign_extended_data;
	}
	ExecuteALU();
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
		// Perform the writeback first, so the register
		// file is in the correct state when we decode.
		Writeback();

		FetchInstruction();
		DecodeInstruction();
		ExecuteAndAddressCalc();
		AccessMemory();
	}
}

// Load Instructions.
void CPU::LB(void)
{
	/* LB rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Sign - extend contents of addressed byte and load into rt. */
}

void CPU::LBU(void)
{
	/* LBU rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Zero - extend contents of addressed byte and load into rt.*/
}

void CPU::LH(void)
{
	/* LH rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Sign - extend contents of addressed byte and load into rt.*/
}

void CPU::LHU(void)
{
	/* LHU rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Zero - extend contents of addressed byte and load into rt.*/
}

void CPU::LW(void)
{
	/* LW rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Load contents of addressed word into register rt.*/
}

void CPU::LWL(void)
{
	/* LWL rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Shift addressed word left so that addressed byte is leftmost byte
		of a word.
		Merge bytes from memory with contents of register rt and load
		result into register rt.*/
}

void CPU::LWR(void)
{
	/* LWR rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Shift addressed word right so that addressed byte is rightmost
		byte of a word.
		Merge bytes from memory with contents of register rt and load
		result into register rt.*/
}

// Store Instructions.
void CPU::SB(void)
{
	/* SB rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Store least significant byte of register rt at addressed location.*/
}

void CPU::SH(void)
{
	/* SH rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Store least significant halfword of register rt at addressed location.*/
}

void CPU::SW(void)
{
	/* SW rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Store least significant word of register rt at addressed location.*/
}

void CPU::SWL(void)
{
	/* SWL rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Shift contents of register rt right so that leftmost byte of the word
		is in position of addressed byte.Store bytes containing original
		data into corresponding bytes at addressed byte.*/
}

void CPU::SWR(void)
{
	/* SWR rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Shift contents of register rt left so that rightmost byte of the word
		is in position of addressed byte.Store bytes containing original
		data into corresponding bytes at addressed byte.*/
}

// Computational Instructions (I-Type).
void CPU::ADDI(void)
{
	/* ADDI rt, rs, immediate
		Add 16 - bit sign - extended immediate to register rs and place 32 -
		bit result in register rt.Trap on two’s complement overflow.*/
}

void CPU::ADDIU(void)
{
	/* ADDIU rt, rs, immediate
		Add 16 - bit sign - extended immediate to register rs and place 32 -
		bit result in register rt.Do not trap on overflow.*/
}

void CPU::SLTI(void)
{
	/*	SLTI rt, rs, immediate
		Compare 16 - bit sign - extended immediate with register rs as
		signed 32 - bit integers.Result = 1 if rs is less than immediate;
		otherwise result = 0.
		Place result in register rt.*/
}

void CPU::SLTIU(void)
{
	/* SLTIU rt, rs, immediate
		Compare 16 - bit sign - extended immediate with register rs as
		unsigned 32 - bit integers.Result = 1 if rs is less than immediate;
		otherwise result = 0. Place result in register rt.Do not trap on
		overflow.*/
}

void CPU::ANDI(void)
{
	/* ANDI rt, rs, immediate
		Zero - extend 16 - bit immediate, AND with contents of register rs
		and place result in register rt.*/
}

void CPU::ORI(void)
{
	/* ORI rt, rs, immediate
		Zero - extend 16 - bit immediate, OR with contents of register rs
		and place result in register rt.*/
}

void CPU::XORI(void)
{
	/* XORI rt, rs, immediate
		Zero - extend 16 - bit immediate, exclusive OR with contents of
		register rs and place result in register rt.*/
}

void CPU::LUI(void)
{
	/* LUI rt, immediate
		Shift 16 - bit immediate left 16 bits.Set least significant 16 bits
		of word to zeroes.Store result in register rt.*/
}

// Computational Instructions (R-Type).
void CPU::ADD(void)
{
	/* ADD rd, rs, rt
		Add contents of registers rs and rt and place 32 - bit result in
		register rd.Trap on two’s complement overflow.*/
}

void CPU::ADDU(void)
{
	/* ADDU rd, rs, rt
		Add contents of registers rs and rt and place 32 - bit result in
		register rd.Do not trap on overflow.*/
}

void CPU::SUB(void)
{
	/* SUB rd, rs, rt
		Subtract contents of registers rt and rs and place 32 - bit result
		in register rd.Trap on two’s complement overflow.*/
}

void CPU::SUBU(void)
{
	/* SUBU rd, rs, rt
		Subtract contents of registers rt and rs and place 32 - bit result
		in register rd.Do not trap on overflow.*/
}

void CPU::SLT(void)
{
	/* SLT rd, rs, rt
		Compare contents of register rt to register rs(as signed 32 - bit
			integers).
		If register rs is less than rt, result = 1; otherwise, result = 0.*/
}

void CPU::SLTU(void)
{
	/* SLTU rd, rs, rt
		Compare contents of register rt to register rs(as unsigned 32 -
		bit integers).If register rs is less than rt, result = 1; otherwise, result = 0.*/
}

void CPU::AND(void)
{
	/* AND rd, rs, rt
		Bit - wise AND contents of registers rs and rt and place result in
		register rd.*/
}

void CPU::OR(void)
{
	/* OR rd, rs, rt
		Bit - wise OR contents of registers rs and rt and place result in
		register rd.*/
}

void CPU::XOR(void)
{
	/* XOR rd, rs, rt
		Bit - wise Exclusive OR contents of registers rs and rt and place
		result in register rd.*/
}

void CPU::NOR(void)
{
	/* NOR rd, rs, rt
		Bit - wise NOR contents of registers rs and rt and place result in
		register rd.*/
}

// Computational Instructions (R-Type Shifts).
void CPU::SLL(void)
{
	/* SLL rd, rt, shamt
		Shift contents of register rt left by shamt bits, inserting zeroes
		into low order bits.Place 32 - bit result in register rd.*/
}

void CPU::SRL(void)
{
	/* SRL rd, rt, shamt
		Shift contents of register rt right by shamt bits, inserting zeroes
		into high order bits.Place 32 - bit result in register rd.*/
}

void CPU::SRA(void)
{
	/* SRA rd, rt, shamt
		Shift contents of register rt right by shamt bits, sign - extending
		the high order bits.Place 32 - bit result in register rd.*/

}

void CPU::SLLV(void)
{
	/* SLLV rd, rt, rs
		Shift contents of register rt left.Low - order 5 bits of register rs
		specify number of bits to shift.Insert zeroes into low order bits
		of rt and place 32 - bit result in register rd.*/

}

void CPU::SRLV(void)
{
	/* SRLV rd, rt, rs
		Shift contents of register rt right.Low - order 5 bits of register rs
		specify number of bits to shift.Insert zeroes into high order bits
		of rt and place 32 - bit result in register rd.*/

}

void CPU::SRAV(void)
{
	/* SRAV rd, rt, rs
		Shift contents of register rt right.Low - order 5 bits of register rs
		specify number of bits to shift.Sign - extend the high order bits
		of rt and place 32 - bit result in register rd.*/
}

// Multiply / Divide Instructions.
void CPU::MULT(void)
{
	/* MULT rs, rt
		Multiply contents of registers rs and rt as twos complement
		values.Place 64 - bit result in special registers HI / LO*/

}

void CPU::MULTU(void)
{
	/* MULTU rs, rt
		Multiply contents of registers rs and rt as unsigned values.Place
		64 - bit result in special registers HI / LO*/

}

void CPU::DIV(void)
{
	/* DIV rs, rt
		Divide contents of register rs by rt treating operands as twos
		complements values.Place 32 - bit quotient in special register
		LO, and 32 - bit remainder in HI.*/

}

void CPU::DIVU(void)
{
	/* DIVU rs, rt
		Divide contents of register rs by rt treating operands as unsigned
		values.Place 32 - bit quotient in special register LO, and 32 - bit
		remainder in HI.*/

}

void CPU::MFHI(void)
{
	/* MFHI rd
		Move contents of special register HI to register rd.*/

}

void CPU::MFLO(void)
{
	/* MFLO rd
		Move contents of special register LO to register rd.*/

}

void CPU::MTHI(void)
{
	/* MTHI rd
		Move contents of special register rd to special register HI.*/

}

void CPU::MTLO(void)
{
	/* MTLO rd
		Move contents of register rd to special register LO.*/
}

// Jump Instructions (J-Type).
void CPU::J(void)
{
	/* J target
		Shift 26 - bit target address left two bits, combine with highorder
		4 bits of PC and jump to address with a one instruction
		delay.*/

}

void CPU::JAL(void)
{
	/* JAL target
		Shift 26 - bit target address left two bits, combine with highorder
		4 bits of PC and jump to address with a one instruction
		delay.Place address of instruction following delay slot in r31
		(link register).*/

}

void CPU::JR(void)
{
	/* JR rs
		Jump to address contained in register rs with a one instruction
		delay.*/

}

void CPU::JALR(void)
{
	/* JALR rs, rd
		Jump to address contained in register rs with a one instruction
		delay.Place address of instruction following delay slot in rd.*/
}

// Branch Instructions (J-Type).
void CPU::BEQ(void)
{
	/* BEQ rs, rt, offset
		Branch to target address if register rs equal to rt*/

}

void CPU::BNE(void)
{
	/* BNE rs, rt, offset
		Branch to target address if register rs not equal to rt.*/

}

void CPU::BLEZ(void)
{
	/* BLEZ rs, offset
		Branch to target address if register rs less than or equal to 0.*/

}

void CPU::BGTZ(void)
{
	/* BGTZ rs, offset
		Branch to target address if register rs greater than 0.*/

}

void CPU::BLTZ(void)
{
	/* BLTZ rs, offset
		Branch to target address if register rs less than 0.*/

}

void CPU::BGEZ(void)
{
	/* BGEZ rs, offset
		Branch to target address if register rs greater than or equal to 0.*/

}

void CPU::BLTZAL(void)
{
	/* BLTZAL rs, offset
		Place address of instruction following delay slot in register r31
		(link register).Branch to target address if register rs less than 0.*/

}

void CPU::BGEZAL(void)
{
	/* BGEZAL rs, offset
		Place address of instruction following delay slot in register r31
		(link register).Branch to target address if register rs is greater
		than or equal to 0.*/
}

// Special Instructions
void CPU::SYSCALL(void)
{
	/* SYSCALL
		Initiates system call trap, immediately transferring control to
		exception handler.*/

}

void CPU::BREAK(void)
{
	/* BREAK
		Initiates breakpoint trap, immediately transferring control to
		exception handler.*/
}

// Co-Processor Instructions.
void CPU::LWCz(void)
{
	/* LWCz rt, offset(base)
		Sign - extend 16 - bit offset and add to base to form address.Load
		contents of addressed word into co - processor register rt of coprocessor
		unit z.*/

}

void CPU::SWCz(void)
{
	/* SWCz rt, offset(base)
		Sign - extend 16 - bit offset and add to base to form address.Store
		contents of co - processor register rt from co - processor unit z at
		addressed memory word.*/

}

void CPU::MTCz(void)
{
	/* MTCz rt, rd
		Move contents of CPU register rt into co - processor register rd of
		co - processor unit z.*/

}

void CPU::MFCz(void)
{
	/* MFCz rt, rd
		Move contents of co - processor register rd from co - processor unit
		z to CPU register rt.*/

}

void CPU::CTCz(void)
{
	/* CTCz rt, rd
		Move contents of CPU register rt into co - processor control register
		rd of co - processor unit z.*/

}

void CPU::CFCz(void)
{
	/* CFCz rt, rd
		Move contents of control register rd of co - processor unit z into
		CPU register rt.*/

}

void CPU::COPz(void)
{
	/* COPz cofun
		Co - processor z performs an operation.The state of the R3051 /
		52 is not modified by a co - processor operation.*/

}

void CPU::BCzT(void)
{
	/* BCzT offset
		Compute a branch target address by adding address of
		instruction in the 16 - bit offset(shifted left two bits and signextended
		to 32 - bits).Branch to the target address(with a delay
		of one instruction) if co - processor z’s condition line is true.*/

}

void CPU::BCzF(void)
{
	/* BCzF offset
		Compute a branch target address by adding address of
		instruction in the 16 - bit offset(shifted left two bits and signextended
		to 32 - bits).Branch to the target address(with a delay
		of one instruction) if co - processor z’s condition line is false.*/
}

// System Control Co-processor Instructions.
void CPU::MTC0(void)
{
	/* MTC0 rt, rd
		Store contents of CPU register rt into register rd of CP0.This
		follows the convention of store operations.*/

}

void CPU::MFC0(void)
{
	/* MFC0 rt, rd
		Load CPU register rt with contents of CP0 register rd.*/

}

void CPU::TLBR(void)
{
	/* TLBR
		Load EntryHi and EntryLo registers with TLB entry pointed at by
		Index register.*/

}

void CPU::TLBWI(void)
{
	/* TLBWI
		Load TLB entry pointed at by Index register with contents of
		EntryHi and EntryLo registers.*/

}

void CPU::TLBWR(void)
{
	/* TLBWR
		Load TLB entry pointed at by Random register with contents of
		EntryHi and EntryLo registers.*/

}

void CPU::TLBP(void)
{
	/* TLBP
		Load Index register with address of TLB entry whose contents
		match EntryHi and EntryLo.If no TLB entry matches, set highorder
		bit of Index register.*/

}

void CPU::RFE(void)
{
	/* RFE
		Restore previous interrupt mask and mode bits of status register
		into current status bits.Restore old status bits into previous
		status bits.*/
}
