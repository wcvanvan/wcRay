#ifndef RAYTRACING_LAMBERTIAN_HPP
#define RAYTRACING_LAMBERTIAN_HPP
#include "material.hpp"
#include "../utils.hpp"

class lambertian : public material {
public:
    color albedo;
    const Random *random{};
    explicit lambertian(const color& c, const Random &_random): albedo(c), random(&_random) {}

    bool scatter(
            const ray& r_in, const hit_record& record, color& _albedo, ray& scattered
    ) const override;
};

bool lambertian::scatter(const ray &r_in, const hit_record &record, color &_albedo, ray &scattered) const {
    _albedo = albedo;
    vec3 scattered_direction = record.normal + random->random_in_unit_sphere();
    if (scattered_direction.near_zero()) {
        scattered_direction = record.normal;
    }
    scattered = {record.hit_point, scattered_direction};
    return true;
}


#endif //RAYTRACING_LAMBERTIAN_HPP
