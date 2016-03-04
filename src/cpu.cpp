#include "cpu.h"
#include "memory.h"
#include "encoding.h"
#include <string.h>

#if 0
#define TODO(X) static_assert(false, "TODO:" #X)
#else
#define TODO(X)
#endif

CPU::CPU(Memory &memory_)
	: memory(memory_) 
{
	Reset();
}

void CPU::Reset()
{
	// Zero all of the registers.
	for (auto &x : registers.data)
	{
		x = 0;
	}
	pc = 0;
	hi = 0;
	lo = 0;

	// Put nops into the pipeline
	auto nop = Instruction(OpcodeEncoding::ADDI, Register::ZERO, Register::ZERO, Register::ZERO, 0, SpecialEncoding::ADD);

	IF.instruction  = nop;
	ID.instruction  = nop;
	EX.instruction  = nop;
	MEM.instruction = nop;
	WB.instruction  = nop;
}

void CPU::FetchInstruction(void)
{
	// Move the previously fetched instruction to the decode stage.
	ID.instruction = IF.instruction;
	IF.instruction = memory.LoadWord(pc);
}

void CPU::DecodeInstruction(void)
{
	EX.instruction        = ID.instruction;
	EX.sign_extended_data = sign_extend(ID.instruction.imm());
}

void CPU::ExecuteInstruction(const Instruction & instruction)
{
	auto nop = Instruction(OpcodeEncoding::ADDI, Register::ZERO, Register::ZERO, Register::ZERO, 0, SpecialEncoding::ADD);
	// Introduce the instruction into the pipeline.
	IF.instruction = instruction;
	// Pass the data through the pipeline (minus the instruction fetch.)
	for (int i = 0; i < 5; i++)
	{
		Writeback();
		AccessMemory();
		Execute();
		DecodeInstruction();
		// Introduce nop into the pipeline.
		ID.instruction = IF.instruction;
		IF.instruction = nop;
	}
}

uint32_t CPU::ExecuteSpecial(void)
{
	SpecialEncoding funct = EX.instruction.funct();
	switch (funct)
	{
	case SpecialEncoding::SLL: SLL(); break;
	case SpecialEncoding::SRL: SRL(); break;
	case SpecialEncoding::SRA: SRA(); break;
	case SpecialEncoding::SLLV: SLLV(); break;
	case SpecialEncoding::SRLV: SRLV(); break;
	case SpecialEncoding::SRAV: SRAV(); break;
	case SpecialEncoding::JR: JR(); break;
	case SpecialEncoding::JALR: JALR(); break;
	case SpecialEncoding::SYSCALL: SYSCALL(); break;
	case SpecialEncoding::BREAK: BREAK(); break;
	case SpecialEncoding::MFHI: MFHI(); break;
	case SpecialEncoding::MTHI: MTHI(); break;
	case SpecialEncoding::MFLO: MFLO(); break;
	case SpecialEncoding::MTLO: MTLO(); break;
	case SpecialEncoding::MULT: MULT(); break;
	case SpecialEncoding::MULTU: MULTU(); break;
	case SpecialEncoding::DIV: DIV(); break;
	case SpecialEncoding::DIVU: DIVU(); break;
	case SpecialEncoding::ADD: ADD(); break;
	case SpecialEncoding::ADDU: ADDU(); break;
	case SpecialEncoding::SUB: SUB(); break;
	case SpecialEncoding::SUBU: SUBU(); break;
	case SpecialEncoding::AND: AND(); break;
	case SpecialEncoding::OR: OR(); break;
	case SpecialEncoding::XOR: XOR(); break;
	case SpecialEncoding::NOR: NOR(); break;
	case SpecialEncoding::SLT: SLT(); break;
	case SpecialEncoding::SLTU: SLTU(); break;
	}
	return 0;
}

uint32_t CPU::ExecuteImmediate(void)
{
	auto encoding = EX.instruction.op();
	switch (encoding)
	{
	case OpcodeEncoding::ADDI: ADDI(); break;
	case OpcodeEncoding::ADDIU: ADDIU(); break;
	case OpcodeEncoding::SLTI: SLTI(); break;
	case OpcodeEncoding::SLTIU: SLTIU(); break;
	case OpcodeEncoding::ANDI: ANDI(); break;
	case OpcodeEncoding::ORI: ORI(); break;
	case OpcodeEncoding::XORI: XORI(); break;
	case OpcodeEncoding::LUI: LUI(); break;
	}
	return 0;
}

uint32_t CPU::ExecuteBranch(void)
{
	TODO("Implement ExecuteBranch");
	return 0;
}

