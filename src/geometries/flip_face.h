#ifndef SOFTWAREPATHTRACING_FLIP_FACE_H
#define SOFTWAREPATHTRACING_FLIP_FACE_H

#include "../core/ray.h"
#include "../geometries/hit.h"
#include <memory>

using std::shared_ptr;

WCRAY_NAMESPACE_BEGIN

    class FlipFace : public Hittable {
    public:
        explicit FlipFace(shared_ptr<Hittable> p);

        bool hit(
                const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

        std::shared_ptr<AABB> bounding_box(double time0, double time1, bool &bounded) const override;

    public:
        shared_ptr<Hittable> ptr{};
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_FLIP_FACE_H
