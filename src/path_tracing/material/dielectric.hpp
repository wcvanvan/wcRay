#ifndef RAYTRACING_DIELECTRIC_HPP
#define RAYTRACING_DIELECTRIC_HPP

#include "material.hpp"
#include "core/vec3.hpp"
#include "core/ray.hpp"
#include "../geometries/hit.hpp"
#include "core/utils.hpp"

class Dielectric : public Material {
public:
    double refraction_idx{};

    explicit Dielectric(double _refraction_idx) : refraction_idx(_refraction_idx) {}

    bool scatter(
            const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
    ) const override;

    static double reflectance(double cosine, double ref_idx);
};

bool Dielectric::scatter(
        const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
) const {
    double refraction_ratio;
    vec3 counter_normal;
    if (hit_record.exterior_hit) {
        refraction_ratio = 1 / refraction_idx;
        counter_normal = hit_record.normal;
    } else {
        refraction_ratio = refraction_idx;
        counter_normal = (-1) * hit_record.normal;
    }
    vec3 unit_direction = ray_in.direction.unit_vector();
    double cos_theta = fmin(unit_direction.dot((-1) * counter_normal), 1.0);
    double sin_theta = sqrt(1 - pow(cos_theta, 2));
    bool cannot_refract = (sin_theta * refraction_ratio) > 1;
    cannot_refract = cannot_refract || reflectance(cos_theta, refraction_ratio) > random_number();
    vec3 scattered_direction;
    if (cannot_refract) {
        scattered_direction = vec3::reflect(unit_direction, counter_normal);
    } else {
        scattered_direction = vec3::refract(unit_direction, counter_normal, refraction_ratio);
    }
    scatter_record.is_specular = true;
    scatter_record.pdf_ptr = nullptr;
    scatter_record.attenuation = {1.0, 1.0, 1.0};
    scatter_record.specular_ray = Ray{hit_record.hit_point, scattered_direction, ray_in.time};
    return true;
}

double Dielectric::reflectance(double cosine, double ref_idx) {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}


#endif //RAYTRACING_DIELECTRIC_HPP