void CPU::Execute(void)
{
	auto op = EX.instruction.op();
	MEM.instruction = EX.instruction;
	if (is_special(op))
	{
		MEM.alu_out = ExecuteSpecial();
	}
	else if (is_immediate(op))
	{
		MEM.alu_out = ExecuteImmediate();
	}
	else if (is_branch(op))
	{
		MEM.alu_out = ExecuteBranch();
	}
	else if (is_memory_access(op))
	{
		MEM.alu_out = registers[EX.instruction.rs()] + EX.sign_extended_data;
	}
}

void CPU::AccessMemory(void)
{
	// Used by LWL and LWR to store intermediate results.
	uint32_t read_word;
	uint32_t byte_count;
	WB.instruction = MEM.instruction;
	if (MEM.instruction.is_load())
	{
		auto &reg = registers[MEM.instruction.rt()];
		switch (MEM.instruction.op())
		{
		case OpcodeEncoding::LB:
			reg = sign_extend(memory.LoadByte(MEM.alu_out));
			break;
		case OpcodeEncoding::LH:
			reg = sign_extend(memory.LoadHalfWord(MEM.alu_out));
			break;
		case OpcodeEncoding::LWL:
			read_word = memory.LoadWord((MEM.alu_out >> 2) << 2);
			// How many of the least significant bytes of the register to keep.
			byte_count = 3 - (MEM.alu_out & 0x3);
			// Copy the retained bits to the read word.
			memcpy(&read_word, &reg, byte_count);
			// Write back into the register.
			reg = read_word;
			break;
		case OpcodeEncoding::LW:
			reg = memory.LoadWord(MEM.alu_out);
			break;
		case OpcodeEncoding::LBU:
			reg = memory.LoadByte(MEM.alu_out);
			break;
		case OpcodeEncoding::LHU:
			reg = memory.LoadHalfWord(MEM.alu_out);
			break;
		case OpcodeEncoding::LWR:
			read_word = memory.LoadWord((MEM.alu_out >> 2) << 2);
			// How many bytes of the read word to actually copy into the register.
			byte_count = 4 - (MEM.alu_out & 0x3);
			// Shift bytes to be copied to the lsb.
			read_word >>= 8 * (MEM.alu_out & 0x3);
			memcpy(&reg, &read_word, byte_count);
			break;
		}
	}
	else if (MEM.instruction.is_store())
	{
		switch (MEM.instruction.op())
		{
		case  OpcodeEncoding::SB:
			break;
		case  OpcodeEncoding::SH:
			break;
		case  OpcodeEncoding::SWL:
			break;
		case  OpcodeEncoding::SW:
			break;
		case  OpcodeEncoding::SWR:
			break;
		}
	}
}

void CPU::Writeback(void)
{
	TODO("Implement");
}

void CPU::Start(void)
{
	while (1)
	{
		// Perform the stages in reverse, using the values from the last clock cycle.
		Writeback();
		Execute();
		AccessMemory();
		DecodeInstruction();
		FetchInstruction();
	}
}
void CPU::TriggerOverflowException()
{
	TODO("Implement");
	debug_state.has_overflown = true;
}

// Load Instructions.
void CPU::LB(void)
{
	/* LB rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Sign - extend contents of addressed byte and load into rt. */
	TODO("Implement");
}

void CPU::LBU(void)
{
	/* LBU rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Zero - extend contents of addressed byte and load into rt.*/
	TODO("Implement");
}

void CPU::LH(void)
{
	/* LH rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Sign - extend contents of addressed byte and load into rt.*/
	TODO("Implement");
}

void CPU::LHU(void)
{
	/* LHU rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Zero - extend contents of addressed byte and load into rt.*/
	TODO("Implement");
}

void CPU::LW(void)
{
	/* LW rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Load contents of addressed word into register rt.*/
	TODO("Implement");
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
	TODO("Implement");
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
	TODO("Implement");
}

// Store Instructions.
void CPU::SB(void)
{
	/* SB rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Store least significant byte of register rt at addressed location.*/
	TODO("Implement");
}

void CPU::SH(void)
{
	/* SH rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Store least significant halfword of register rt at addressed location.*/
	TODO("Implement");
}

void CPU::SW(void)
{
	/* SW rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Store least significant word of register rt at addressed location.*/
	TODO("Implement");
}

void CPU::SWL(void)
{
	/* SWL rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Shift contents of register rt right so that leftmost byte of the word
		is in position of addressed byte.Store bytes containing original
		data into corresponding bytes at addressed byte.*/
	TODO("Implement");
}

void CPU::SWR(void)
{
	/* SWR rt, offset(base)
		Sign - extend 16 - bit offset and add to contents of register base to
		form address.
		Shift contents of register rt left so that rightmost byte of the word
		is in position of addressed byte.Store bytes containing original
		data into corresponding bytes at addressed byte.*/
	TODO("Implement");
}

