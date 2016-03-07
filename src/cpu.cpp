#include "cpu.h"
#include "memory.h"
#include "encoding.h"
#include <string.h>


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
	auto nop = Instruction(OpcodeEncoding::ADDIU, Register::ZERO, Register::ZERO, Register::ZERO, 0, SpecialEncoding::ADD);
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




