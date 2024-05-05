#pragma once
#ifndef _CPU_6502_H
#define _CPU_6502_H

#include <string>
#include <vector>

#include "Util.h"

namespace nes
{
    class Bus;

    struct RegFile
    {
        u8 a = 0x00;
        u8 x = 0x00;
        u8 y = 0x00;
        u8 sp = 0x00;
        u16 pc = 0x0000;
        u8 status = 0x00;
    };

    class Cpu6502
    {
    public:
        Cpu6502();
        ~Cpu6502();

        void connectBus(Bus* b) { bus_ = b; }

        void clock();
        void reset();
        void irq();
        void nmi();

        enum FLAGS6502
        {
            C = (1 << 0),     // Carry bit
            Z = (1 << 1),     // Zero
            I = (1 << 2),     // Disable Interrupts
            D = (1 << 3),     // Decimal mode
            B = (1 << 4),     // Break
            U = (1 << 5),     // Unused
            V = (1 << 6),     // Overflow
            N = (1 << 7),     // Negative
        };

    public:
        RegFile reg;

    private:
        /**
         * Addressing modes
        */
        u8 IMP();  u8 IMM();
        u8 ZP0();  u8 ZPX();
        u8 ZPY();  u8 REL();
        u8 ABS();  u8 ABX();
        u8 ABY();  u8 IND();
        u8 IZX();  u8 IZY();

        /**
         * Instruction set
        */
        u8 ADC();  u8 AND();  u8 ASL();  u8 BCC();
        u8 BCS();  u8 BEQ();  u8 BIT();  u8 BMI();
        u8 BNE();  u8 BPL();  u8 BRK();  u8 BVC();
        u8 BVS();  u8 CLC();  u8 CLD();  u8 CLI();
        u8 CLV();  u8 CMP();  u8 CPX();  u8 CPY();
        u8 DEC();  u8 DEX();  u8 DEY();  u8 EOR();
        u8 INC();  u8 INX();  u8 INY();  u8 JMP();
        u8 JSR();  u8 LDA();  u8 LDX();  u8 LDY();
        u8 LSR();  u8 NOP();  u8 ORA();  u8 PHA();
        u8 PHP();  u8 PLA();  u8 PLP();  u8 ROL();
        u8 ROR();  u8 RTI();  u8 RTS();  u8 SBC();
        u8 SEC();  u8 SED();  u8 SEI();  u8 STA();
        u8 STX();  u8 STY();  u8 TAX();  u8 TAY();
        u8 TSX();  u8 TXA();  u8 TXS();  u8 TYA();

        /**
         * Illegal opcode
        */
        u8 XXX();

        u8 read(u16 a) const;
        void write(u16 a, u8 d) const;

        u8 getFlag(FLAGS6502 f) const;
        void setFlag(FLAGS6502 f, bool v);

        u8 fetch();

    private:
        Bus* bus_ = nullptr;

        u8 fetched_ = 0x00;
        u16 temp_ = 0x0000;
        u16 addrAbs_ = 0x0000;
        u16 addrRel_ = 0x0000;
        u8 opcode_ = 0x00;
        u8 cycles_ = 0;

        struct Instruction
        {
            std::string name;
            u8(Cpu6502::*operation)(void) = nullptr;
            u8(Cpu6502::*addrmode)(void) = nullptr;
            u8 cycles = 0;
        };

        std::vector<Instruction> lookup_;
    };
}

#endif