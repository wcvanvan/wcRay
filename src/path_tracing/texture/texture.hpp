#ifndef RAYTRACING_TEXTURE_HPP
#define RAYTRACING_TEXTURE_HPP

#include "../vec3.hpp"

class texture {
public:
    [[nodiscard]] virtual color value(double u, double v, const point3 &p) const = 0;
};

class solid_color : public texture {
private:
    color color_value;
public:
    explicit solid_color(const color &c) : color_value(c) {}
    [[nodiscard]] color value(double u, double v, const point3 &p) const override;
};

color solid_color::value(double u, double v, const point3 &p) const {
    return color_value;
}

#endif //RAYTRACING_TEXTURE_HPP
