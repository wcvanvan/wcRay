#ifndef RAYTRACING_LAMBERTIAN_HPP
#define RAYTRACING_LAMBERTIAN_HPP

#include <utility>

#include "material.hpp"
#include "../utils.hpp"
#include "../texture/texture.hpp"

class lambertian : public material {
public:
    std::shared_ptr<texture> albedo;

    explicit lambertian(const color &c) : albedo(std::make_shared<solid_color>(c)) {}

    explicit lambertian(std::shared_ptr<texture> texture) : albedo(std::move(texture)) {}


    bool scatter(
            const ray &r_in, const hit_record &record, color &_albedo, ray &scattered
    ) const override;
};

bool lambertian::scatter(const ray &r_in, const hit_record &record, color &_albedo, ray &scattered) const {
    _albedo = albedo->value(record.u, record.v, record.hit_point);
    vec3 scattered_direction = record.normal + random_in_unit_sphere();
    if (scattered_direction.near_zero()) {
        scattered_direction = record.normal;
    }
    scattered = {record.hit_point, scattered_direction, r_in.time};
    return true;
}


#endif //RAYTRACING_LAMBERTIAN_HPP
