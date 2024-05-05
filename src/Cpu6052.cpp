#include "Cpu6502.h"
#include "Bus.h"

namespace nes
{
    Cpu6502::Cpu6502()
    {
        using a = Cpu6502;
	    lookup_ = 
	    {
	    	{ "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
	    	{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
	    	{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
	    	{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
	    	{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
	    	{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
	    	{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
	    	{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
	    	{ "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
	    	{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
	    	{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
	    	{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
	    	{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
	    	{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
	    	{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
	    	{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
	    };
    }

    Cpu6502::~Cpu6502()
    {
    }

    void Cpu6502::clock()
    {
        if (cycles_ != 0)
        {
            cycles_--;
            return;
        }

        opcode_ = read(reg.pc);
        reg.pc++;

        cycles_ = lookup_[opcode_].cycles;

        // perform addressing and operation
        u8 addCycle1 = (this->*lookup_[opcode_].addrmode)();
        u8 addCycle2 = (this->*lookup_[opcode_].operation)();

        // determine if extra clock cycles are needed
        cycles_ += (addCycle1 & addCycle2);

        cycles_--;
    }

    void Cpu6502::reset()
    {
        reg.a = 0x00;
        reg.x = 0x00;
        reg.y = 0x00;
        reg.sp = 0xFD;
        reg.status = 0x00 | U;

        addrAbs_ = 0xFFFC;
        u16 low = read(addrAbs_);
        u16 high = read(addrAbs_ + 1);

        reg.pc = (high << 8) | low;

        addrRel_ = 0x0000;
        addrAbs_ = 0x0000;
        fetched_ = 0x00;

        cycles_ = 8;
    }

    void Cpu6502::irq()
    {
        if (getFlag(I) != 0)
            return;

        // push current program counter onto stack
        write(0x0100 + reg.sp, (reg.pc >> 8) & 0x00FF);
        reg.sp--;
        write(0x0100 + reg.sp, reg.pc & 0x00FF);
        reg.sp--;

        // push the status register onto the stack
        setFlag(B, 0);
        setFlag(U, 1);
        setFlag(I, 1);
        write(0x0100 + reg.sp, reg.status);
        reg.sp--;

        addrAbs_ = 0xFFFE;
        u16 low = read(addrAbs_);
        u16 high = read(addrAbs_ + 1);

        reg.pc = (high << 8) | low;

        cycles_ = 7;
    }

    void Cpu6502::nmi()
    {
        // push current program counter onto stack
        write(0x0100 + reg.sp, (reg.pc >> 8) & 0x00FF);
        reg.sp--;
        write(0x0100 + reg.sp, reg.pc & 0x00FF);
        reg.sp--;

        // push the status register onto the stack
        setFlag(B, 0);
        setFlag(U, 1);
        setFlag(I, 1);
        write(0x0100 + reg.sp, reg.status);
        reg.sp--;

        addrAbs_ = 0xFFFA;
        u16 low = read(addrAbs_);
        u16 high = read(addrAbs_ + 1);

        reg.pc = (high << 8) | low;

        cycles_ = 8;
    }

    u8 Cpu6502::IMP()
    {
        fetched_ = reg.a;
        return 0;
    }

    u8 Cpu6502::IMM()
    {
        addrAbs_ = reg.pc++;
        return 0;
    }

    u8 Cpu6502::ZP0()
    {
        addrAbs_ = read(reg.pc);
        reg.pc++;
        addrAbs_ &= 0x00FF;
        return 0;
    }

    u8 Cpu6502::ZPX()
    {
        addrAbs_ = read(reg.pc) + reg.x;
        reg.pc++;
        addrAbs_ &= 0x00FF;
        return 0;
    }

    u8 Cpu6502::ZPY()
    {
        addrAbs_ = read(reg.pc) + reg.y;
        reg.pc++;
        addrAbs_ &= 0x00FF;
        return 0;
    }

    u8 Cpu6502::REL()
    {
        addrRel_ = read(reg.pc);
        reg.pc++;

        // relative address is signed in twos complement, so if the 7th bit is 1, then the number is negative, as it exceeds 0x007F (127)
        if (addrRel_ & 0x0080)      
            addrRel_ |= 0xFF00;

        return 0;
    }

    u8 Cpu6502::ABS()
    {
        u16 low = (u16)(read(reg.pc));
        reg.pc++;
        u16 high = (u16)(read(reg.pc));
        reg.pc++;

        addrRel_ = (high << 8) | low;

        return 0;
    }

    u8 Cpu6502::ABX()
    {
        u16 low = (u16)(read(reg.pc));
        reg.pc++;
        u16 high = (u16)(read(reg.pc));
        reg.pc++;

        addrAbs_ = (high << 8) | low;
        addrAbs_ += reg.x;

        // If the high byte has changed, we need to change the page, so we may need another clock cycle
        if ((addrAbs_ & 0xFF00) != (high << 8))
            return 1;

        return 0;
    }

    u8 Cpu6502::ABY()
    {
        u16 low = (u16)(read(reg.pc));
        reg.pc++;
        u16 high = (u16)(read(reg.pc));
        reg.pc++;

        addrAbs_ = (high << 8) | low;
        addrAbs_ += reg.y;

        // If the high byte has changed, we need to change the page, so we may need another clock cycle
        if ((addrAbs_ & 0xFF00) != (high << 8))
            return 1;

        return 0;
    }

    u8 Cpu6502::IND()
    {
        u16 low = (u16)(read(reg.pc));
        reg.pc++;
        u16 high = (u16)(read(reg.pc));
        reg.pc++;

        u16 ptr = (high << 8) | low;

        if (low == 0x00FF)
            addrAbs_ = (read(ptr & 0xFF00) << 8) | read(ptr);

        else
            addrAbs_ = (read(ptr + 1) << 8) | read(ptr);

        return 0;
    }

    u8 Cpu6502::IZX()
    {
        u16 t = read(reg.pc);
        reg.pc++;

        u16 low = read((u16)(t + (u16)(reg.x)) &  0x00FF);
        u16 high = read((u16)(t + (u16)(reg.x + 1)) &  0x00FF);

        addrAbs_ = (high << 8) | low;

        return 0;
    }

    u8 Cpu6502::IZY()
    {
        u16 t = read(reg.pc);
        reg.pc++;

        u16 low = read((u16)(t + (u16)(reg.y)) &  0x00FF);
        u16 high = read((u16)(t + (u16)(reg.y + 1)) &  0x00FF);

        addrAbs_ = (high << 8) | low;

        return 0;
    }

    /**
     * ----------------------------
     * Instructions
     * ----------------------------
    */

    u8 Cpu6502::fetch()
    {
        if (lookup_[opcode_].addrmode != &Cpu6502::IMP)
            fetched_ = read(addrAbs_);

        return fetched_;
    }

    u8 Cpu6502::ADC()
    {
        fetch();

        temp_ = (u16)(reg.a) + (u16)(fetched_) + (u16)(getFlag(C));

        setFlag(C, temp_ > 0x00FF);
        setFlag(Z, (temp_ & 0x00FF) == 0);
        setFlag(V, (~((u16)(reg.a) ^ (u16)(fetched_)) & ((u16)(reg.a) ^ (u16)(temp_))) & 0x0080);
        setFlag(N, temp_ & 0x0080);

        reg.a = temp_ & 0x00FF;

        return 1;  
    }

    u8 Cpu6502::AND()
    {
        fetch();

        reg.a = reg.a & fetched_;
        setFlag(Z, reg.a == 0);
        setFlag(N, reg.a & 0x80);

        return 1;
    }

    u8 Cpu6502::ASL()
    {
        fetch();

        temp_ = (u16)(fetched_) << 1;

        // if most significant bit in fetched was 1, then bit 9 should be 1 after shifting once. In that case, carry is 1
        setFlag(C, temp_ & 0x0100);
        setFlag(Z, (temp_ & 0x00FF) == 0);
        setFlag(N, temp_ & 0x0080);

        // if implied, then we write to accumulator, else we write to memory
        if (lookup_[opcode_].addrmode == &Cpu6502::IMP)
            reg.a = temp_ & 0x00FF;
        else 
            write(addrAbs_, temp_ & 0x00FF);

        return 0;
    }

    u8 Cpu6502::BCC()
    {
        if (getFlag(C) != 0)
            return 0;

        cycles_++;
        addrAbs_ = reg.pc + addrRel_;

        // if we need to go to a different page.
        if ((addrAbs_ & 0xFF00) != (reg.pc & 0xFF00))
            cycles_++;

        reg.pc = addrAbs_;
        
        return 0;
    }

    u8 Cpu6502::BCS()
    {
        if (getFlag(C) != 1)
            return 0;

        cycles_++;
        addrAbs_ = reg.pc + addrRel_;

        // if we need to go to a different page.
        if ((addrAbs_ & 0xFF00) != (reg.pc & 0xFF00))
            cycles_++;

        reg.pc = addrAbs_;
        
        return 0;
    }

    u8 Cpu6502::BEQ()
    {
        if (getFlag(Z) != 1)
            return 0;

        cycles_++;
        addrAbs_ = reg.pc + addrRel_;

        // if we need to go to a different page.
        if ((addrAbs_ & 0xFF00) != (reg.pc & 0xFF00))
            cycles_++;

        reg.pc = addrAbs_;
        
        return 0;
    }

    u8 Cpu6502::BIT()
    {
        fetch();

        temp_ = reg.a & fetched_;
        setFlag(Z, (temp_ & 0x00FF) == 0);
        setFlag(N, fetched_ & (1 << 7));
        setFlag(V, fetched_ & (1 << 6));

        return 0;
    }

    u8 Cpu6502::BMI()
    {
        if (getFlag(N) != 1)
            return 0;

        cycles_++;
        addrAbs_ = reg.pc + addrRel_;

        // if we need to go to a different page.
        if ((addrAbs_ & 0xFF00) != (reg.pc & 0xFF00))
            cycles_++;

        reg.pc = addrAbs_;
        
        return 0;
    }

    u8 Cpu6502::BNE()
    {
        if (getFlag(Z) != 0)
            return 0;

        cycles_++;
        addrAbs_ = reg.pc + addrRel_;

        // if we need to go to a different page.
        if ((addrAbs_ & 0xFF00) != (reg.pc & 0xFF00))
            cycles_++;

        reg.pc = addrAbs_;
        
        return 0;
    }

    u8 Cpu6502::BPL()
    {
        if (getFlag(N) != 0)
            return 0;

        cycles_++;
        addrAbs_ = reg.pc + addrRel_;

        // if we need to go to a different page.
        if ((addrAbs_ & 0xFF00) != (reg.pc & 0xFF00))
            cycles_++;

        reg.pc = addrAbs_;
        
        return 0;
    }

    u8 Cpu6502::BRK()
    {
        reg.pc++;

        setFlag(I, 1);
        write(0x0100 + reg.sp, (reg.pc >> 8) & 0x00FF);
        reg.sp--;
        write(0x0100 + reg.sp, reg.pc & 0x00FF);
        reg.sp--;

        setFlag(B, 1);
        write(0x0100 + reg.sp, reg.status);
        reg.sp--;
        setFlag(B, 0);

        reg.pc = (u16)(read(0xFFFE)) | ((u16)(read(0xFFFF)) << 8);
        return 0;
    }

    u8 Cpu6502::BVC()
    {
        if (getFlag(V) != 0)
            return 0;

        cycles_++;
        addrAbs_ = reg.pc + addrRel_;

        // if we need to go to a different page.
        if ((addrAbs_ & 0xFF00) != (reg.pc & 0xFF00))
            cycles_++;

        reg.pc = addrAbs_;
        
        return 0;
    }

    u8 Cpu6502::BVS()
    {
        if (getFlag(V) != 1)
            return 0;

        cycles_++;
        addrAbs_ = reg.pc + addrRel_;

        // if we need to go to a different page.
        if ((addrAbs_ & 0xFF00) != (reg.pc & 0xFF00))
            cycles_++;

        reg.pc = addrAbs_;
        
        return 0;
    }

    u8 Cpu6502::CLC()
    {
        setFlag(C, 0);
        return 0;
    }

    u8 Cpu6502::CLD()
    {
        setFlag(D, 0);
        return 0;
    }

    u8 Cpu6502::CLI()
    {
        setFlag(I, 0);
        return 0;
    }

    u8 Cpu6502::CLV()
    {
        setFlag(V, 0);
        return 0;
    }

    u8 Cpu6502::CMP()
    {
        fetch();

        temp_ = (u16)(reg.a) - (u16)(fetched_);
        setFlag(C, reg.a >= fetched_);
        setFlag(Z, (temp_ & 0x00FF) == 0);
        setFlag(N, temp_ & 0x0080);

        return 1;
    }

    u8 Cpu6502::CPX()
    {
        fetch();

        temp_ = (u16)(reg.x) - (u16)(fetched_);
        setFlag(C, reg.x >= fetched_);
        setFlag(Z, (temp_ & 0x00FF) == 0);
        setFlag(N, temp_ & 0x0080);

        return 0;
    }

    u8 Cpu6502::CPY()
    {
        fetch();

        temp_ = (u16)(reg.y) - (u16)(fetched_);
        setFlag(C, reg.y >= fetched_);
        setFlag(Z, (temp_ & 0x00FF) == 0);
        setFlag(N, temp_ & 0x0080);

        return 0;
    }

    u8 Cpu6502::DEC()
    {
        fetch();

        temp_ = fetched_ - 1;
        write(addrAbs_, temp_ & 0x00FF);
        setFlag(Z, (temp_ & 0x00FF) == 0);
        setFlag(N, temp_ & 0x0080);

        return 0;
    }

    u8 Cpu6502::DEX()
    {
        reg.x--;
        setFlag(Z, reg.x == 0);
        setFlag(N, reg.x & 0x80);

        return 0;
    }

    u8 Cpu6502::DEY()
    {
        reg.y--;
        setFlag(Z, reg.y == 0);
        setFlag(N, reg.y & 0x80);

        return 0;
    }

    u8 Cpu6502::EOR()
    {
        fetch();

        reg.a = reg.a ^ fetched_;
        setFlag(Z, reg.a == 0);
        setFlag(N, reg.a & 0x80);

        return 0;    
    }

    u8 Cpu6502::INC()
    {
        fetch();

        temp_ = fetched_ + 1;
        write(addrAbs_, temp_ & 0x00FF);
        setFlag(Z, (temp_ & 0x00FF) == 0);
        setFlag(N, temp_ & 0x0080);

        return 0;     
    }

    u8 Cpu6502::INX()
    {
        reg.x++;
        setFlag(Z, reg.x == 0);
        setFlag(N, reg.x & 0x80);

        return 0;
    }

    u8 Cpu6502::INY()
    {
        reg.y++;
        setFlag(Z, reg.y == 0);
        setFlag(N, reg.y & 0x80);

        return 0;
    }

    u8 Cpu6502::JMP()
    {
        reg.pc = addrAbs_;
        return 0;
    }

    u8 Cpu6502::JSR()
    {
        reg.pc--;

        // push pc on stack, first high byte then low byte
        write(0x0100 + reg.sp, (reg.pc >> 8) & 0x00FF);
        reg.sp--;
        write(0x0100 + reg.sp, reg.pc & 0x00FF);
        reg.sp--;

        reg.pc = addrAbs_;
        return 0;
    }
    
    u8 Cpu6502::LDA()
    {
        fetch();

        reg.a = fetched_;
        setFlag(Z, reg.a == 0);
        setFlag(N, reg.a & 0x80);

        return 1;
    }

    u8 Cpu6502::LDX()
    {
        fetch();

        reg.x = fetched_;
        setFlag(Z, reg.x == 0);
        setFlag(N, reg.x & 0x80);

        return 1;
    }

    u8 Cpu6502::LDY()
    {
        fetch();

        reg.y = fetched_;
        setFlag(Z, reg.y == 0);
        setFlag(N, reg.y & 0x80);

        return 1;
    }

    u8 Cpu6502::LSR()
    {
        fetch();

        temp_ = (u16)(fetched_) >> 1;

        // if least significant bit in fetched was 1, then carry is set
        setFlag(C, fetched_ & 0x01);
        setFlag(Z, (temp_ & 0x00FF) == 0);
        setFlag(N, temp_ & 0x0080);

        // if implied, then we write to accumulator, else we write to memory
        if (lookup_[opcode_].addrmode == &Cpu6502::IMP)
            reg.a = temp_ & 0x00FF;
        else 
            write(addrAbs_, temp_ & 0x00FF);

        return 0;
    }

    u8 Cpu6502::NOP()
    {
        // Some nops require an extra clock cycle
        switch (opcode_) 
        {
        case 0x1C:
        case 0x3C:
        case 0x5C:
        case 0x7C:
        case 0xDC:
        case 0xFC:
            return 1;
            break;
        }

        return 0;
    }

    u8 Cpu6502::ORA()
    {
        fetch();

        reg.a = reg.a | fetched_;
        setFlag(Z, reg.a == 0);
        setFlag(N, reg.a & 0x80);

        return 1;
    }

    u8 Cpu6502::PHA()
    {
        write(0x0100 + reg.sp, reg.a);
        reg.sp--;
        return 0;
    }

    u8 Cpu6502::PHP()
    {
        write(0x0100 + reg.sp, reg.status | B | U);
        setFlag(B, 0);
        setFlag(U, 0);
        reg.sp--;

        return 0;
    }

    u8 Cpu6502::PLA()
    {
        reg.sp++;
        reg.a = read(0x0100 + reg.sp);
        setFlag(Z, reg.a == 0);
        setFlag(N, reg.a & 0x80);
        
        return 0;
    }

    u8 Cpu6502::PLP()
    {
        reg.sp++;
        reg.status = read(0x0100 + reg.sp);
        setFlag(U, 1);

        return 0;
    }

    u8 Cpu6502::ROL()
    {
        fetch();

        temp_ = ((u16)(fetched_) << 1) | getFlag(C);
        setFlag(C, temp_ & 0x0100);
        setFlag(Z, (temp_ & 0x00FF) == 0);
        setFlag(N, temp_ & 0x0080);

        // if implied, then we write to accumulator, else we write to memory
        if (lookup_[opcode_].addrmode == &Cpu6502::IMP)
            reg.a = temp_ & 0x00FF;
        else 
            write(addrAbs_, temp_ & 0x00FF);

        return 0;
    }

    u8 Cpu6502::ROR()
    {
        fetch();

        temp_ = ((u16)(fetched_) >> 1) | ((u16)(getFlag(C)) << 7);
        setFlag(C, fetched_ & 0x01);
        setFlag(Z, (temp_ & 0x00FF) == 0);
        setFlag(N, temp_ & 0x0080);

        // if implied, then we write to accumulator, else we write to memory
        if (lookup_[opcode_].addrmode == &Cpu6502::IMP)
            reg.a = temp_ & 0x00FF;
        else 
            write(addrAbs_, temp_ & 0x00FF);

        return 0;
    }

    u8 Cpu6502::RTI()
    {
        reg.sp++;
        reg.status = read(0x0100 + reg.sp);
        reg.status &= ~B;
        reg.status &= ~U;

        reg.sp++;
        // low byte of the pc
        reg.pc = read(0x0100 + reg.sp);
        reg.sp++;
        // high byte
        reg.pc |= read(0x0100 + reg.sp) << 8;

        return 0;
    }

    u8 Cpu6502::RTS()
    {
        reg.sp++;
        // low byte of the pc
        reg.pc = read(0x0100 + reg.sp);
        reg.sp++;
        // high byte
        reg.pc |= read(0x0100 + reg.sp) << 8;

        reg.pc++;
        return 0;
    }

    u8 Cpu6502::SBC()
    {
        fetch();

        u16 n = (u16)(~fetched_);
        temp_ = (u16)(reg.a) + n + (u16)(getFlag(C));

        setFlag(C, temp_ & 0xFF00);
        setFlag(Z, (temp_ & 0x00FF) == 0);
        setFlag(V, ((temp_ ^ (u16)(reg.a)) & (temp_ ^ n)) & 0x0080);
        setFlag(N, temp_ & 0x0080);

        reg.a = temp_ & 0x00FF;
        
        return 1;
    }

    u8 Cpu6502::SEC()
    {
        setFlag(C, 1);
        return 0;
    }

    u8 Cpu6502::SED()
    {
        setFlag(D, 1);
        return 0;
    }

    u8 Cpu6502::SEI()
    {
        setFlag(I, 1);
        return 0;
    }

    u8 Cpu6502::STA()
    {
        write(addrAbs_, reg.a);
        return 0;
    }

    u8 Cpu6502::STX()
    {
        write(addrAbs_, reg.x);
        return 0;
    }

    u8 Cpu6502::STY()
    {
        write(addrAbs_, reg.y);
        return 0;
    }

    u8 Cpu6502::TAX()
    {
        reg.x = reg.a;
        setFlag(Z, reg.x == 0);
        setFlag(N, reg.x & 0x80);

        return 0;
    }

    u8 Cpu6502::TAY()
    {
        reg.y = reg.a;
        setFlag(Z, reg.y == 0);
        setFlag(N, reg.y & 0x80);

        return 0;
    }

    u8 Cpu6502::TSX()
    {
        reg.x = reg.sp;
        setFlag(Z, reg.x == 0);
        setFlag(N, reg.x & 0x80);

        return 0;
    }

    u8 Cpu6502::TXA()
    {
        reg.a = reg.x;
        setFlag(Z, reg.a == 0);
        setFlag(N, reg.a & 0x80);

        return 0;
    }

    u8 Cpu6502::TXS()
    {
        reg.sp = reg.x;
        return 0;
    }

    u8 Cpu6502::TYA()
    {
        reg.a = reg.y;
        setFlag(Z, reg.a == 0);
        setFlag(N, reg.a & 0x80);

        return 0;
    }

    u8 Cpu6502::XXX()
    {
        return 0;
    }

    u8 Cpu6502::read(u16 a) const
    {
        bus_->read(a);
    }

    void Cpu6502::write(u16 a, u8 d) const
    {
        bus_->write(a, d);
    }

    u8 Cpu6502::getFlag(FLAGS6502 f) const 
    {
        return (reg.status & f > 0) ? 1 : 0;
    }

    void Cpu6502::setFlag(FLAGS6502 f, bool v)
    {
        if (v)
            reg.status |= f;
        else 
            reg.status &= ~f;
    } 
}