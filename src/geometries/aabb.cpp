#ifndef RAYTRACING_AABB_HPP
#define RAYTRACING_AABB_HPP

#include "aabb.h"

WCRAY_NAMESPACE_BEGIN

    bool AABB::hit(const Ray &r, double t_min, double t_max) const {
        int dimension = 3;
        for (int dim = 0; dim < dimension; ++dim) {
            auto t0 = (point0.value[dim] - r.origin.value[dim]) / r.direction.value[dim];
            auto t1 = (point1.value[dim] - r.origin.value[dim]) / r.direction.value[dim];
            if (r.direction.value[dim] < 0.0f)
                std::swap(t0, t1);
            t_min = t0 > t_min ? t0 : t_min;
            t_max = t1 < t_max ? t1 : t_max;
            if (t_max <= t_min)
                return false;
        }
        return true;
    }

    std::shared_ptr<AABB>
    AABB::surrounding_box(const std::shared_ptr<AABB> &box0, const std::shared_ptr<AABB> &box1) {
        Point3 small(fmin(box0->point0.x(), box1->point0.x()),
                     fmin(box0->point0.y(), box1->point0.y()),
                     fmin(box0->point0.z(), box1->point0.z()));

        Point3 big(fmax(box0->point1.x(), box1->point1.x()),
                   fmax(box0->point1.y(), box1->point1.y()),
                   fmax(box0->point1.z(), box1->point1.z()));

        return std::make_shared<AABB>(small, big);
    }

WCRAY_NAMESPACE_END

#endif //RAYTRACING_AABB_HPP
