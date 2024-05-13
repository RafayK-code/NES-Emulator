#include "Util.h"

namespace nes
{
    std::string hex(u32 n, u8 d)
    {
        std::string s(d, '0');
        for (int i = d - 1; i >= 0; i--, n >>= 4)
            s[i] = "0123456789ABCDEF"[n & 0xF];

        return s;
    }
}