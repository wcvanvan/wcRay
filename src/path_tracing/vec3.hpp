#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>

class vec3 {
public:
    double e[3]{0., 0., 0.};

    vec3() = default;

    vec3(double x, double y, double z) : e{x, y, z} {}

    vec3(const vec3 &v) {
        *this = v;
    }

    double x() const {
        return e[0];

    }

    double y() const {
        return e[1];

    }

    double z() const {
        return e[2];
    }

    void setX(double x) {
        e[0] = x;
    }

    void setY(double y) {
        e[1] = y;
    }

    void setZ(double z) {
        e[2] = z;
    }

    vec3 &operator=(const vec3 &v) {
        e[0] = v.e[0];
        e[1] = v.e[1];
        e[2] = v.e[2];
        return *this;
    }

    bool operator==(const vec3 &v) {
        return (e[0] == v.e[0] && e[1] == v.e[1] && e[2] == v.e[2]);
    }

    double &operator[](int index) {
        if (index >= 0 && index <= 2) {
            return e[index];
        } else {
            std::cerr << "Error in File \"" << __FILE__ << "\", Function " << __FUNCTION__ << ", Line " << __LINE__
                      << ": Index out of bound" << std::endl;
            return e[0];
        }
    }

    vec3 operator+(double t) const {
        return vec3{e[0] + t, e[1] + t, e[2] + t};
    }

    friend vec3 operator+(double t, const vec3 &v) {
        return v + t;
    }

    vec3 operator+(const vec3 &v) const {
        return vec3{e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]};
    }

    vec3 &operator+=(double t) {
        e[0] += t;
        e[1] += t;
        e[2] += t;
        return *this;
    }

    vec3 &operator+=(const vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3 operator-(double t) const {
        return {e[0] - t, e[1] - t, e[2] - t};
    }

    friend vec3 operator-(double t, const vec3 &v) {
        return (v - t) * (-1.0);
    }

    vec3 operator-(const vec3 &v) const {
        return vec3{e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]};
    }

    vec3 &operator-=(double t) {
        e[0] -= t;
        e[1] -= t;
        e[2] -= t;
        return *this;
    }

    vec3 &operator-=(const vec3 &v) {
        e[0] -= v.e[0];
        e[1] -= v.e[1];
        e[2] -= v.e[2];
        return *this;
    }

    vec3 operator*(double t) const {
        return vec3{e[0] * t, e[1] * t, e[2] * t};
    }

    friend vec3 operator*(double t, const vec3 &v) {
        return v * t;
    }

    vec3 &operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3 operator*(const vec3 &v) const {
        return {e[0] * v.x(), e[1] * v.y(), e[2] * v.z()};
    }

    vec3 operator/(double t) const {
        if (t != 0) {
            return vec3{e[0] / t, e[1] / t, e[2] / t};
        } else {
            std::cerr << "Error in File \"" << __FILE__ << "\", Function " << __FUNCTION__ << ", Line " << __LINE__
                      << ": divisor must not be 0" << std::endl;
            return *this;
        }
    }

    vec3 &operator/=(double t) {
        if (t != 0) {
            e[0] /= t;
            e[1] /= t;
            e[2] /= t;
        } else {
            std::cerr << "Error in File \"" << __FILE__ << "\", Function " << __FUNCTION__ << ", Line " << __LINE__
                      << ": divisor must not be 0" << std::endl;
        }
        return *this;
    }

    double dot(const vec3 &v) const {
        return e[0] * v.e[0] + e[1] * v.e[1] + e[2] * v.e[2];
    }

    vec3 cross(const vec3 &v) const {
        return vec3{e[1] * v.e[2] - e[2] * v.e[1],
                    e[2] * v.e[0] - e[0] * v.e[2],
                    e[0] * v.e[1] - e[1] * v.e[0]};
    }

    double length() const {
        return sqrt(pow(e[0], 2) + pow(e[1], 2) + pow(e[2], 2));
    }

    double length_squared() const {
        return pow(e[0], 2) + pow(e[1], 2) + pow(e[2], 2);
    }

    vec3 unit_vector() const {
        return vec3{*this / length()};
    }


    friend std::ostream &operator<<(std::ostream &out, const vec3 &v) {
        out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
        return out;
    }

    bool near_zero() {
        const double min = 1e-8;
        if (fabs(e[0]) < min && fabs(e[1]) < min && fabs(e[2]) < min) {
            return true;
        }
        return false;
    }

    //    vec3 refract(const vec3 &normal, double refraction_ratio) const {
    ////        double cos_theta = fmin((*this * (-1)).dot(normal), 1.0);
    ////        vec3 r_out_perp = (*this + normal * cos_theta) * refraction_ratio;
    ////        vec3 r_out_parallel = normal * -sqrt(fabs(1.0 - sqrt(r_out_perp.length())));
    ////        return r_out_parallel + r_out_perp;
    //    }

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

using color = vec3;
using point3 = vec3;

#endif //VEC3_HPP
