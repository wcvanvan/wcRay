#ifndef SOFTWAREPATHTRACING_MOVING_SPHERE_H
#define SOFTWAREPATHTRACING_MOVING_SPHERE_H

#include "hit.h"
#include "aabb.h"
#include "../material/material.h"
#include <utility>

WCRAY_NAMESPACE_BEGIN

    class MovingSphere : public Hittable {
    public:
        Point3 center_start, center_end;
        double radius;
        double time_start, time_end;
        std::shared_ptr<Material> material_ptr;

        explicit MovingSphere(const Point3& p0, const Point3& p1, double _radius, std::shared_ptr<Material> _material_ptr,
                               double _time_start, double _time_end);

        bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const override;

        [[nodiscard]] Point3 get_center(double time) const;

        std::shared_ptr<AABB> bounding_box(double time0, double time1, bool &bounded) const override;
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_MOVING_SPHERE_H
