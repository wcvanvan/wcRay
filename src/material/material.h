#ifndef SOFTWAREPATHTRACING_MATERIAL_H
#define SOFTWAREPATHTRACING_MATERIAL_H

#include "../core/ray.h"
#include "../pdf/pdf.h"
#include "../core/common.h"

WCRAY_NAMESPACE_BEGIN

class HitRecord;

class ScatterRecord {
public:
    Ray specular_ray;
    bool is_specular;
    Color attenuation;
    Color BRDF;
    std::shared_ptr<PDF> pdf_ptr;
};

class Material {
public:
    virtual Color emitted(const Ray &ray_in, const HitRecord &hit_record) {
        return {0, 0, 0};
    }

    virtual bool scatter(
            const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
    ) const {
        return false;
    }
};

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_MATERIAL_H
