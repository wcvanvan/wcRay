#include "triangle.h"
#include <limits>
#include <algorithm>

WCRAY_NAMESPACE_BEGIN


    Triangle::Triangle(const Point3 &A_, const Point3 &B_, const Point3 &C_,
                       std::shared_ptr<Material> _material_ptr) : A(A_), B(B_), C(C_),
                                                                  material_ptr(std::move(_material_ptr)) {};

    bool Triangle::hit(const Ray &r, double t_min, double t_max, HitRecord &record) const {
        bool hit_plane;
        // plane expression: Ax + By + Cz = D
        Vec3 normal = cross(C - A, B - A);
        hit_plane = dot(r.direction, normal) != 0;
        if (!hit_plane) {
            return false;
        }
        double D = dot(normal, A);
        double t = (D - dot(normal, r.origin)) / dot(normal, r.direction);
        if (t < t_min || t > t_max) {
            return false;
        }
        Point3 hit_point = r.at(t);
        Vec3 v1 = cross(B - A, hit_point - A);
        Vec3 v2 = cross(C - B, hit_point - B);
        Vec3 v3 = cross(A - C, hit_point - C);
        bool inside_triangle = (dot(v1, v2) > 0) && (dot(v2, v3) > 0);
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

    std::shared_ptr<AABB> Triangle::bounding_box(double time0, double time1, bool &bounded) const {
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
        return std::make_shared<AABB>(Point3(x_min, y_min, z_min), Point3(x_max, y_max, z_max));
    }

WCRAY_NAMESPACE_END
