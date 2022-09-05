#ifndef SOFTWAREPATHTRACING_ISOTROPIC_H
#define SOFTWAREPATHTRACING_ISOTROPIC_H

#include "material.h"
#include "../texture/texture.h"
#include "../geometries/hit.h"

WCRAY_NAMESPACE_BEGIN

    class Isotropic : public Material {
    public:
        std::shared_ptr<texture> albedo;

        explicit Isotropic(std::shared_ptr<texture> tex);

        bool scatter(
                const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
        ) const override;
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_ISOTROPIC_H
