#ifndef SOFTWAREPATHTRACING_RAY_H
#define SOFTWAREPATHTRACING_RAY_H

#include "vec.h"

WCRAY_NAMESPACE_BEGIN

    class Ray {
    public:
        Point3 origin;
        Vec3 direction;
        double time{};

        Ray() = default;

        Ray(const Point3 &origin_, const Vec3 &direction_, double time_ = 0.0);

        [[nodiscard]] Point3 at(double t) const;
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_RAY_H
