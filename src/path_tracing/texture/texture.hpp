#ifndef RAYTRACING_TEXTURE_HPP
#define RAYTRACING_TEXTURE_HPP

#include "core/vec3.hpp"

class texture {
public:
    [[nodiscard]] virtual Color value(double u, double v, const point3 &p) const = 0;
};

class solid_color : public texture {
private:
    Color color_value;
public:
    explicit solid_color(const Color &c) : color_value(c) {}
    [[nodiscard]] Color value(double u, double v, const point3 &p) const override;
};

Color solid_color::value(double u, double v, const point3 &p) const {
    return color_value;
}

#endif //RAYTRACING_TEXTURE_HPP
