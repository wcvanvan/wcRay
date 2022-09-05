#include "material.h"
#include "../texture/texture.h"
#include "diffuse_light.h"

WCRAY_NAMESPACE_BEGIN

    bool DiffuseLight::scatter(
            const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
    ) const {
        return false;
    }

    Color DiffuseLight::emitted(const Ray &ray_in, const HitRecord &hit_record) {
        if (!hit_record.exterior_hit) {
            return {0, 0, 0};
        }
        return texture_ptr->value(hit_record.u, hit_record.v, hit_record.hit_point);
    }

WCRAY_NAMESPACE_END
