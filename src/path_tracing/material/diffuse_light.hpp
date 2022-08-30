#ifndef RAYTRACING_DIFFUSE_LIGHT_HPP
#define RAYTRACING_DIFFUSE_LIGHT_HPP

#include <memory>
#include <utility>
#include "material.hpp"
#include "../texture/texture.hpp"

class DiffuseLight : public Material {
public:
    std::shared_ptr<texture> texture_ptr;

    explicit DiffuseLight(std::shared_ptr<texture> tex) : texture_ptr(std::move(tex)) {}

    bool scatter(
            const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
    ) const override {
        return false;
    }

    Color emitted(const Ray &ray_in, const HitRecord &hit_record) override {
        if (!hit_record.exterior_hit) {
            return {0, 0, 0};
        }
        return texture_ptr->value(hit_record.u, hit_record.v, hit_record.hit_point);
    }
};

#endif //RAYTRACING_DIFFUSE_LIGHT_HPP
