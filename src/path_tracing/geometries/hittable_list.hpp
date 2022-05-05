#ifndef RAYTRACING_HITTABLE_LIST_HPP
#define RAYTRACING_HITTABLE_LIST_HPP

#include <vector>
#include <memory>
#include "hit.hpp"
#include "aabb.hpp"

using std::vector;
using std::shared_ptr;

class hittable_list : public hittable {
public:

    hittable_list() = default;


    vector<shared_ptr<hittable>> hittable_objects;

    void add(const shared_ptr<hittable> &hittable_object) { hittable_objects.push_back(hittable_object); }

    bool hit(const ray &r, double t_min, double t_max, hit_record &record) const override;

    std::shared_ptr<aabb> bounding_box(double time0, double time1, bool &bounded) const override;

};

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &record) const {
    double shortest_t = t_max;
    bool hit_something{false};

    for (const auto &object: hittable_objects) {
        if (object->hit(r, t_min, shortest_t, record)) {
            hit_something = true;
            shortest_t = record.t;
        }
    }

    return hit_something;
}

std::shared_ptr<aabb> hittable_list::bounding_box(double time0, double time1, bool &bounded) const {
    if (hittable_objects.empty()) { bounded = false; }
    std::shared_ptr<aabb> output_box = nullptr;
    std::shared_ptr<aabb> temp_box;
    for (const auto &object: hittable_objects) {
        temp_box = std::move(object->bounding_box(time0, time1, bounded));
        if (!bounded) {
            return nullptr;
        }
        output_box = aabb::surrounding_box(std::move(output_box), std::move(temp_box));
    }
    return output_box;
}


#endif //RAYTRACING_HITTABLE_LIST_HPP
