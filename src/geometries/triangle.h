#ifndef SOFTWAREPATHTRACING_TRIANGLE_H
#define SOFTWAREPATHTRACING_TRIANGLE_H

#include "hit.h"
#include "aabb.h"

WCRAY_NAMESPACE_BEGIN

    class Triangle : public Hittable {
    public:
        Point3 A, B, C;
        std::shared_ptr<Material> material_ptr{};

        explicit Triangle(const Point3 &A_, const Point3 &B_, const Point3 &C_,
                          std::shared_ptr<Material> _material_ptr);

        bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const override;

        std::shared_ptr<AABB> bounding_box(double time0, double time1, bool &bounded) const override;
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_TRIANGLE_H
