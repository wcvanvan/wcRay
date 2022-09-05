#include "ray.h"

WCRAY_NAMESPACE_BEGIN

    Ray::Ray(const Point3 &origin_, const Vec3 &direction_, double time_) {
        origin = origin_;
        direction = direction_;
        time = time_;
    }

    [[nodiscard]] Point3 Ray::at(double t) const {
        return {origin + direction * t};
    }

WCRAY_NAMESPACE_END

