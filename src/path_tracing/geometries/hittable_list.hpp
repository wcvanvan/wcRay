#ifndef RAYTRACING_HITTABLE_LIST_HPP
#define RAYTRACING_HITTABLE_LIST_HPP

#include <vector>
#include <memory>
#include "hit.hpp"
#include "aabb.hpp"

using std::vector;
using std::shared_ptr;

class HittableList : public Hittable {
public:

    HittableList() = default;


    vector<shared_ptr<Hittable>> hittable_objects;

    void add(const shared_ptr<Hittable> &hittable_object) { hittable_objects.push_back(hittable_object); }

    bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const override;

    std::shared_ptr<aabb> bounding_box(double time0, double time1, bool &bounded) const override;

    [[nodiscard]] double pdf_value(const point3 &origin, const vec3 &direction) const override;

    [[nodiscard]] vec3 random_direction(const vec3 &origin) const override;

};

bool HittableList::hit(const Ray &r, double t_min, double t_max, HitRecord &record) const {
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

std::shared_ptr<aabb> HittableList::bounding_box(double time0, double time1, bool &bounded) const {
    if (hittable_objects.empty()) { bounded = false; }
    std::shared_ptr<aabb> output_box = nullptr;
    std::shared_ptr<aabb> temp_box;
    for (const auto &object: hittable_objects) {
        temp_box = std::move(object->bounding_box(time0, time1, bounded));
        if (!bounded) {
            return nullptr;
        }
        output_box = aabb::surrounding_box(output_box, temp_box);
    }
    return output_box;
}

double HittableList::pdf_value(const point3 &origin, const vec3 &direction) const {
    double sum{0.0};
    double weight = 1.0 / (double) hittable_objects.size();
    for (const auto &object: hittable_objects) {
        sum += weight * object->pdf_value(origin, direction);
    }
    return sum;
}

vec3 HittableList::random_direction(const vec3 &origin) const {
    auto size = hittable_objects.size();
    return hittable_objects[random_int(0, (int)size - 1)]->random_direction(origin);
}


#endif //RAYTRACING_HITTABLE_LIST_HPP
