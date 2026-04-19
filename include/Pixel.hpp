#ifndef __PIXEL_HPP__
#define __PIXEL_HPP__

#include <cstdint>
#include <algorithm>
#include "CommonDefinitions.hpp"

namespace DBRT
{
    class PixelRGB
    {
        public:
            PixelRGB() : r(0), g(0), b(0) {}
            PixelRGB(uint8_t _c) : r(_c), g(_c), b(_c) {}
            PixelRGB(uint8_t _r, uint8_t _g, uint8_t _b) : r(_r), g(_g), b(_b) {}
            ~PixelRGB() = default;
            static Color3f RGBToFloat(const PixelRGB &pixel)
            {
                Color3f color;
                color[0] = std::max(0.0, std::min(1.0, pixel.r/255.0));
                color[1] = std::max(0.0, std::min(1.0, pixel.g/255.0));
                color[2] = std::max(0.0, std::min(1.0, pixel.b/255.0));
                return color;
            }
            static PixelRGB floatToRGB(const Color3f &color)
            {
                PixelRGB px;
                px.r = std::max(0, std::min(255, static_cast<int>(color[0]*255)));
                px.g = std::max(0, std::min(255, static_cast<int>(color[1]*255)));
                px.b = std::max(0, std::min(255, static_cast<int>(color[2]*255)));
                return px;
            }
            void setPixelRGB(uint8_t _r, uint8_t _g, uint8_t _b) { r = _r; g = _g; b = _b; }
            void setPixelRGB(Color3f &color)
            {
                PixelRGB px = floatToRGB(color);
                this->r = px.r;
                this->g = px.g;
                this->b = px.b;
            }

        public:
            uint8_t r, g, b;
    };
}

#endif