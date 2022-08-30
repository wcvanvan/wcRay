#ifndef RAYTRACING_MOVING_SPHERE_HPP
#define RAYTRACING_MOVING_SPHERE_HPP

#include <utility>

#include "hit.hpp"
#include "aabb.hpp"
#include "../material/material.hpp"

class moving_sphere : public Hittable {
public:
    point3 center_start, center_end;
    double radius;
    double time_start, time_end;
    std::shared_ptr<Material> material_ptr;

    explicit moving_sphere(point3 p0, point3 p1, double _radius, std::shared_ptr<Material> _material_ptr,
                           double _time_start, double _time_end) :
            radius(_radius),
            material_ptr(std::move(
                    _material_ptr)), center_start(p0), center_end(p1), time_start{_time_start}, time_end(_time_end) {}

    bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const override;

    [[nodiscard]] point3 get_center(double time) const {
        return center_start + (time - time_start) / (time_start - time_end) * (center_end - center_start);
    }

    std::shared_ptr<aabb> bounding_box(double time0, double time1, bool &bounded) const override;
};

bool moving_sphere::hit(const Ray &r, double t_min, double t_max, HitRecord &record) const {
    vec3 oc = r.origin - get_center(r.time);
    double a = r.direction.dot(r.direction);
    double b = 2 * r.direction.dot(oc);
    double c = oc.dot(oc) - pow(radius, 2);
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
    record.normal = (record.hit_point - get_center(r.time)).unit_vector();
    record.material_ptr = material_ptr;
    if (record.normal.dot(r.direction) < 0) {
        record.exterior_hit = true;
    } else {
        record.exterior_hit = false;
    }
    return true;
}

std::shared_ptr<aabb> moving_sphere::bounding_box(double time0, double time1, bool &bounded) const {
    bounded = true;
    auto box0 = std::make_shared<aabb>(
            get_center(time0) - radius,
            get_center(time0) + radius
    );
    auto box1 = std::make_shared<aabb>(
            get_center(time1) - radius,
            get_center(time1) + radius
    );
    return aabb::surrounding_box(std::move(box0), std::move(box1));
}


#endif // RAYTRACING_MOVING_SPHERE_HPP

