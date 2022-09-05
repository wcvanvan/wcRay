#ifndef SOFTWAREPATHTRACING_DIFFUSE_LIGHT_H
#define SOFTWAREPATHTRACING_DIFFUSE_LIGHT_H

#include "material.h"
#include "../texture/texture.h"
#include "../geometries/hit.h"
#include <memory>
#include <utility>

WCRAY_NAMESPACE_BEGIN

    class DiffuseLight : public Material {
    public:
        std::shared_ptr<texture> texture_ptr;

        explicit DiffuseLight(std::shared_ptr<texture> tex) : texture_ptr(std::move(tex)) {}

        bool scatter(
                const Ray &ray_in, const HitRecord &hit_record, ScatterRecord &scatter_record
        ) const override;

        Color emitted(const Ray &ray_in, const HitRecord &hit_record) override;
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_DIFFUSE_LIGHT_H
