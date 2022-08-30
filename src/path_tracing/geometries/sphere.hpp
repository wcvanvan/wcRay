#ifndef RAYTRACING_SPHERE_HPP
#define RAYTRACING_SPHERE_HPP

#include <core/onb.hpp>
#include "hit.hpp"
#include "aabb.hpp"
#include "../material/material.hpp"

vec3 random_to_sphere(double radius, double distance_squared) {
    auto r1 = random_number();
    auto r2 = random_number();
    auto z = 1 + r2 * (sqrt(1 - radius * radius / distance_squared) - 1);

    auto phi = 2 * pi * r1;
    auto x = cos(phi) * sqrt(1 - z * z);
    auto y = sin(phi) * sqrt(1 - z * z);

    return {x, y, z};
}

class sphere : public Hittable {
public:
    point3 center;
    double radius;
    std::shared_ptr<Material> material_ptr;

    explicit sphere(const point3 &p, double _radius, std::shared_ptr<Material> _material_ptr) : center(p),
                                                                                                radius(_radius),
                                                                                                material_ptr(std::move(
                                                                                                        _material_ptr)) {};

    bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const override;

    std::shared_ptr<aabb> bounding_box(double time0, double time1, bool &bounded) const override;

    static void get_sphere_uv(const point3 &p, double &u, double &v);

    [[nodiscard]] double pdf_value(const point3 &origin, const vec3 &direction) const override;

    [[nodiscard]] vec3 random_direction(const vec3 &origin) const override;
};

bool sphere::hit(const Ray &r, double t_min, double t_max, HitRecord &record) const {
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
    record.set_face_normal(r, (record.hit_point - center).unit_vector());
    record.material_ptr = material_ptr;
    sphere::get_sphere_uv(record.normal, record.u, record.v);
    return true;
}

std::shared_ptr<aabb> sphere::bounding_box(double time0, double time1, bool &bounded) const {
    bounded = true;
    return std::make_shared<aabb>(
            aabb(center - point3(radius, radius, radius), center + point3(radius, radius, radius)));
}

void sphere::get_sphere_uv(const point3 &p, double &u, double &v) {
    double theta = acos(-p.y());
    double phi = atan2(-p.z(), p.x()) + pi;
    u = phi / (2 * pi);
    v = theta / pi;
}

double sphere::pdf_value(const point3 &origin, const vec3 &direction) const {
    HitRecord rec;
    if (!this->hit(Ray(origin, direction), 0.001, infinity, rec))
        return 0;

    auto cos_theta_max = sqrt(1 - radius * radius / (center - origin).length_squared());
    auto solid_angle = 2 * pi * (1 - cos_theta_max);

    return 1 / solid_angle;
}

vec3 sphere::random_direction(const vec3 &origin) const {
    vec3 direction = center - origin;
    auto distance_squared = direction.length_squared();
    ONB uvw;
    uvw.build_from_w(direction);
    return uvw.local(random_to_sphere(radius, distance_squared));
}

#endif //RAYTRACING_SPHERE_HPP
