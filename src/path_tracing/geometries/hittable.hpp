#ifndef RAYTRACING_HITTABLE_HPP
#define RAYTRACING_HITTABLE_HPP

#include "../texture/material.hpp"

class hit_record {
public:
    point3 hit_point;
    vec3 normal;
    double t;
    bool exterior_hit;
    std::shared_ptr<material> material_ptr;
};

class hittable {
public:
    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &record) const = 0;
};


#endif //RAYTRACING_HITTABLE_HPP
