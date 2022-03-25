#ifndef RAYTRACING_HITTABLE_LIST_HPP
#define RAYTRACING_HITTABLE_LIST_HPP

#include <vector>
#include <memory>
#include "geometries/hittable.hpp"

using std::vector;
using std::shared_ptr;

class hittable_list : public hittable {
public:
    vector<shared_ptr<hittable>> hittable_objects;

    void add(const shared_ptr<hittable>& hittable_object) { hittable_objects.push_back(hittable_object); }

    bool hit(const ray &r, double t_min, double t_max, hit_record &record) const override;
};

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &record) const {
    double shortest_t = t_max;
    bool hit_something{false};
    hit_record tmp_record;

    for (const auto &object: hittable_objects) {
        if (object->hit(r, t_min, shortest_t, tmp_record)) {
            hit_something = true;
            shortest_t = tmp_record.t;
            record = tmp_record;
        }
    }

    return hit_something;
}


#endif //RAYTRACING_HITTABLE_LIST_HPP
