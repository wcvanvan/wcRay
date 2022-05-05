#ifndef RAYTRACING_UTILS_CPP
#define RAYTRACING_UTILS_CPP

#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include <ctime>
#include "vec3.hpp"


double infinity = std::numeric_limits<double>::infinity();
double pi = 3.1415926535897932385;

double degrees_to_radians(double degrees) {
    return degrees * pi / 180.;
}

double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}


class vec3;


[[nodiscard]] double random_number() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

[[nodiscard]] double random_number(double min, double max) {
    return min + (max - min) * random_number();
}

[[nodiscard]] vec3 random_in_unit_sphere() {
    auto a = random_number(0, 2 * pi);
    auto z = random_number(-1, 1);
    auto r = sqrt(1 - z * z);
    return {r * cos(a), r * sin(a), z};
}

[[nodiscard]] vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_number(-1, 1), random_number(-1, 1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

[[nodiscard]] color random_color(double min = 0.0, double max = 1.0) {
    return {random_number(min, max), random_number(min, max), random_number(min, max)};
}

[[nodiscard]] int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return static_cast<int>(random_number(min, max + 1));
}


#endif //RAYTRACING_UTILS_CPP
