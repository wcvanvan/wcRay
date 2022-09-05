#ifndef SOFTWAREPATHTRACING_VEC_H
#define SOFTWAREPATHTRACING_VEC_H

#include "common.h"

WCRAY_NAMESPACE_BEGIN

    class Vec3 {
    public:
        double value[3]{0., 0., 0.};

        Vec3();

        Vec3(double x, double y, double z);

        Vec3(const Vec3 &v);

        [[nodiscard]] double x() const;

        [[nodiscard]] double y() const;

        [[nodiscard]] double z() const;

        Vec3 &operator=(const Vec3 &v);

        bool operator==(const Vec3 &v);

        double &operator[](int index);

        Vec3 operator+(double t) const;

        friend Vec3 operator+(double t, const Vec3 &v);

        Vec3 operator+(const Vec3 &v) const;

        Vec3 &operator+=(double t);

        Vec3 &operator+=(const Vec3 &v);

        Vec3 operator-(double t) const;

        friend Vec3 operator-(double t, const Vec3 &v);

        Vec3 operator-(const Vec3 &v) const;

        Vec3 &operator-=(double t);

        Vec3 &operator-=(const Vec3 &v);

        Vec3 operator*(double t) const;

        friend Vec3 operator*(double t, const Vec3 &v);

        Vec3 &operator*=(double t);

        Vec3 operator*(const Vec3 &v) const;

        Vec3 operator/(double t) const;

        Vec3 &operator/=(double t);

    };

    [[nodiscard]] double dot(const Vec3 &v1, const Vec3 &v2);

    [[nodiscard]] Vec3 cross(const Vec3 &v1, const Vec3 &v2);

    [[nodiscard]] double length_squared(Vec3 v);

    [[nodiscard]] Vec3 normalize(Vec3 v);

    std::ostream &operator<<(std::ostream &out, const Vec3 &v);

    bool near_zero(Vec3 &v);

    Vec3 refract(const Vec3 &vec_in, const Vec3 &n, double etai_over_etat);

    Vec3 reflect(const Vec3 &vec_in, const Vec3 &normal);

    using Color = Vec3;
    using Point3 = Vec3;

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_VEC_H


