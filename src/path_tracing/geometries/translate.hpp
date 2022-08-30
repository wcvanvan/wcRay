#ifndef RAYTRACING_TRANSLATE_HPP
#define RAYTRACING_TRANSLATE_HPP

#include <memory>
#include <utility>
#include "core/vec3.hpp"
#include "hit.hpp"

class translate : public Hittable {
public:
    vec3 offset;
    std::shared_ptr<Hittable> object;

    translate(std::shared_ptr<Hittable> _object, const vec3 &displacement) : object(std::move(_object)),
                                                                             offset(displacement) {}

    bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const override;

    std::shared_ptr<aabb> bounding_box(double time0, double time1, bool &bounded) const override;

};

bool translate::hit(const Ray &r, double t_min, double t_max, HitRecord &record) const {
    Ray r_moved(r.origin - offset, r.direction, r.time);
    bool hit = object->hit(r_moved, t_min, t_max, record);
    if (!hit) {
        return false;
    }
    record.hit_point += offset;
    record.set_face_normal(r_moved, record.normal);
    return true;
}

std::shared_ptr<aabb> translate::bounding_box(double time0, double time1, bool &bounded) const {
    auto origin_box = object->bounding_box(time0, time1, bounded);
    point3 point0 = origin_box->point0 + offset;
    point3 point1 = origin_box->point1 + offset;
    return std::make_shared<aabb>(point0, point1);
}

#endif //RAYTRACING_TRANSLATE_HPP
