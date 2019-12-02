#pragma once

/**
 * Simple 2D Vector Structure
 */
struct Vector2D {
    int x;
    int y;
};


/**
 * Simple Color Structure
 * - Stores Values 0-255
 * - Default Value for Alpha is 255
 */
struct RGBA {
    RGBA(unsigned char _r, unsigned char _g, unsigned char _b):
        r(_r), g(_g), b(_b), a(255) {};
    RGBA(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a):
        r(_r), g(_g), b(_b), a(_a) {};
    
    unsigned char r, g, b, a;
};