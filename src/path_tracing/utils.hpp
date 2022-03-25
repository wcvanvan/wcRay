#ifndef RAYTRACING_UTILS_CPP
#define RAYTRACING_UTILS_CPP

#include <iostream>
#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include <ctime>
#include "vec3.hpp"


const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

double degrees_to_radians(double degrees) {
    return degrees * pi / 180.;
}

double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}


class vec3;

class Random {
public:
    std::default_random_engine *engine;
    std::uniform_real_distribution<double> *distribution;

    explicit Random(double min = 0.0, double max = 1.0) {
        std::random_device seed;
        engine = new std::default_random_engine(seed());
        distribution = new std::uniform_real_distribution<double>(min, max);
    }

    double random_number() const {
        return (*distribution)(*engine);
    }

    double random_number(double min, double max) const {
        return min + (max - min) * random_number();
    }

    vec3 random_in_unit_sphere() const {
        auto a = random_number(0, 2 * pi);
        auto z = random_number(-1, 1);
        auto r = sqrt(1 - z * z);
        return {r * cos(a), r * sin(a), z};
    }

    vec3 random_in_unit_disk() const {
        while (true) {
            auto p = vec3(random_number(-1, 1), random_number(-1, 1), 0);
            if (p.length_squared() >= 1) continue;
            return p;
        }
    }

    color random_color(double min = 0.0, double max = 1.0) const {
        return {random_number(min, max), random_number(min, max), random_number(min, max)};
    }
};


#endif //RAYTRACING_UTILS_CPP
