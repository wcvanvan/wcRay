#ifndef RAYTRACING_ROTATE_HPP
#define RAYTRACING_ROTATE_HPP

#include <memory>
#include <utility>
#include "core/vec3.hpp"
#include "hit.hpp"

class rotate_y : public Hittable {
public:
    std::shared_ptr<Hittable> object;
    double sin_theta;
    double cos_theta;

    rotate_y(std::shared_ptr<Hittable> _object, double angle) : object(std::move(_object)) {
        double radian = angle * 3.1415926535897932385 / 180.0;
        sin_theta = sin(radian);
        cos_theta = cos(radian);
    }

    bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const override;

    std::shared_ptr<aabb> bounding_box(double time0, double time1, bool &bounded) const override;
};

bool rotate_y::hit(const Ray &r, double t_min, double t_max, HitRecord &record) const {
    point3 origin = r.origin;
    vec3 direction = r.direction;
    origin[0] = cos_theta * r.origin.value[0] - sin_theta * r.origin.value[2];
    origin[2] = sin_theta * r.origin.value[0] + cos_theta * r.origin.value[2];
    direction[0] = cos_theta * r.direction.value[0] - sin_theta * r.direction.value[2];
    direction[2] = sin_theta * r.direction.value[0] + cos_theta * r.direction.value[2];
    Ray r_rotated(origin, direction, r.time);
    if (!object->hit(r_rotated, t_min, t_max, record)) {
        return false;
    }
    point3 hit_p = record.hit_point;
    vec3 normal = record.normal;
    hit_p.value[0] = cos_theta * record.hit_point[0] + sin_theta * record.hit_point[2];
    hit_p.value[2] = -sin_theta * record.hit_point[0] + cos_theta * record.hit_point[2];
    normal[0] = cos_theta * record.normal[0] + sin_theta * record.normal[2];
    normal[2] = -sin_theta * record.normal[0] + cos_theta * record.normal[2];
    record.hit_point = hit_p;
    record.set_face_normal(r, normal);
    return true;
}

std::shared_ptr<aabb> rotate_y::bounding_box(double time0, double time1, bool &bounded) const {
    auto origin_box = object->bounding_box(time0, time1, bounded);
    if (!bounded) {
        std::cerr << "no bounding box" << std::endl;
        return {};
    }
    point3 point0(infinity, origin_box->point0.y(), infinity), point1(-infinity, origin_box->point1.y(), -infinity);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            auto x = i * origin_box->point0.x() + (1 - i) * origin_box->point1.x();
            auto z = j * origin_box->point0.z() + (1 - j) * origin_box->point1.z();
            auto x_rotate = cos_theta * x + sin_theta * z;
            auto z_rotate = -sin_theta * x + cos_theta * z;
            point0.value[0] = std::min(point0.x(), x_rotate);
            point1.value[0] = std::max(point1.x(), x_rotate);
            point0.value[2] = std::min(point0.z(), z_rotate);
            point1.value[2] = std::max(point1.z(), z_rotate);
        }
    }
    return std::make_shared<aabb>(point0, point1);
}

#endif //RAYTRACING_ROTATE_HPP
