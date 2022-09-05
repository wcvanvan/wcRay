#ifndef RAYTRACING_UTILS_CPP
#define RAYTRACING_UTILS_CPP

#include "common.h"
#include "vec.h"

WCRAY_NAMESPACE_BEGIN

    double degrees_to_radians(double degrees) {
        return degrees * PI / 180.;
    }

    double clamp(double x, double min, double max) {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    [[nodiscard]] double random_number() {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

    [[nodiscard]] double random_number(double min, double max) {
        return min + (max - min) * random_number();
    }

    [[nodiscard]] Vec3 random_in_unit_sphere() {
        auto a = random_number(0, 2 *PI);
        auto z = random_number(-1, 1);
        auto r = sqrt(1 - z * z);
        return {r * cos(a), r * sin(a), z};
    }

    [[nodiscard]] Vec3 random_in_unit_disk() {
        while (true) {
            auto p = Vec3(random_number(-1, 1), random_number(-1, 1), 0);
            if (length_squared(p) >= 1) continue;
            return p;
        }
    }

/*
 * Returns a random integer in [min,max].
 */
    [[nodiscard]] int random_int(int min, int max) {

        return static_cast<int>(random_number(min, max + 1));
    }


WCRAY_NAMESPACE_END

#endif //RAYTRACING_UTILS_CPP