#ifndef SOFTWAREPATHTRACING_DIELECTRIC_H
#define SOFTWAREPATHTRACING_DIELECTRIC_H

#include "material.h"
#include "../texture/texture.h"
#include "../geometries/hit.h"

WCRAY_NAMESPACE_BEGIN

    class Dielectric : public Material {
    public:
        double refraction_idx{};

        explicit Dielectric(double _refraction_idx) : refraction_idx(_refraction_idx) {}

        bool scatter(
                const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
        ) const override;

        static double reflectance(double cosine, double ref_idx);
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_DIELECTRIC_H
