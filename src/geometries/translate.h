#ifndef SOFTWAREPATHTRACING_TRANSLATE_H
#define SOFTWAREPATHTRACING_TRANSLATE_H

#include "../core/vec.h"
#include "hit.h"
#include <memory>

WCRAY_NAMESPACE_BEGIN

    class translate : public Hittable {
    public:
        Vec3 offset;
        std::shared_ptr<Hittable> object;

        translate(std::shared_ptr<Hittable> _object, const Vec3 &displacement) : object(std::move(_object)),
                                                                                 offset(displacement) {}

        bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const override;

        std::shared_ptr<AABB> bounding_box(double time0, double time1, bool &bounded) const override;

    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_TRANSLATE_H
