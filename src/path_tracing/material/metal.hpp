#ifndef RAYTRACING_METAL_HPP
#define RAYTRACING_METAL_HPP
#include "material.hpp"
#include "../vec3.hpp"

class metal : public material {
public:
    color albedo;
    double fuzz;
    explicit metal(const color& c, double _fuzz): albedo(c), fuzz(_fuzz) {}
    bool scatter(const ray &r_in, const hit_record &record, color &_albedo, ray &scattered) const override;
};

bool metal::scatter(const ray &r_in, const hit_record &record, color &_albedo, ray &scattered) const {
    _albedo = albedo;
    vec3 unit_direction = r_in.direction.unit_vector();
    vec3 scattered_direction = vec3::reflect(unit_direction, record.normal) + random_in_unit_sphere() * fuzz;
    scattered = {record.hit_point, scattered_direction, r_in.time};
    return scattered.direction.dot(record.normal) > 0;
}


#endif //RAYTRACING_METAL_HPP
