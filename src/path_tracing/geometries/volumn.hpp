#ifndef RAYTRACING_VOLUMN_HPP
#define RAYTRACING_VOLUMN_HPP

#include <utility>

#include "hit.hpp"
#include "../material/isotropic.hpp"

class volumn : public hittable {
public:
    std::shared_ptr<hittable> boundary;
    double density;
    std::shared_ptr<isotropic> iso;

    volumn(std::shared_ptr<hittable> obj, double _density, std::shared_ptr<isotropic> _isotropic) :
            boundary(std::move(obj)), density(_density), iso(std::move(_isotropic)) {}

    bool hit(const ray &r, double t_min, double t_max, hit_record &record) const override;

    std::shared_ptr<aabb> bounding_box(double time0, double time1, bool &bounded) const override;
};

bool volumn::hit(const ray &r, double t_min, double t_max, hit_record &record) const {
    hit_record record1, record2;
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

    const double ray_length = r.direction.length();
    const double distance_inside_boundary = ray_length * (record2.t - record1.t);
    const double hit_distance = -(1.0 / density) * log(random_number());
    if (hit_distance > distance_inside_boundary) {
        return false;
    }
    record.t = record1.t + distance_inside_boundary / ray_length;
    record.hit_point = r.at(record.t);
    record.normal = vec3(0, 0, 1); //arbitrary, no use
    record.material_ptr = iso;

//    std::cerr << "hit_distance = " << hit_distance << '\n'
//              << "rec.t = " << record.t << '\n'
//              << "rec.p = " << record.hit_point << '\n';
    return true;
}

std::shared_ptr<aabb> volumn::bounding_box(double time0, double time1, bool &bounded) const {
    return boundary->bounding_box(time0, time1, bounded);
}

#endif //RAYTRACING_VOLUMN_HPP
