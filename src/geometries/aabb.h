#ifndef SOFTWAREPATHTRACING_AABB_H
#define SOFTWAREPATHTRACING_AABB_H

#include "../core/vec.h"
#include "../core/ray.h"
#include <memory>

WCRAY_NAMESPACE_BEGIN

    class AABB {
    public:
        Point3 point0, point1; // point0 is the smaller point
        AABB() = default;

        AABB(const Point3 &_point0, const Point3 &_point1) : point0(_point0), point1(_point1) {}

        [[nodiscard]] bool hit(const Ray &r, double t_min, double t_max) const;

        static std::shared_ptr<AABB>
        surrounding_box(const std::shared_ptr<AABB> &box0, const std::shared_ptr<AABB> &box1);
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_AABB_H
