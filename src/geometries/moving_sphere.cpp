#ifndef RAYTRACING_MOVING_SPHERE_HPP
#define RAYTRACING_MOVING_SPHERE_HPP

#include "moving_sphere.h"

WCRAY_NAMESPACE_BEGIN

    MovingSphere::MovingSphere(const Point3 &p0, const Point3 &p1, double _radius,
                                 std::shared_ptr<Material> _material_ptr,
                                 double _time_start, double _time_end) :
            radius(_radius),
            material_ptr(std::move(
                    _material_ptr)), center_start(p0), center_end(p1), time_start{_time_start}, time_end(_time_end) {}


    [[nodiscard]] Point3 MovingSphere::get_center(double time) const {
        return center_start + (time - time_start) / (time_start - time_end) * (center_end - center_start);
    }


    bool MovingSphere::hit(const Ray &r, double t_min, double t_max, HitRecord &record) const {
        Vec3 oc = r.origin - get_center(r.time);
        double a = dot(r.direction, r.direction);
        double b = 2 * dot(r.direction, oc);
        double c = dot(oc, oc) - pow(radius, 2);
        double delta = pow(b, 2) - 4 * a * c;
        if (delta < 0) {
            return false;
        }
        double root = (-b - sqrt(delta)) / (2 * a);
        if (root < t_min || root > t_max) {
            root = (-b + sqrt(delta)) / (2 * a);
            if (root < t_min || root > t_max) {
                return false;
            }
        }
        record.t = root;
        record.hit_point = r.at(root);
        record.normal = normalize(record.hit_point - get_center(r.time));
        record.material_ptr = material_ptr;
        if (dot(record.normal, r.direction) < 0) {
            record.exterior_hit = true;
        } else {
            record.exterior_hit = false;
        }
        return true;
    }

    std::shared_ptr<AABB> MovingSphere::bounding_box(double time0, double time1, bool &bounded) const {
        bounded = true;
        auto box0 = std::make_shared<AABB>(
                get_center(time0) - radius,
                get_center(time0) + radius
        );
        auto box1 = std::make_shared<AABB>(
                get_center(time1) - radius,
                get_center(time1) + radius
        );
        return AABB::surrounding_box(box0, box1);
    }

WCRAY_NAMESPACE_END

#endif // RAYTRACING_MOVING_SPHERE_HPP

