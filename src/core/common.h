#ifndef SOFTWAREPATHTRACING_COMMON_H
#define SOFTWAREPATHTRACING_COMMON_H

#include <cmath>
#include <limits>
#include <memory>
#include <iostream>
#include <random>
#include <ctime>

#define WCRAY_NAMESPACE_BEGIN namespace wcRay {
#define WCRAY_NAMESPACE_END }

WCRAY_NAMESPACE_BEGIN

#define infinity std::numeric_limits<double>::infinity()
#define PI 3.1415926535897932385

    double degrees_to_radians(double degrees);

    double clamp(double x, double min, double max);

    class Vec3;

    [[nodiscard]] double random_number();

    [[nodiscard]] double random_number(double min, double max);

    [[nodiscard]] Vec3 random_in_unit_sphere();

    [[nodiscard]] Vec3 random_in_unit_disk();

    /*
     * Returns a random integer in [min,max].
     */
    [[nodiscard]] int random_int(int min, int max);

WCRAY_NAMESPACE_END
#endif //SOFTWAREPATHTRACING_COMMON_H
