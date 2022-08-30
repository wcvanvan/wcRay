#ifndef RAYTRACING_RAY_HPP
#define RAYTRACING_RAY_HPP

#include "vec3.hpp"

class Ray {
public:
    point3 origin;
    vec3 direction;
    double time{};

    Ray() = default;

    Ray(const point3 &_origin, const vec3 &_direction, double _time=0.0) {
        origin = _origin;
        direction = _direction;
        time = _time;
    }

    [[nodiscard]] point3 at(double t) const {
        return {origin + direction * t};
    }
};


#endif //RAYTRACING_RAY_HPP
