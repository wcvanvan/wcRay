#ifndef RENDERER_TRIANGLE_HPP
#define RENDERER_TRIANGLE_HPP

#include "hit.hpp"
#include "aabb.hpp"
#include <limits>
#include <algorithm>

class triangle : public hittable {
public:
    point3 A, B, C;
    std::shared_ptr<material> material_ptr{};

    explicit triangle(const point3 &A_, const point3 &B_, const point3 &C_,
                      std::shared_ptr<material> _material_ptr) : A(A_), B(B_), C(C_),
                                                                 material_ptr(std::move(_material_ptr)) {};

    bool hit(const ray &r, double t_min, double t_max, hit_record &record) const override;

    std::shared_ptr<aabb> bounding_box(double time0, double time1, bool &bounded) const override;
};

bool triangle::hit(const ray &r, double t_min, double t_max, hit_record &record) const {
    bool hit_plane;
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
    record.set_face_normal(r, normal);
    record.material_ptr = material_ptr;
    record.exterior_hit = true;
    record.t = t;
    record.hit_point = hit_point;
    return true;
}

std::shared_ptr<aabb> triangle::bounding_box(double time0, double time1, bool &bounded) const {
    bounded = true;
    double x_min = std::min(std::min(A.x(), B.x()), C.x());
    double y_min = std::min(std::min(A.y(), B.y()), C.y());
    double z_min = std::min(std::min(A.z(), B.z()), C.z());
    double x_max = std::max(std::max(A.x(), B.x()), C.x());
    double y_max = std::max(std::max(A.y(), B.y()), C.y());
    double z_max = std::max(std::max(A.z(), B.z()), C.z());
    if (x_min == x_max) {
        x_min -= 0.0001;
        x_max += 0.0001;
    }
    if (y_min == y_max) {
        y_min -= 0.0001;
        y_max += 0.0001;
    }
    if (z_min == z_max) {
        z_min -= 0.0001;
        z_max += 0.0001;
    }
    return std::make_shared<aabb>(point3(x_min, y_min, z_min), point3(x_max, y_max, z_max));
}

#endif //RENDERER_TRIANGLE_HPP
