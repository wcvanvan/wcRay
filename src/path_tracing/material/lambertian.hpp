#ifndef RAYTRACING_LAMBERTIAN_HPP
#define RAYTRACING_LAMBERTIAN_HPP

#include <utility>

#include "material.hpp"
#include "core/utils.hpp"
#include "../texture/texture.hpp"
#include "core/onb.hpp"

class Lambertian : public Material {
public:
    std::shared_ptr<texture> albedo;

    explicit Lambertian(const Color &c) : albedo(std::make_shared<solid_color>(c)) {}

    explicit Lambertian(std::shared_ptr<texture> texture) : albedo(std::move(texture)) {}


    [[nodiscard]] bool scatter(
            const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
    ) const override;

    [[nodiscard]] double scattering_pdf(
            const Ray &r_in, const HitRecord &rec, const Ray &scattered
    ) const override;
};

bool Lambertian::scatter(
        const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
) const {
    scatter_record.attenuation = albedo->value(hit_record.u, hit_record.v, hit_record.hit_point);
    scatter_record.is_specular = false;
    scatter_record.pdf_ptr = std::make_shared<CosinePDF>(hit_record.normal);
    return true;
}

double Lambertian::scattering_pdf(
        const Ray &r_in, const HitRecord &rec, const Ray &scattered
) const {
    auto cosine = rec.normal.dot(scattered.direction);
    return std::max(0.0, cosine / pi);
}


#endif //RAYTRACING_LAMBERTIAN_HPP
