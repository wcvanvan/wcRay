#ifndef RENDERER_TRIANGLE_HPP
#define RENDERER_TRIANGLE_HPP

#include "hittable.hpp"
#include <limits>

class triangle : public hittable {
public:
    point3 A, B, C;
    std::shared_ptr<material> material_ptr{};

    explicit triangle(const point3 &A_, const point3 &B_, const point3 &C_,
                      std::shared_ptr<material> _material_ptr) : A(A_), B(B_), C(C_),
                                                                 material_ptr(std::move(_material_ptr)) {};

    bool hit(const ray &r, double t_min, double t_max, hit_record &record) const override;
};

bool triangle::hit(const ray &r, double t_min, double t_max, hit_record &record) const {
    bool hit_plane = false;
    // plane expression: Ax + By + Cz = D
    vec3 normal = (C - A).cross(B - A);
    hit_plane = r.direction.dot(normal) != 0;
    if (!hit_plane) {
        return false;
    }
    double D = normal.dot(A);
    double t = (D - normal.dot(r.origin)) / (normal.dot(r.direction));
    if (t < t_min || t > t_max) {
        return false;
    }
    point3 hit_point = r.at(t);
    vec3 v1 = (B - A).cross(hit_point - A);
    vec3 v2 = (C - B).cross(hit_point - B);
    vec3 v3 = (A - C).cross(hit_point - C);
    bool inside_triangle = (v1.dot(v2) > 0) && (v2.dot(v3) > 0);
    if (!inside_triangle) {
        return false;
    }
    record.normal = normal;
    record.material_ptr = material_ptr;
    record.exterior_hit = true;
    record.t = t;
    record.hit_point = hit_point;
    return true;
}

#endif //RENDERER_TRIANGLE_HPP
