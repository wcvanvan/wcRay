#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>

class vec3 {
public:
    double value[3]{0., 0., 0.};

    vec3() = default;

    vec3(double x, double y, double z) : value{x, y, z} {}

    vec3(const vec3 &v) {
        value[0] = v.x();
        value[1] = v.y();
        value[2] = v.z();
    }

    [[nodiscard]] double x() const {
        return value[0];

    }

    [[nodiscard]] double y() const {
        return value[1];

    }

    [[nodiscard]] double z() const {
        return value[2];
    }


    vec3 &operator=(const vec3 &v) {
        value[0] = v.value[0];
        value[1] = v.value[1];
        value[2] = v.value[2];
        return *this;
    }

    bool operator==(const vec3 &v) {
        return (value[0] == v.value[0] && value[1] == v.value[1] && value[2] == v.value[2]);
    }

    double &operator[](int index) {
        if (index >= 0 && index <= 2) {
            return value[index];
        } else {
            std::cerr << "Error in File \"" << __FILE__ << "\", Function " << __FUNCTION__ << ", Line " << __LINE__
                      << ": Index out of bound" << std::endl;
            return value[0];
        }
    }

    vec3 operator+(double t) const {
        return vec3{value[0] + t, value[1] + t, value[2] + t};
    }

    friend vec3 operator+(double t, const vec3 &v) {
        return v + t;
    }

    vec3 operator+(const vec3 &v) const {
        return vec3{value[0] + v.value[0], value[1] + v.value[1], value[2] + v.value[2]};
    }

    vec3 &operator+=(double t) {
        value[0] += t;
        value[1] += t;
        value[2] += t;
        return *this;
    }

    vec3 &operator+=(const vec3 &v) {
        value[0] += v.value[0];
        value[1] += v.value[1];
        value[2] += v.value[2];
        return *this;
    }

    vec3 operator-(double t) const {
        return {value[0] - t, value[1] - t, value[2] - t};
    }

    friend vec3 operator-(double t, const vec3 &v) {
        return (v - t) * (-1.0);
    }

    vec3 operator-(const vec3 &v) const {
        return vec3{value[0] - v.value[0], value[1] - v.value[1], value[2] - v.value[2]};
    }

    vec3 &operator-=(double t) {
        value[0] -= t;
        value[1] -= t;
        value[2] -= t;
        return *this;
    }

    vec3 &operator-=(const vec3 &v) {
        value[0] -= v.value[0];
        value[1] -= v.value[1];
        value[2] -= v.value[2];
        return *this;
    }

    vec3 operator*(double t) const {
        return vec3{value[0] * t, value[1] * t, value[2] * t};
    }

    friend vec3 operator*(double t, const vec3 &v) {
        return v * t;
    }

    vec3 &operator*=(double t) {
        value[0] *= t;
        value[1] *= t;
        value[2] *= t;
        return *this;
    }

    vec3 operator*(const vec3 &v) const {
        return {value[0] * v.x(), value[1] * v.y(), value[2] * v.z()};
    }

    vec3 operator/(double t) const {
        if (t != 0) {
            return vec3{value[0] / t, value[1] / t, value[2] / t};
        } else {
            std::cerr << "Error in File \"" << __FILE__ << "\", Function " << __FUNCTION__ << ", Line " << __LINE__
                      << ": divisor must not be 0" << std::endl;
            return *this;
        }
    }

    vec3 &operator/=(double t) {
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

    [[nodiscard]] double dot(const vec3 &v) const {
        return value[0] * v.value[0] + value[1] * v.value[1] + value[2] * v.value[2];
    }

    [[nodiscard]] vec3 cross(const vec3 &v) const {
        return vec3{value[1] * v.value[2] - value[2] * v.value[1],
                    value[2] * v.value[0] - value[0] * v.value[2],
                    value[0] * v.value[1] - value[1] * v.value[0]};
    }

    [[nodiscard]] double length() const {
        return sqrt(pow(value[0], 2) + pow(value[1], 2) + pow(value[2], 2));
    }

    [[nodiscard]] double length_squared() const {
        return pow(value[0], 2) + pow(value[1], 2) + pow(value[2], 2);
    }

    [[nodiscard]] vec3 unit_vector() const {
        return vec3{*this / length()};
    }


    friend std::ostream &operator<<(std::ostream &out, const vec3 &v) {
        out << v.value[0] << ' ' << v.value[1] << ' ' << v.value[2];
        return out;
    }

    bool near_zero() {
        const double min = 1e-8;
        if (fabs(value[0]) < min && fabs(value[1]) < min && fabs(value[2]) < min) {
            return true;
        }
        return false;
    }



    static vec3 refract(const vec3 &vec_in, const vec3 &n, double etai_over_etat) {
        auto cos_theta = fmin(-vec_in.dot(n), 1.0);
        vec3 r_out_perp = etai_over_etat * (vec_in + cos_theta * n);
        vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
        return r_out_perp + r_out_parallel;
    }

    static vec3 reflect(const vec3 &vec_in, const vec3 &normal) {
        return {vec_in + 2 * ((-1) * vec_in).dot(normal) * normal};
    }


};

using Color = vec3;
using point3 = vec3;

#endif //VEC3_HPP
