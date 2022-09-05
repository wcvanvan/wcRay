#ifndef SOFTWAREPATHTRACING_HIT_H
#define SOFTWAREPATHTRACING_HIT_H

#include "../core/vec.h"
#include "../material/material.h"
#include "aabb.h"
#include <memory>

WCRAY_NAMESPACE_BEGIN

    class HitRecord {
    public:
        Point3 hit_point{};
        Vec3 normal{};
        double t{0};
        double u{}, v{}; // coordinate on texture
        bool exterior_hit{true};
        std::shared_ptr<Material> material_ptr{};

        inline void set_face_normal(const Ray &r, const Vec3 &outward_normal) {
            bool front_face = dot(r.direction, outward_normal) < 0;
            normal = front_face ? outward_normal : outward_normal * (-1);
        }
    };

    class Hittable {
    public:
        virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const = 0;

        virtual std::shared_ptr<AABB> bounding_box(double time0, double time1, bool &bounded) const = 0;

        [[nodiscard]] virtual double pdf_value(const Point3 &origin, const Vec3 &direction) const {
            return 1.0;
        }

        [[nodiscard]] virtual Vec3 random_direction(const Vec3 &origin) const {
            return {0, 0, 1};
        }
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_HIT_H
