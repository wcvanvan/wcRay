#include "metal.h"
#include "../geometries/hit.h"

WCRAY_NAMESPACE_BEGIN

    bool Metal::scatter(
            const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
    ) const {
        scatter_record.attenuation = albedo;
        scatter_record.is_specular = true;
        scatter_record.pdf_ptr = nullptr;
        Vec3 unit_direction = normalize(ray_in.direction);
        Vec3 scattered_direction = reflect(unit_direction, hit_record.normal) + random_in_unit_sphere() * fuzz;
        scatter_record.specular_ray = Ray(hit_record.hit_point, scattered_direction, ray_in.time);
        return true;
    }

WCRAY_NAMESPACE_END
