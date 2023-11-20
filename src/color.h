#pragma once
#include <iostream>
#include <cstdint>

class Color
{
private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

public:
    Color();
    Color(uint8_t red, uint8_t green, uint8_t blue);
    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    uint8_t getBlue();
    uint8_t getRed();
    uint8_t getGreen();
    uint8_t getAlpha();

    friend std::ostream &operator<<(std::ostream &os, const Color &color);
    Color operator+(const Color &color);
    Color operator*(float factor) const;
    bool operator==(const Color &color);
    void print();
};
