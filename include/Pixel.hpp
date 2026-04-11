#ifndef __PIXEL_HPP__
#define __PIXEL_HPP__

#include <cstdint>

class PixelRGB
{
    public:
        PixelRGB() : r(0), g(0), b(0) {}
        PixelRGB(uint8_t _c) : r(_c), g(_c), b(_c) {}
        PixelRGB(uint8_t _r, uint8_t _g, uint8_t _b) : r(_r), g(_g), b(_b) {}
        ~PixelRGB() = default;
        void setPixelRGB(uint8_t _r, uint8_t _g, uint8_t _b) {r = _r; g = _g; b = _b; }

    public:
        uint8_t r, g, b;
};

#endif