#ifndef RAYTRACING_BOX_HPP
#define RAYTRACING_BOX_HPP

#include <memory>
#include "hit.hpp"
#include "hittable_list.hpp"
#include "rectangle.hpp"

using std::make_shared;

class box : public hittable {
private:
    hittable_list sides;
    point3 point0, point1;
    std::shared_ptr<material> material_ptr;
public:
    box(const point3 &_point0, const point3 &_point1, std::shared_ptr<material> mat) {
        point0 = _point0;
        point1 = _point1;
        material_ptr = std::move(mat);

        sides.add(make_shared<xy_rect>(point0.x(), point1.x(), point0.y(), point1.y(), point1.z(), material_ptr));
        sides.add(make_shared<xy_rect>(point0.x(), point1.x(), point0.y(), point1.y(), point0.z(), material_ptr));

        sides.add(make_shared<xz_rect>(point0.x(), point1.x(), point0.z(), point1.z(), point1.y(), material_ptr));
        sides.add(make_shared<xz_rect>(point0.x(), point1.x(), point0.z(), point1.z(), point0.y(), material_ptr));

        sides.add(make_shared<yz_rect>(point0.y(), point1.y(), point0.z(), point1.z(), point1.x(), material_ptr));
        sides.add(make_shared<yz_rect>(point0.y(), point1.y(), point0.z(), point1.z(), point0.x(), material_ptr));
    }

    bool hit(const ray &r, double t_min, double t_max, hit_record &record) const override {
        return sides.hit(r, t_min, t_max, record);
    }

    std::shared_ptr<aabb> bounding_box(double time0, double time1, bool &bounded) const override {
        bounded = true;
        return std::make_shared<aabb>(point0, point1);
    }
};

#endif //RAYTRACING_BOX_HPP
