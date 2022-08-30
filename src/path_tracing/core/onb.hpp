#ifndef SOFTWAREPATHTRACING_ONB_HPP
#define SOFTWAREPATHTRACING_ONB_HPP

#include "vec3.hpp"

class ONB {
public:
    vec3 axis[3];

    ONB() = default;

    vec3 operator[](int i) const { return axis[i]; }

    [[nodiscard]] vec3 u() const { return axis[0]; }

    [[nodiscard]] vec3 v() const { return axis[1]; }

    [[nodiscard]] vec3 w() const { return axis[2]; }

    [[nodiscard]] vec3 local(double a, double b, double c) const {
        return a * u() + b * v() + c * w();
    }

    [[nodiscard]] vec3 local(const vec3 &a) const {
        return a.x() * u() + a.y() * v() + a.z() * w();
    }

    void build_from_w(const vec3 &);
};

void ONB::build_from_w(const vec3 &n) {
    axis[2] = n.unit_vector();
    vec3 a = (fabs(axis[2][0]) > 0.9) ? vec3(0, 1, 0) : vec3(1, 0, 0);
    axis[0] = a.cross(axis[2]).unit_vector();
    axis[1] = (axis[0].cross(axis[2])).unit_vector();
}


#endif //SOFTWAREPATHTRACING_ONB_HPP
