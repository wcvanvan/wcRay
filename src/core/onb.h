#ifndef SOFTWAREPATHTRACING_ONB_H
#define SOFTWAREPATHTRACING_ONB_H

#include "vec.h"

WCRAY_NAMESPACE_BEGIN

    class ONB {
    public:
        Vec3 axis[3];

        ONB() = default;

        Vec3 operator[](int i) const { return axis[i]; }

        [[nodiscard]] Vec3 u() const { return axis[0]; }

        [[nodiscard]] Vec3 v() const { return axis[1]; }

        [[nodiscard]] Vec3 w() const { return axis[2]; }

        [[nodiscard]] Vec3 local(double a, double b, double c) const {
            return a * u() + b * v() + c * w();
        }

        [[nodiscard]] Vec3 local(const Vec3 &a) const {
            return a.x() * u() + a.y() * v() + a.z() * w();
        }

        void build_from_w(const Vec3 &);
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_ONB_H
