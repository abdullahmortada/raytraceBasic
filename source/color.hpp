#ifndef COLOR_H
#define COLOR_H

#include "vec3.hpp"
#include "rtweekend.hpp"
#include <iostream>

void write_color(std::ostream &out, color pixel_col, int samples_per_pixel)
{
    double r = pixel_col.e[0];
    double g = pixel_col.e[1];
    double b = pixel_col.e[2];

    double scale = 1.0 /samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);
    

    out << static_cast<int>(256 * clamp(r,0,0.999)) << " "
        << static_cast<int>(256 * clamp(g,0,0.999)) << " "
        << static_cast<int>(256 * clamp(b,0,0.999)) << "\n";
}

#endif