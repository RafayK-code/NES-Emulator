#include "Bus.h"

namespace nes
{
    Bus::Bus()
    {
        for (auto& i : ram)
            i = 0x00;

        cpu.connectBus(this);
    }

    Bus::~Bus()
    {
    }

    u8 Bus::read(u16 addr, bool readOnly) const
    {
        if (addr >= 0x0000 && addr <= 0xFFFF)
            return ram[addr];

        return 0x00;
    }

    void Bus::write(u16 addr, u8 data)
    {
        if (addr >= 0x0000 && addr <= 0xFFFF)
            ram[addr] = data;
    }
}