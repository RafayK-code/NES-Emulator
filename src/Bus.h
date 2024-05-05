#pragma once
#ifndef _BUS_H
#define _BUS_H

#include <array>

#include "Cpu6502.h"

namespace nes
{
    class Bus
    {
    public:
        Bus();
        ~Bus();

        u8 read(u16 addr, bool readOnly = false) const;
        void write(u16 addr, u8 data);

    public:
        Cpu6502 cpu;
        std::array<u8, 64 * 1024> ram;   //fake ram for now
    };
}

#endif