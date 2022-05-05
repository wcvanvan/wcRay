#ifndef RAYTRACING_MATERIAL_HPP
#define RAYTRACING_MATERIAL_HPP

#include "../ray.hpp"

class hit_record;

class material {
public:
    virtual color emit(double u, double v, const point3 &point) {
        return {0, 0, 0};
    }

    virtual bool scatter(const ray &r_in, const hit_record &record, color &albedo, ray &scattered) const = 0;
};


#endif //RAYTRACING_MATERIAL_HPP
