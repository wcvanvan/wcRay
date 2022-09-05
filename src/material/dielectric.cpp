#include "dielectric.h"

WCRAY_NAMESPACE_BEGIN

    bool Dielectric::scatter(
            const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
    ) const {
        double refraction_ratio;
        Vec3 counter_normal;
        if (hit_record.exterior_hit) {
            refraction_ratio = 1 / refraction_idx;
            counter_normal = hit_record.normal;
        } else {
            refraction_ratio = refraction_idx;
            counter_normal = (-1) * hit_record.normal;
        }
        Vec3 unit_direction = normalize(ray_in.direction);
        double cos_theta = fmin(dot(unit_direction, (-1) * counter_normal), 1.0);
        double sin_theta = sqrt(1 - pow(cos_theta, 2));
        bool cannot_refract = (sin_theta * refraction_ratio) > 1;
        cannot_refract = cannot_refract || reflectance(cos_theta, refraction_ratio) > random_number();
        Vec3 scattered_direction;
        if (cannot_refract) {
            scattered_direction = reflect(unit_direction, counter_normal);
        } else {
            scattered_direction = refract(unit_direction, counter_normal, refraction_ratio);
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


WCRAY_NAMESPACE_END