// Computational Instructions (I-Type).
void CPU::ADDI(void)
{
	/* ADDI rt, rs, immediate
		Add 16 - bit sign - extended immediate to register rs and place 32 -
		bit result in register rt.Trap on two�s complement overflow.*/
	auto &rs = registers[EX.instruction.rs()];
	auto &rt = registers[EX.instruction.rt()];
	auto sum = rs + EX.sign_extended_data;
	auto rs_neg = extract(rs, 31, 31);
	auto imm_neg = extract(EX.sign_extended_data, 31, 31);
	auto sum_neg = extract(sum, 31, 31);

	if ((rs_neg && imm_neg && !sum_neg) || // Negative overflow.
		(!rs_neg && !imm_neg && sum_neg))  // Positive overflow.
	{
		TriggerOverflowException();
	}
	else
	{
		rt = sum;
	}
}

void CPU::ADDIU(void)
{
	/* ADDIU rt, rs, immediate
		Add 16 - bit sign - extended immediate to register rs and place 32 -
		bit result in register rt.Do not trap on overflow.*/
	auto &rs = registers[EX.instruction.rs()];
	auto &rt = registers[EX.instruction.rt()];
	auto sum = rs + EX.sign_extended_data;
	rt = sum;
}

void CPU::SLTI(void)
{
	/*	SLTI rt, rs, immediate
		Compare 16 - bit sign - extended immediate with register rs as
		signed 32 - bit integers.Result = 1 if rs is less than immediate;
		otherwise result = 0.
		Place result in register rt.*/
	TODO("Implement");
}

void CPU::SLTIU(void)
{
	/* SLTIU rt, rs, immediate
		Compare 16 - bit sign - extended immediate with register rs as
		unsigned 32 - bit integers.Result = 1 if rs is less than immediate;
		otherwise result = 0. Place result in register rt.Do not trap on
		overflow.*/
	TODO("Implement");
}

void CPU::ANDI(void)
{
	/* ANDI rt, rs, immediate
		Zero - extend 16 - bit immediate, AND with contents of register rs
		and place result in register rt.*/
	TODO("Implement");
}

void CPU::ORI(void)
{
	/* ORI rt, rs, immediate
		Zero - extend 16 - bit immediate, OR with contents of register rs
		and place result in register rt.*/
	TODO("Implement");
}

void CPU::XORI(void)
{
	/* XORI rt, rs, immediate
		Zero - extend 16 - bit immediate, exclusive OR with contents of
		register rs and place result in register rt.*/
	TODO("Implement");
}

void CPU::LUI(void)
{
	/* LUI rt, immediate
		Shift 16 - bit immediate left 16 bits.Set least significant 16 bits
		of word to zeroes.Store result in register rt.*/
	TODO("Implement");
}

