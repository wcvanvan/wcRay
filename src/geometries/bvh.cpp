#include "bvh.h"
#include <iostream>

WCRAY_NAMESPACE_BEGIN

    bool box_compare(const std::shared_ptr<Hittable> &h0, const std::shared_ptr<Hittable> &h1, int axis) {
        bool bounded0, bounded1;
        std::shared_ptr<AABB> box0 = h0->bounding_box(0, 0, bounded0);
        std::shared_ptr<AABB> box1 = h1->bounding_box(0, 0, bounded1);
        if (!bounded0 || !bounded1) {
            std::cerr << "no bounding box" << std::endl;
        }
        return box0->point0.value[axis] < box1->point0.value[axis];
    }

    bool box_compare_x(const std::shared_ptr<Hittable> &h0, const std::shared_ptr<Hittable> &h1) {
        return box_compare(h0, h1, 0);
    }

    bool box_compare_y(const std::shared_ptr<Hittable> &h0, const std::shared_ptr<Hittable> &h1) {
        return box_compare(h0, h1, 1);
    }

    bool box_compare_z(const std::shared_ptr<Hittable> &h0, const std::shared_ptr<Hittable> &h1) {
        return box_compare(h0, h1, 2);
    }


    BVHNode::BVHNode(const std::vector<std::shared_ptr<Hittable>> &objects, int start, int end, double time_start,
                       double time_end) {
        std::vector<std::shared_ptr<Hittable>> copy_objects = objects;
        int axis = random_int(0, 2);
        auto comparator = box_compare_x;
        if (axis == 1) {
            comparator = box_compare_y;
        } else if (axis == 2) {
            comparator = box_compare_z;
        }

        size_t object_span = end - start;
        if (object_span == 1) {
            left = copy_objects[start];
            right = left;
        } else if (object_span == 2) {
            left = copy_objects[start];
            right = copy_objects[start + 1];
            if (!comparator(left, right)) {
                std::swap(left, right);
            }
        } else {
            std::sort(copy_objects.begin() + start, copy_objects.begin() + end, comparator);
            size_t mid = start + object_span / 2;
            left = std::make_shared<BVHNode>(copy_objects, start, mid + 1, time_start, time_end);
            right = std::make_shared<BVHNode>(copy_objects, mid + 1, end, time_start, time_end);
        }
        bool bounded0, bounded1;
        auto box_left = left->bounding_box(time_start, time_end, bounded0);
        auto box_right = right->bounding_box(time_start, time_end, bounded1);
        if (!bounded0 || !bounded1) {
            std::cerr << "no bounding box" << std::endl;
        }
        box = AABB::surrounding_box(box_left, box_right);
    }

    std::shared_ptr<AABB> BVHNode::bounding_box(double time0, double time1, bool &bounded) const {
        bounded = true;
        return box;
    }

    bool BVHNode::hit(const Ray &r, double t_min, double t_max, HitRecord &record) const {
        if (!box->hit(r, t_min, t_max)) {
            return false;
        }
        bool hit_left = left->hit(r, t_min, t_max, record);
        bool hit_right = right->hit(r, t_min, hit_left ? record.t : t_max, record);
        return hit_left || hit_right;
    }

WCRAY_NAMESPACE_END
