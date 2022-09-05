#ifndef SOFTWAREPATHTRACING_BVH_H
#define SOFTWAREPATHTRACING_BVH_H

#include "hit.h"
#include "aabb.h"
#include <memory>
#include <vector>
#include <algorithm>

WCRAY_NAMESPACE_BEGIN

    class bvh_node : public Hittable {
    public:
        std::shared_ptr<Hittable> left, right;
        std::shared_ptr<AABB> box;

        bvh_node(const std::vector<std::shared_ptr<Hittable>> &objects, int start, int end, double time_start,
                 double time_end);

        bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const override;

        std::shared_ptr<AABB> bounding_box(double time0, double time1, bool &bounded) const override;
    };

    bool box_compare(const std::shared_ptr<Hittable> &h0, const std::shared_ptr<Hittable> &h1, int axis);

    bool box_compare_x(const std::shared_ptr<Hittable> &h0, const std::shared_ptr<Hittable> &h1);

    bool box_compare_y(const std::shared_ptr<Hittable> &h0, const std::shared_ptr<Hittable> &h1);

    bool box_compare_z(const std::shared_ptr<Hittable> &h0, const std::shared_ptr<Hittable> &h1);

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_BVH_H
