#ifndef SOFTWAREPATHTRACING_SPHERE_H
#define SOFTWAREPATHTRACING_SPHERE_H

#include "../core/onb.h"
#include "hit.h"
#include "aabb.h"
#include "../material/material.h"

WCRAY_NAMESPACE_BEGIN

    class Sphere : public Hittable {
    public:
        Point3 center;
        double radius;
        std::shared_ptr<Material> material_ptr;

        explicit Sphere(const Point3 &p, double _radius, std::shared_ptr<Material> _material_ptr);

        bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const override;

        std::shared_ptr<AABB> bounding_box(double time0, double time1, bool &bounded) const override;

        static void get_sphere_uv(const Point3 &p, double &u, double &v);

        [[nodiscard]] double pdf_value(const Point3 &origin, const Vec3 &direction) const override;

        [[nodiscard]] Vec3 random_direction(const Vec3 &origin) const override;
    };

WCRAY_NAMESPACE_END
#endif //SOFTWAREPATHTRACING_SPHERE_H
