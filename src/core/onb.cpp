
#include "onb.h"

WCRAY_NAMESPACE_BEGIN

    void ONB::build_from_w(const Vec3 &n) {
        axis[2] = normalize(n);
        Vec3 a = (fabs(axis[2][0]) > 0.9) ? Vec3(0, 1, 0) : Vec3(1, 0, 0);
        axis[0] = normalize(cross(a, axis[2]));
        axis[1] = normalize(cross(axis[0], axis[2]));
    }

WCRAY_NAMESPACE_END
