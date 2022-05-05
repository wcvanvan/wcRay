#ifndef RAYTRACING_ISOTROPIC_HPP
#define RAYTRACING_ISOTROPIC_HPP

#include <utility>

#include "material.hpp"
#include "../utils.hpp"
#include "../texture/texture.hpp"

class isotropic : public material {
public:
    std::shared_ptr<texture> albedo;

    explicit isotropic(std::shared_ptr<texture> tex) : albedo(std::move(tex)) {}

    bool scatter(const ray &r_in, const hit_record &record, color &_albedo, ray &scattered) const override;
};

bool isotropic::scatter(const ray &r_in, const hit_record &record, color &_albedo, ray &scattered) const {
    scattered.direction = random_in_unit_sphere();
    scattered.origin = r_in.at(record.t);
    scattered.time = r_in.time;
    _albedo = albedo->value(record.u, record.v, record.hit_point);
    return true;
}

#endif //RAYTRACING_ISOTROPIC_HPP
