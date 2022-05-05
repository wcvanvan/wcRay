#ifndef RAYTRACING_DIFFUSE_LIGHT_HPP
#define RAYTRACING_DIFFUSE_LIGHT_HPP

#include <memory>
#include <utility>
#include "material.hpp"
#include "../texture/texture.hpp"

class diffuse_light : public material {
public:
    std::shared_ptr<texture> texture_ptr;

    explicit diffuse_light(std::shared_ptr<texture> tex) : texture_ptr(std::move(tex)) {}
    bool scatter(const ray &r_in, const hit_record &record, color &albedo, ray &scattered) const override {
        return false;
    }
    color emit(double u, double v, const point3 &point) override {
        return texture_ptr->value(u, v, point);
    }
};

#endif //RAYTRACING_DIFFUSE_LIGHT_HPP
