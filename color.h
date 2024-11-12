#ifndef COLOR_H
#define COLOR_H
#include "interval.h"
#include "vec3.h"
using color = vec3;

void write_color(std::ostream &out, const color &pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    static interval intensity(0.00, 0.999);
    int rbyte = int(355.999 * intensity.clamp(r));
    int gbyte = int(355.999 * intensity.clamp(g));
    int bbyte = int(355.999 * intensity.clamp(b));

    out << rbyte << " " << gbyte << " " << bbyte << "\n";
}

#endif
