#pragma once
#include <allegro5/allegro_primitives.h>
#include <array>
#include "datastructures.h"

struct ColorRGB {
    unsigned char r, g, b;
    ColorRGB() : r(0), g(0), b(0) {}
    ColorRGB(unsigned char r_, unsigned char g_, unsigned char b_) : r(r_), g(g_), b(b_) {}
};

enum class Color : unsigned char {
    HP,
    ARMOR,
    SHIELD,
    TORBARMOR,
    LUCIOSHIELD,
    
    ALLY,
    ENEMY,
    SPAWNROOM,
    CP,

    WHITE,
    BLACK,

    COLOR_MAX
};

class ColorPalette {
public:
    static ALLEGRO_COLOR get (Color color) {
        unsigned char colorindex = static_cast<unsigned char>(color);
        if (colorindex < static_cast<unsigned char>(Color::COLOR_MAX))
        {
            return al_map_rgb(colorlist.at(colorindex).r,
                              colorlist.at(colorindex).g,
                              colorlist.at(colorindex).b );
        }
        else
        {
            fprintf(stderr, "Prefixed color index is not in range! Received index: %d\n", colorindex);
            throw -1;
        }
    };

    static ALLEGRO_COLOR get (Color color, unsigned char alpha) {
        unsigned char colorindex = static_cast<unsigned char>(color);
        if (colorindex < static_cast<unsigned char>(Color::COLOR_MAX))
        {
            return al_map_rgba(colorlist.at(colorindex).r,
                               colorlist.at(colorindex).g,
                               colorlist.at(colorindex).b,
                               alpha);
        }
        else
        {
            fprintf(stderr, "Prefixed color index is not in range!");
            throw - 1;
        }
    };

    static ALLEGRO_COLOR premul(Color color, unsigned char alpha) {
        unsigned char colorindex = static_cast<unsigned char>(color);
        if (colorindex < static_cast<unsigned char>(Color::COLOR_MAX))
        {
            return al_premul_rgba(colorlist.at(colorindex).r,
                                  colorlist.at(colorindex).g,
                                  colorlist.at(colorindex).b,
                                  alpha);
        }
        else
        {
            fprintf(stderr, "Prefixed color index is not in range!");
            throw - 1;
        }
    };

private:
    const static std::array<ColorRGB, static_cast<unsigned char>(Color::COLOR_MAX)> colorlist;
};