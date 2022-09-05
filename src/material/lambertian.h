#ifndef SOFTWAREPATHTRACING_LAMBERTIAN_H
#define SOFTWAREPATHTRACING_LAMBERTIAN_H

#include "material.h"
#include "../texture/texture.h"
#include "../core/onb.h"
#include "../core/color.h"
#include "../geometries/hit.h"
#include "../pdf/cosine_pdf.h"
#include <memory>

WCRAY_NAMESPACE_BEGIN

    class Lambertian : public Material {
    public:
        std::shared_ptr<texture> albedo;

        explicit Lambertian(const Color &c);

        explicit Lambertian(std::shared_ptr<texture> texture);


        [[nodiscard]] bool scatter(
                const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
        ) const override;
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_LAMBERTIAN_H
