#ifndef RAYTRACING_HIT_HPP
#define RAYTRACING_HIT_HPP

#include "../material/material.hpp"
#include "../utils.hpp"
#include "aabb.hpp"
#include <cmath>

class hit_record {
public:
    point3 hit_point{};
    vec3 normal{};
    double t{0};
    double u, v; // coordinate on texture
    bool exterior_hit{true};
    std::shared_ptr<material> material_ptr{};

    inline void set_face_normal(const ray &r, const vec3 &outward_normal) {
        bool front_face = r.direction.dot(outward_normal) < 0;
        normal = front_face ? outward_normal : outward_normal * (-1);
    }
};

class hittable {
public:
    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &record) const = 0;

    virtual std::shared_ptr<aabb> bounding_box(double time0, double time1, bool &bounded) const = 0;

};



#endif //RAYTRACING_HIT_HPP
