#include "volumn.h"

WCRAY_NAMESPACE_BEGIN

    Volumn::Volumn(std::shared_ptr<Hittable> obj, double _density, std::shared_ptr<Isotropic> _isotropic) :
            boundary(std::move(obj)), density(_density), iso(std::move(_isotropic)) {}


    bool Volumn::hit(const Ray &r, double t_min, double t_max, HitRecord &record) const {
        HitRecord record1, record2;
        if (!boundary->hit(r, -infinity, infinity, record1)) {
            return false;
        }
        if (!boundary->hit(r, record1.t + 0.0001, infinity, record2)) {
            return false;
        }
        record1.t = std::max(record1.t, t_min);
        record2.t = std::min(record2.t, t_max);
        record1.t = std::max(record1.t, 0.0);
        if (record1.t > record2.t) {
            return false;
        }

        const double ray_length = sqrt(length_squared(r.direction));
        const double distance_inside_boundary = ray_length * (record2.t - record1.t);
        const double hit_distance = -(1.0 / density) * log(random_number());
        if (hit_distance > distance_inside_boundary) {
            return false;
        }
        record.t = record1.t + distance_inside_boundary / ray_length;
        record.hit_point = r.at(record.t);
        record.normal = Vec3(0, 0, 1); //arbitrary, no use
        record.material_ptr = iso;
        return true;
    }

    std::shared_ptr<AABB> Volumn::bounding_box(double time0, double time1, bool &bounded) const {
        return boundary->bounding_box(time0, time1, bounded);
    }

WCRAY_NAMESPACE_END
