#ifndef RAYTRACING_ALTERNATING_TEXTURE_HPP
#define RAYTRACING_ALTERNATING_TEXTURE_HPP

#include "texture.hpp"
#include <memory>

class alternating_texture : public texture {
public:
    std::shared_ptr<texture> t1, t2;

    [[nodiscard]] color value(double u, double v, const point3 &p) const override;

    alternating_texture(const color &_c1, const color &_c2) {
        t1 = std::make_shared<solid_color>(_c1);
        t2 = std::make_shared<solid_color>(_c2);
    }
};

color alternating_texture::value(double u, double v, const point3 &p) const {
    auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
    if (sines < 0)
        return t1->value(u, v, p);
    else
        return t2->value(u, v, p);
}

#endif //RAYTRACING_ALTERNATING_TEXTURE_HPP
