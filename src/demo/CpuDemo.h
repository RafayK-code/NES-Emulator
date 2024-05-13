#pragma once
#ifndef _CPU_DEMO_H
#define _CPU_DEMO_H

#include <SFML/Graphics.hpp>

#include <map>
#include <sstream>

#include "Bus.h"

namespace nes
{
    namespace demo
    {
        class CpuDemo
        {
        public:
            CpuDemo();

            void init(std::stringstream& bytes);
            void tick();

            void assignWindow(sf::RenderWindow* window) { window_ = window; }

        private:
            void drawString(float xpos, float ypos, std::string str, const sf::Color& col = sf::Color::White) const;
            void drawRam(int x, int y, u16 nAddr, int nRows, int nCols) const;
            void drawCpu(int x, int y) const;
            void drawCode(int x, int y, int nLines) const;

        private:
            Bus nes_;
            std::map<u16, std::string> mapAsm_;

            sf::RenderWindow* window_;
            sf::Font font_;

        };

        void runCpuDemo();
    }
}

#endif