// Computational Instructions (R-Type).
void CPU::ADD(void)
{
	/* ADD rd, rs, rt
		Add contents of registers rs and rt and place 32 - bit result in
		register rd.Trap on two�s complement overflow.*/
	auto &rs = registers[EX.instruction.rs()];
	auto &rt = registers[EX.instruction.rt()];
	auto sum = rs + rt;
	if (sum < rs)
	{
		TriggerOverflowException();
	}
	else
	{
		registers[EX.instruction.rd()] = sum;
	}
	
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
		in register rd.Trap on two�s complement overflow.*/
	auto rs      = to_signed(registers[EX.instruction.rs()]);
	auto rt      = to_signed(registers[EX.instruction.rt()]);
#if USE_GCC_BUILTINS
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

void CPU::SLT(void)
{
	/* SLT rd, rs, rt
		Compare contents of register rt to register rs(as signed 32 - bit integers).
		If register rs is less than rt, result = 1; otherwise, result = 0.*/
    auto rs = to_unsigned(registers[EX.instruction.rs()]);
    auto rt = to_unsigned(registers[EX.instruction.rt()]);
    if(rs < rt)
    {
        registers[EX.instruction.rd()] = 1;
    }
    else
    {
        registers[EX.instruction.rd()] = 0;
    }
}

void CPU::SLTU(void)
{
	/* SLTU rd, rs, rt
		Compare contents of register rt to register rs(as unsigned 32 - bit integers).
        If register rs is less than rt, result = 1; otherwise, result = 0.*/
	TODO("Implement");
}

void CPU::AND(void)
{
	/* AND rd, rs, rt
		Bit - wise AND contents of registers rs and rt and place result in
		register rd.*/
	TODO("Implement");
}

void CPU::OR(void)
{
	/* OR rd, rs, rt
		Bit - wise OR contents of registers rs and rt and place result in
		register rd.*/
	TODO("Implement");
}

void CPU::XOR(void)
{
	/* XOR rd, rs, rt
		Bit - wise Exclusive OR contents of registers rs and rt and place
		result in register rd.*/
	TODO("Implement");
}

void CPU::NOR(void)
{
	/* NOR rd, rs, rt
		Bit - wise NOR contents of registers rs and rt and place result in
		register rd.*/
	TODO("Implement");
}

// Computational Instructions (R-Type Shifts).
void CPU::SLL(void)
{
	/* SLL rd, rt, shamt
		Shift contents of register rt left by shamt bits, inserting zeroes
		into low order bits.Place 32 - bit result in register rd.*/
	TODO("Implement");
}

void CPU::SRL(void)
{
	/* SRL rd, rt, shamt
		Shift contents of register rt right by shamt bits, inserting zeroes
		into high order bits.Place 32 - bit result in register rd.*/
	TODO("Implement");
}

void CPU::SRA(void)
{
	/* SRA rd, rt, shamt
		Shift contents of register rt right by shamt bits, sign - extending
		the high order bits.Place 32 - bit result in register rd.*/
	TODO("Implement");

}

void CPU::SLLV(void)
{
	/* SLLV rd, rt, rs
		Shift contents of register rt left.Low - order 5 bits of register rs
		specify number of bits to shift.Insert zeroes into low order bits
		of rt and place 32 - bit result in register rd.*/
	TODO("Implement");

}

void CPU::SRLV(void)
{
	/* SRLV rd, rt, rs
		Shift contents of register rt right.Low - order 5 bits of register rs
		specify number of bits to shift.Insert zeroes into high order bits
		of rt and place 32 - bit result in register rd.*/
	TODO("Implement");

}

void CPU::SRAV(void)
{
	/* SRAV rd, rt, rs
		Shift contents of register rt right.Low - order 5 bits of register rs
		specify number of bits to shift.Sign - extend the high order bits
		of rt and place 32 - bit result in register rd.*/
	TODO("Implement");
}

// Multiply / Divide Instructions.
void CPU::MULT(void)
{
	/* MULT rs, rt
		Multiply contents of registers rs and rt as twos complement
		values.Place 64 - bit result in special registers HI / LO*/
    auto rs = to_signed(uint64_t(registers[EX.instruction.rs()]));
    auto rt = to_signed(uint64_t(registers[EX.instruction.rt()]));
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

// Jump Instructions (J-Type).
void CPU::J(void)
{
	/* J target
		Shift 26 - bit target address left two bits, combine with highorder
		4 bits of PC and jump to address with a one instruction
		delay.*/
	TODO("Implement");

}

void CPU::JAL(void)
{
	/* JAL target
		Shift 26 - bit target address left two bits, combine with highorder
		4 bits of PC and jump to address with a one instruction
		delay.Place address of instruction following delay slot in r31
		(link register).*/
	TODO("Implement");

}

void CPU::JR(void)
{
	/* JR rs
		Jump to address contained in register rs with a one instruction
		delay.*/
	TODO("Implement");

}

void CPU::JALR(void)
{
	/* JALR rs, rd
		Jump to address contained in register rs with a one instruction
		delay.Place address of instruction following delay slot in rd.*/
	TODO("Implement");
}

// Branch Instructions (J-Type).
void CPU::BEQ(void)
{
	/* BEQ rs, rt, offset
		Branch to target address if register rs equal to rt*/
	TODO("Implement");

}

void CPU::BNE(void)
{
	/* BNE rs, rt, offset
		Branch to target address if register rs not equal to rt.*/
	TODO("Implement");

}

void CPU::BLEZ(void)
{
	/* BLEZ rs, offset
		Branch to target address if register rs less than or equal to 0.*/
	TODO("Implement");

}

void CPU::BGTZ(void)
{
	/* BGTZ rs, offset
		Branch to target address if register rs greater than 0.*/
	TODO("Implement");

}

void CPU::BLTZ(void)
{
	/* BLTZ rs, offset
		Branch to target address if register rs less than 0.*/
	TODO("Implement");

}

void CPU::BGEZ(void)
{
	/* BGEZ rs, offset
		Branch to target address if register rs greater than or equal to 0.*/
	TODO("Implement");

}

void CPU::BLTZAL(void)
{
	/* BLTZAL rs, offset
		Place address of instruction following delay slot in register r31
		(link register).Branch to target address if register rs less than 0.*/
	TODO("Implement");

}

void CPU::BGEZAL(void)
{
	/* BGEZAL rs, offset
		Place address of instruction following delay slot in register r31
		(link register).Branch to target address if register rs is greater
		than or equal to 0.*/
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
		of one instruction) if co - processor z�s condition line is true.*/
	TODO("Implement");

}

void CPU::BCzF(void)
{
	/* BCzF offset
		Compute a branch target address by adding address of
		instruction in the 16 - bit offset(shifted left two bits and signextended
		to 32 - bits).Branch to the target address(with a delay
		of one instruction) if co - processor z�s condition line is false.*/
	TODO("Implement");
}

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
