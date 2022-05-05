#ifndef RAYTRACING_RAY_HPP
#define RAYTRACING_RAY_HPP

#include "vec3.hpp"

class ray {
public:
    point3 origin;
    vec3 direction;
    double time{};

    ray() = default;

    ray(const point3 &_origin, const vec3 &_direction, double _time) {
        origin = _origin;
        direction = _direction;
        time = _time;
    }

    [[nodiscard]] point3 at(double t) const {
        return {origin + direction * t};
    }
};


#endif //RAYTRACING_RAY_HPP
