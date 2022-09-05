#include "translate.h"

WCRAY_NAMESPACE_BEGIN

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

    std::shared_ptr<AABB> translate::bounding_box(double time0, double time1, bool &bounded) const {
        auto origin_box = object->bounding_box(time0, time1, bounded);
        Point3 point0 = origin_box->point0 + offset;
        Point3 point1 = origin_box->point1 + offset;
        return std::make_shared<AABB>(point0, point1);
    }

WCRAY_NAMESPACE_END
