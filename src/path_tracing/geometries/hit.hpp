#ifndef RAYTRACING_HIT_HPP
#define RAYTRACING_HIT_HPP

#include "../material/material.hpp"
#include "core/utils.hpp"
#include "aabb.hpp"
#include <cmath>

class HitRecord {
public:
    point3 hit_point{};
    vec3 normal{};
    double t{0};
    double u, v; // coordinate on texture
    bool exterior_hit{true};
    std::shared_ptr<Material> material_ptr{};

    inline void set_face_normal(const Ray &r, const vec3 &outward_normal) {
        bool front_face = r.direction.dot(outward_normal) < 0;
        normal = front_face ? outward_normal : outward_normal * (-1);
    }
};

class Hittable {
public:
    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const = 0;

    virtual std::shared_ptr<aabb> bounding_box(double time0, double time1, bool &bounded) const = 0;

    [[nodiscard]] virtual double pdf_value(const point3 &origin, const vec3 &direction) const {
        return 0.0;
    }

    [[nodiscard]] virtual vec3 random_direction(const vec3 &origin) const {
        return {1, 0, 0};
    }
};


#endif //RAYTRACING_HIT_HPP
