#ifndef SOFTWAREPATHTRACING_METAL_H
#define SOFTWAREPATHTRACING_METAL_H

#include "material.h"
#include "../core/vec.h"

WCRAY_NAMESPACE_BEGIN

    class Metal : public Material {
    public:
        Color albedo;
        double fuzz;

        explicit Metal(const Color &c, double _fuzz) : albedo(c), fuzz(_fuzz) {}

        bool scatter(
                const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
        ) const override;
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_METAL_H
