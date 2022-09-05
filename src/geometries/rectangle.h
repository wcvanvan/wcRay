#ifndef SOFTWAREPATHTRACING_RECTANGLE_H
#define SOFTWAREPATHTRACING_RECTANGLE_H

#include "hit.h"
#include "../material/material.h"

WCRAY_NAMESPACE_BEGIN

    class XYRect : public Hittable {
    public:
        double x0, x1, y0, y1, z;
        // (x0, y0) will be the closest corner, (x1, y1) will be the farthest corner
        std::shared_ptr<Material> material_ptr;

        XYRect(double _x0, double _x1, double _y0, double _y1, double _z, std::shared_ptr<Material> mat);

        bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const override;

        std::shared_ptr<AABB> bounding_box(double time0, double time1, bool &bounded) const override;

    };

    class XZRect : public Hittable {
    public:
        double x0, x1, z0, z1, y;
        std::shared_ptr<Material> material_ptr;

        XZRect(double _x0, double _x1, double _z0, double _z1, double _y, std::shared_ptr<Material> mat);

        bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const override;

        std::shared_ptr<AABB> bounding_box(double time0, double time1, bool &bounded) const override;

        [[nodiscard]] double pdf_value(const Point3 &origin, const Vec3 &direction) const override;

        [[nodiscard]] Vec3 random_direction(const Vec3 &origin) const override;
    };

    class YZRect : public Hittable {
    public:
        double y0, y1, z0, z1, x;
        std::shared_ptr<Material> material_ptr;

        YZRect(double _y0, double _y1, double _z0, double _z1, double _x, std::shared_ptr<Material> mat);

        bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const override;

        std::shared_ptr<AABB> bounding_box(double time0, double time1, bool &bounded) const override;
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_RECTANGLE_H
