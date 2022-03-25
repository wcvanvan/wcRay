#ifndef RAYTRACING_METAL_HPP
#define RAYTRACING_METAL_HPP
#include "material.hpp"
#include "../vec3.hpp"

class metal : public material {
public:
    color albedo;
    double fuzz;
    const Random *random{};
    explicit metal(const color c, double _fuzz, const Random &_random): albedo(c), fuzz(_fuzz), random(&_random) {}
    bool scatter(const ray &r_in, const hit_record &record, color &_albedo, ray &scattered) const override;
};

bool metal::scatter(const ray &r_in, const hit_record &record, color &_albedo, ray &scattered) const {
    _albedo = albedo;
    vec3 unit_direction = r_in.direction.unit_vector();
    vec3 scattered_direction = vec3::reflect(unit_direction, record.normal) + random->random_in_unit_sphere() * fuzz;
    scattered = {record.hit_point, scattered_direction};
    return scattered.direction.dot(record.normal) > 0;
}


#endif //RAYTRACING_METAL_HPP
