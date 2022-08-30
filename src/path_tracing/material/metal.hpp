#ifndef RAYTRACING_METAL_HPP
#define RAYTRACING_METAL_HPP

#include "material.hpp"
#include "core/vec3.hpp"

class Metal : public Material {
public:
    Color albedo;
    double fuzz;

    explicit Metal(const Color &c, double _fuzz) : albedo(c), fuzz(_fuzz) {}

    bool scatter(
            const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
    ) const override;
};

bool Metal::scatter(
        const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
) const {
    scatter_record.attenuation = albedo;
    scatter_record.is_specular = true;
    scatter_record.pdf_ptr = nullptr;
    vec3 unit_direction = ray_in.direction.unit_vector();
    vec3 scattered_direction = vec3::reflect(unit_direction, hit_record.normal) + random_in_unit_sphere() * fuzz;
    scatter_record.specular_ray = Ray(hit_record.hit_point, scattered_direction, ray_in.time);
    return true;
}


#endif //RAYTRACING_METAL_HPP
