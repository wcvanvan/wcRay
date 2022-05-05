#ifndef RAYTRACING_RECTANGLE_HPP
#define RAYTRACING_RECTANGLE_HPP

#include <utility>

#include "hit.hpp"
#include "../material/material.hpp"

class xy_rect : public hittable {
public:
    double x0, x1, y0, y1, z;
    std::shared_ptr<material> material_ptr;

    xy_rect(double _x0, double _x1, double _y0, double _y1, double _z, std::shared_ptr<material> mat) : x0(_x0),
                                                                                                        x1(_x1),
                                                                                                        y0(_y0),
                                                                                                        y1(_y1), z(_z),
                                                                                                        material_ptr(
                                                                                                                std::move(
                                                                                                                        mat)) {}

    bool hit(const ray &r, double t_min, double t_max, hit_record &record) const override;

    std::shared_ptr<aabb> bounding_box(double time0, double time1, bool &bounded) const override;

};

bool xy_rect::hit(const ray &r, double t_min, double t_max, hit_record &record) const {
    record.t = (z - r.origin.z()) / r.direction.z();
    if (record.t < t_min || record.t > t_max) {
        return false;
    }
    record.hit_point = point3(r.at(record.t));
    if (record.hit_point.x() < x0 || record.hit_point.x() > x1 || record.hit_point.y() < y0 ||
        record.hit_point.y() > y1) {
        return false;
    }
    record.material_ptr = material_ptr;
    record.set_face_normal(r, vec3(0, 0, 1));
    record.exterior_hit = true;
    record.u = (record.hit_point.x() - x0) / (x1 - x0);
    record.v = (record.hit_point.y() - y0) / (y1 - y0);
    return true;
}

std::shared_ptr<aabb> xy_rect::bounding_box(double time0, double time1, bool &bounded) const {
    bounded = true;
    return std::make_shared<aabb>(point3(x0, y0, z - 0.0001), point3(x1, y1, z + 0.0001));
}



class xz_rect : public hittable {
public:
    double x0, x1, z0, z1, y;
    std::shared_ptr<material> material_ptr;

    xz_rect(double _x0, double _x1, double _z0, double _z1, double _y, std::shared_ptr<material> mat) : x0(_x0),
                                                                                                        x1(_x1),
                                                                                                        z0(_z0),
                                                                                                        z1(_z1), y(_y),
                                                                                                        material_ptr(
                                                                                                                std::move(
                                                                                                                        mat)) {}

    bool hit(const ray &r, double t_min, double t_max, hit_record &record) const override;

    std::shared_ptr<aabb> bounding_box(double time0, double time1, bool &bounded) const override;
};

bool xz_rect::hit(const ray &r, double t_min, double t_max, hit_record &record) const {
    record.t = (y - r.origin.y()) / r.direction.y();
    if (record.t < t_min || record.t > t_max) {
        return false;
    }
    record.hit_point = point3(r.at(record.t));
    if (record.hit_point.x() < x0 || record.hit_point.x() > x1 || record.hit_point.z() < z0 ||
        record.hit_point.z() > z1) {
        return false;
    }
    record.material_ptr = material_ptr;
    record.set_face_normal(r, vec3(0, 1, 0));
    record.exterior_hit = true;
    record.u = (record.hit_point.x() - x0) / (x1 - x0);
    record.v = (record.hit_point.z() - z0) / (z1 - z0);
    return true;
}

std::shared_ptr<aabb> xz_rect::bounding_box(double time0, double time1, bool &bounded) const {
    bounded = true;
    return std::make_shared<aabb>(point3(x0, y - 0.0001, z0), point3(x1, y + 0.0001, z1));
}

class yz_rect : public hittable {
public:
    double y0, y1, z0, z1, x;
    std::shared_ptr<material> material_ptr;

    yz_rect(double _y0, double _y1, double _z0, double _z1, double _x, std::shared_ptr<material> mat) : y0(_y0),
                                                                                                        y1(_y1),
                                                                                                        z0(_z0),
                                                                                                        z1(_z1), x(_x),
                                                                                                        material_ptr(
                                                                                                                std::move(
                                                                                                                        mat)) {}

    bool hit(const ray &r, double t_min, double t_max, hit_record &record) const override;

    std::shared_ptr<aabb> bounding_box(double time0, double time1, bool &bounded) const override;
};

bool yz_rect::hit(const ray &r, double t_min, double t_max, hit_record &record) const {
    record.t = (x - r.origin.x()) / r.direction.x();
    if (record.t < t_min || record.t > t_max) {
        return false;
    }
    record.hit_point = point3(r.at(record.t));
    if (record.hit_point.y() < y0 || record.hit_point.y() > y1 || record.hit_point.z() < z0 ||
        record.hit_point.z() > z1) {
        return false;
    }
    record.material_ptr = material_ptr;
    record.set_face_normal(r, vec3(1, 0, 0));
    record.exterior_hit = true;
    record.u = (record.hit_point.y() - y0) / (y1 - y0);
    record.v = (record.hit_point.z() - z0) / (z1 - z0);
    return true;
}

std::shared_ptr<aabb> yz_rect::bounding_box(double time0, double time1, bool &bounded) const {
    bounded = true;
    return std::make_shared<aabb>(point3(x - 0.0001, y0, z0), point3(x + 0.0001, y1, z1));
}

#endif //RAYTRACING_RECTANGLE_HPP
