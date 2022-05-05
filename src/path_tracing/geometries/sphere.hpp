#ifndef RAYTRACING_SPHERE_HPP
#define RAYTRACING_SPHERE_HPP

#include "hit.hpp"
#include "aabb.hpp"
#include "../material/material.hpp"

class sphere : public hittable {
public:
    point3 center;
    double radius;
    std::shared_ptr<material> material_ptr;

    explicit sphere(const point3 &p, double _radius, std::shared_ptr<material> _material_ptr) : center(p),
                                                                                                 radius(_radius),
                                                                                                 material_ptr(std::move(
                                                                                                         _material_ptr)) {};

    bool hit(const ray &r, double t_min, double t_max, hit_record &record) const override;
    std::shared_ptr<aabb> bounding_box(double time0, double time1, bool &bounded) const override;
    static void get_sphere_uv(const point3 &p, double &u, double &v);
};

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &record) const {
    vec3 oc = r.origin - center;
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
    record.normal = (record.hit_point - center).unit_vector();
//    record.set_face_normal(r, (record.hit_point - center).unit_vector());
    record.material_ptr = material_ptr;
//    if (record.normal.dot(r.direction) < 0) {
//        record.exterior_hit = true;
//    } else {
//        record.exterior_hit = false;
//    }
    sphere::get_sphere_uv(record.normal, record.u, record.v);
    return true;
}

std::shared_ptr<aabb> sphere::bounding_box(double time0, double time1, bool &bounded) const {
    bounded = true;
    return std::make_shared<aabb>(aabb(center - point3(radius, radius, radius), center + point3(radius, radius, radius)));
}

void sphere::get_sphere_uv(const point3 &p, double &u, double &v) {
    double theta = acos(-p.y());
    double phi = atan2(-p.z(), p.x()) + pi;
    u = phi / (2*pi);
    v = theta / pi;
}

#endif //RAYTRACING_SPHERE_HPP
