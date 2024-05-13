#include "CpuDemo.h"

namespace nes
{
    namespace demo
    {
        CpuDemo::CpuDemo()
            : window_(nullptr)
        {
            font_.loadFromFile("assets/vcr.ttf");
        }

        void CpuDemo::init(std::stringstream& bytes)
        {
            //std::stringstream ss;
            //ss << "A2 0A 8E 00 00 A2 03 8E 01 00 AC 00 00 A9 00 18 6D 01 00 88 D0 FA 8D 02 00 EA EA EA";
            u16 nOffset = 0x8000;
            while (!bytes.eof())
            {
                std::string b;
                bytes >> b;
                nes_.ram[nOffset++] = (u8)(std::stoul(b, nullptr, 16));
            }
            nes_.ram[0xFFFC] = 0x00;
            nes_.ram[0xFFFD] = 0x80;
            mapAsm_ = nes_.cpu.disassemble(0x0000, 0xFFFF);
            nes_.cpu.reset();
        }

        void CpuDemo::tick()
        {
            while (sf::Event e = window_->pollEvent())
            {
                if (e.is<sf::Event::Closed>())
                    window_->close();
                if (const sf::Event::KeyPressed* keyPressed = e.getIf<sf::Event::KeyPressed>())
                {
                    if (keyPressed->code == sf::Keyboard::Key::Escape)
                        window_->close();
                    if (keyPressed->code == sf::Keyboard::Key::Space)
                    {
                        do
                        {
                            nes_.cpu.clock();
                        } 
                        while (!nes_.cpu.complete());
                    }
                    if (keyPressed->code == sf::Keyboard::Key::R)
                        nes_.cpu.reset();
                    if (keyPressed->code == sf::Keyboard::Key::I)
                        nes_.cpu.irq();
                    if (keyPressed->code == sf::Keyboard::Key::N)
                        nes_.cpu.nmi();
                }
            }

            window_->clear(sf::Color::Blue);
            drawRam(4, 4, 0x0000, 16, 16);
            drawRam(4, 364, 0x8000, 16, 16);
            drawCpu(896, 4);
            drawCode(896, 144, 26);
            drawString(20, 740, "SPACE = Step Instruction    R = RESET    I = IRQ    N = NMI");
            window_->display();
        }

        void CpuDemo::drawString(float xpos, float ypos, std::string str, const sf::Color& col) const
        {
            sf::Text text(font_, str, 20);
            text.setPosition({ xpos, ypos });
            text.setFillColor(col);
            window_->draw(text);
        }

        void CpuDemo::drawRam(int x, int y, u16 nAddr, int nRows, int nCols) const
        {
            int nRamX = x;
            int nRamY = y;
            for (int row = 0; row < nRows; row++)
            {
                std::string sOffset = "$" + hex(nAddr, 4) + ": ";
                for (int col = 0; col < nCols; col++)
                {
                    sOffset += " " + hex(nes_.read(nAddr, true), 2);
                    nAddr++;
                }
                drawString(nRamX, nRamY, sOffset);
                nRamY += 20;
            }
        }

        void CpuDemo::drawCpu(int x, int y) const
        {
            std::string status = "STATUS: ";
            drawString(x, y, "STATUS:");
            drawString(x + 128, y, "N", nes_.cpu.reg.status & Cpu6502::N ? sf::Color::Green : sf::Color::Red);
            drawString(x + 160, y, "V", nes_.cpu.reg.status & Cpu6502::V ? sf::Color::Green : sf::Color::Red);
            drawString(x + 192, y, "-", nes_.cpu.reg.status & Cpu6502::U ? sf::Color::Green : sf::Color::Red);
            drawString(x + 224, y, "B", nes_.cpu.reg.status & Cpu6502::B ? sf::Color::Green : sf::Color::Red);
            drawString(x + 256, y, "D", nes_.cpu.reg.status & Cpu6502::D ? sf::Color::Green : sf::Color::Red);
            drawString(x + 288, y, "I", nes_.cpu.reg.status & Cpu6502::I ? sf::Color::Green : sf::Color::Red);
            drawString(x + 320, y, "Z", nes_.cpu.reg.status & Cpu6502::Z ? sf::Color::Green : sf::Color::Red);
            drawString(x + 356, y, "C", nes_.cpu.reg.status & Cpu6502::C ? sf::Color::Green : sf::Color::Red);
            drawString(x, y + 20, "PC: $" + hex(nes_.cpu.reg.pc, 4));
            drawString(x, y + 40, "A: $" + hex(nes_.cpu.reg.a, 2) + "  [" + std::to_string(nes_.cpu.reg.a) + "]");
            drawString(x, y + 60, "X: $" + hex(nes_.cpu.reg.x, 2) + "  [" + std::to_string(nes_.cpu.reg.x) + "]");
            drawString(x, y + 80, "Y: $" + hex(nes_.cpu.reg.y, 2) + "  [" + std::to_string(nes_.cpu.reg.y) + "]");
            drawString(x, y + 100, "Stack P: $" + hex(nes_.cpu.reg.sp, 4));
        }

        void CpuDemo::drawCode(int x, int y, int nLines) const
        {
            auto itA = mapAsm_.find(nes_.cpu.reg.pc);
            int nLineY = (nLines >> 1) * 20 + y;
            if (itA != mapAsm_.end())
            {
                drawString(x, nLineY, itA->second, sf::Color::Cyan);
                while (nLineY < (nLines * 20) + y)
                {
                    nLineY += 20;
                    if (++itA != mapAsm_.end())
                        drawString(x, nLineY, itA->second);
                }
            }
            itA = mapAsm_.find(nes_.cpu.reg.pc);
            nLineY = (nLines >> 1) * 20 + y;
            if (itA != mapAsm_.end())
            {
                while (nLineY > y)
                {
                    nLineY -= 20;
                    if (--itA != mapAsm_.end())
                        drawString(x, nLineY, itA->second);
                }
            }
        }

        void runCpuDemo()
        {
            sf::RenderWindow window(sf::VideoMode({ 1360, 960 }), "CPU Demo");

            CpuDemo* cpuDemo = new CpuDemo();
            cpuDemo->assignWindow(&window);

            std::stringstream ss;
            ss << "A2 0A 8E 00 00 A2 03 8E 01 00 AC 00 00 A9 00 18 6D 01 00 88 D0 FA 8D 02 00 EA EA EA";
            cpuDemo->init(ss);

            while (window.isOpen())
            {
                cpuDemo->tick();
            }

            delete cpuDemo;
        }
    }
}