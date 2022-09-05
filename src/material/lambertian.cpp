#include "lambertian.h"
#include <utility>

WCRAY_NAMESPACE_BEGIN

    Lambertian::Lambertian(const Color &c) : albedo(std::make_shared<solid_color>(c)) {}

    Lambertian::Lambertian(std::shared_ptr<texture> texture) : albedo(std::move(texture)) {}


    bool Lambertian::scatter(
            const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
    ) const {
        scatter_record.attenuation = albedo->value(hit_record.u, hit_record.v, hit_record.hit_point);
        scatter_record.BRDF = scatter_record.attenuation / PI;
        scatter_record.is_specular = false;
        scatter_record.pdf_ptr = std::make_shared<CosinePDF>(hit_record.normal);
        return true;
    }

WCRAY_NAMESPACE_END
