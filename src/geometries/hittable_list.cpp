#include "hittable_list.h"

WCRAY_NAMESPACE_BEGIN

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

    std::shared_ptr<AABB> HittableList::bounding_box(double time0, double time1, bool &bounded) const {
        if (hittable_objects.empty()) { bounded = false; }
        std::shared_ptr<AABB> output_box = nullptr;
        std::shared_ptr<AABB> temp_box;
        for (const auto &object: hittable_objects) {
            temp_box = std::move(object->bounding_box(time0, time1, bounded));
            if (!bounded) {
                return nullptr;
            }
            output_box = AABB::surrounding_box(output_box, temp_box);
        }
        return output_box;
    }

    double HittableList::pdf_value(const Point3 &origin, const Vec3 &direction) const {
        double sum{0.0};
        double weight = 1.0 / (double) hittable_objects.size();
        for (const auto &object: hittable_objects) {
            sum += weight * object->pdf_value(origin, direction);
        }
        return sum;
    }

    Vec3 HittableList::random_direction(const Vec3 &origin) const {
        auto size = hittable_objects.size();
        return hittable_objects[random_int(0, (int) size - 1)]->random_direction(origin);
    }

WCRAY_NAMESPACE_END