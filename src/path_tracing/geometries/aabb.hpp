#ifndef RAYTRACING_AABB_HPP
#define RAYTRACING_AABB_HPP

#include <algorithm>
#include <memory>


class aabb {
public:
    point3 point0, point1; // point0 is the smaller point
    aabb() = default;

    aabb(const point3 &_point0, const point3 &_point1) : point0(_point0), point1(_point1) {}

    [[nodiscard]] bool hit(const ray &r, double t_min, double t_max) const;

    static std::shared_ptr<aabb> surrounding_box(std::shared_ptr<aabb> box0, std::shared_ptr<aabb> box1);
};

bool aabb::hit(const ray &r, double t_min, double t_max) const {
    int dimension = 3;
    for (int dim = 0; dim < dimension; ++dim) {
        double t0 = double(point0.value[dim] - r.origin.value[dim]) / r.direction.value[dim];
        double t1 = double(point1.value[dim] - r.origin.value[dim]) / r.direction.value[dim];
        if (r.direction.value[dim] < 0.0) {
            std::swap(t0, t1);
        }
        t_min = std::fmax(t0, t_min);
        t_max = std::fmin(t1, t_max);
        if (t_max <= t_min) {
            return false;
        }
    }
    return true;
}

std::shared_ptr<aabb> aabb::surrounding_box(std::shared_ptr<aabb> box0, std::shared_ptr<aabb> box1) {
    if (box0 == nullptr) {
        return box1;
    } else if (box1 == nullptr) {
        return box0;
    }
    point3 near_point(
            std::fmin(std::min(box0->point0.x(), box0->point1.x()), std::min(box1->point0.x(), box1->point1.x())),
            std::fmin(std::min(box0->point0.y(), box0->point1.y()), std::min(box1->point0.y(), box1->point1.y())),
            std::fmin(std::min(box0->point0.z(), box0->point1.z()), std::min(box1->point0.z(), box1->point1.z()))
    );
    point3 far_point(
            std::fmax(std::max(box0->point0.x(), box0->point1.x()), std::max(box1->point0.x(), box1->point1.x())),
            std::fmax(std::max(box0->point0.y(), box0->point1.y()), std::max(box1->point0.y(), box1->point1.y())),
            std::fmax(std::max(box0->point0.z(), box0->point1.z()), std::max(box1->point0.z(), box1->point1.z()))
    );
    auto sur_box = std::make_shared<aabb>(near_point, far_point);
    return sur_box;
}

#endif //RAYTRACING_AABB_HPP
