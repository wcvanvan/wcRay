#ifndef RAYTRACING_ISOTROPIC_HPP
#define RAYTRACING_ISOTROPIC_HPP

#include <utility>

#include "material.hpp"
#include "core/utils.hpp"
#include "../texture/texture.hpp"

class Isotropic : public Material {
public:
    std::shared_ptr<texture> albedo;

    explicit Isotropic(std::shared_ptr<texture> tex) : albedo(std::move(tex)) {}

    bool scatter(
            const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
    ) const override;
};

bool Isotropic::scatter(
        const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
) const {
    scatter_record.is_specular = true;
    scatter_record.specular_ray = {ray_in.at(hit_record.t), random_in_unit_sphere(), ray_in.time};
    scatter_record.attenuation = albedo->value(hit_record.u, hit_record.v, hit_record.hit_point);
    return true;
}

#endif //RAYTRACING_ISOTROPIC_HPP
