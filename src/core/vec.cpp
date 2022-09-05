#include "vec.h"
#include <cmath>
#include <iostream>

WCRAY_NAMESPACE_BEGIN

    Vec3::Vec3() = default;

    Vec3::Vec3(double x, double y, double z) : value{x, y, z} {}

    Vec3::Vec3(const Vec3 &v) {
        value[0] = v.x();
        value[1] = v.y();
        value[2] = v.z();
    }

    [[nodiscard]] double Vec3::x() const {
        return value[0];

    }

    [[nodiscard]] double Vec3::y() const {
        return value[1];

    }

    [[nodiscard]] double Vec3::z() const {
        return value[2];
    }


    Vec3 &Vec3::operator=(const Vec3 &v) {
        value[0] = v.value[0];
        value[1] = v.value[1];
        value[2] = v.value[2];
        return *this;
    }

    bool Vec3::operator==(const Vec3 &v) {
        return (value[0] == v.value[0] && value[1] == v.value[1] && value[2] == v.value[2]);
    }

    double &Vec3::operator[](int index) {
        if (index >= 0 && index <= 2) {
            return value[index];
        } else {
            std::cerr << "Error in File \"" << __FILE__ << "\", Function " << __FUNCTION__ << ", Line " << __LINE__
                      << ": Index out of bound" << std::endl;
            return value[0];
        }
    }

    Vec3 Vec3::operator+(double t) const {
        return Vec3{value[0] + t, value[1] + t, value[2] + t};
    }

    Vec3 operator+(double t, const Vec3 &v) {
        return v + t;
    }

    Vec3 Vec3::operator+(const Vec3 &v) const {
        return Vec3{value[0] + v.value[0], value[1] + v.value[1], value[2] + v.value[2]};
    }

    Vec3 &Vec3::operator+=(double t) {
        value[0] += t;
        value[1] += t;
        value[2] += t;
        return *this;
    }

    Vec3 &Vec3::operator+=(const Vec3 &v) {
        value[0] += v.value[0];
        value[1] += v.value[1];
        value[2] += v.value[2];
        return *this;
    }

    Vec3 Vec3::operator-(double t) const {
        return {value[0] - t, value[1] - t, value[2] - t};
    }

    Vec3 operator-(double t, const Vec3 &v) {
        return (v - t) * (-1.0);
    }

    Vec3 Vec3::operator-(const Vec3 &v) const {
        return Vec3{value[0] - v.value[0], value[1] - v.value[1], value[2] - v.value[2]};
    }

    Vec3 &Vec3::operator-=(double t) {
        value[0] -= t;
        value[1] -= t;
        value[2] -= t;
        return *this;
    }

    Vec3 &Vec3::operator-=(const Vec3 &v) {
        value[0] -= v.value[0];
        value[1] -= v.value[1];
        value[2] -= v.value[2];
        return *this;
    }

    Vec3 Vec3::operator*(double t) const {
        return Vec3{value[0] * t, value[1] * t, value[2] * t};
    }

    Vec3 operator*(double t, const Vec3 &v) {
        return v * t;
    }

    Vec3 &Vec3::operator*=(double t) {
        value[0] *= t;
        value[1] *= t;
        value[2] *= t;
        return *this;
    }

    Vec3 Vec3::operator*(const Vec3 &v) const {
        return {value[0] * v.x(), value[1] * v.y(), value[2] * v.z()};
    }

    Vec3 Vec3::operator/(double t) const {
        if (t != 0) {
            return Vec3{value[0] / t, value[1] / t, value[2] / t};
        } else {
            std::cerr << "Error in File \"" << __FILE__ << "\", Function " << __FUNCTION__ << ", Line " << __LINE__
                      << ": divisor must not be 0" << std::endl;
            return *this;
        }
    }

    Vec3 &Vec3::operator/=(double t) {
        if (t != 0) {
            value[0] /= t;
            value[1] /= t;
            value[2] /= t;
        } else {
            std::cerr << "Error in File \"" << __FILE__ << "\", Function " << __FUNCTION__ << ", Line " << __LINE__
                      << ": divisor must not be 0" << std::endl;
        }
        return *this;
    }

    [[nodiscard]] double dot(const Vec3 &v1, const Vec3 &v2) {
        return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
    }

    [[nodiscard]] Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
        return Vec3{v1.y() * v2.z() - v1.z() * v2.y(),
                    v1.z() * v2.x() - v1.x() * v2.z(),
                    v1.x() * v2.y() - v1.y() * v2.x()};
    }

    [[nodiscard]] double length_squared(Vec3 v) {
        return pow(v.x(), 2) + pow(v.y(), 2) + pow(v.z(), 2);
    }

    [[nodiscard]] Vec3 normalize(Vec3 v) {
        return {v / sqrt(length_squared(v))};
    }


    std::ostream &operator<<(std::ostream &out, const Vec3 &v) {
        out << v.value[0] << ' ' << v.value[1] << ' ' << v.value[2];
        return out;
    }

    bool near_zero(Vec3 &v) {
        const double min = 1e-8;
        if (fabs(v.x()) < min && fabs(v.y()) < min && fabs(v.z()) < min) {
            return true;
        }
        return false;
    }

    Vec3 refract(const Vec3 &vec_in, const Vec3 &n, double etai_over_etat) {
        auto cos_theta = fmin(dot((-1) * vec_in, n), 1.0);
        Vec3 r_out_perp = etai_over_etat * (vec_in + cos_theta * n);
        Vec3 r_out_parallel = -sqrt(fabs(1.0 - length_squared(r_out_perp))) * n;
        return r_out_perp + r_out_parallel;
    }

    Vec3 reflect(const Vec3 &vec_in, const Vec3 &normal) {
        return {vec_in + 2 * dot((-1) * vec_in, normal) * normal};
    }

WCRAY_NAMESPACE_END