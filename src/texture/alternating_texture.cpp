#include "alternating_texture.h"

WCRAY_NAMESPACE_BEGIN

    AlternatingTexture::AlternatingTexture(const Color &_c1, const Color &_c2) {
        t1 = std::make_shared<solid_color>(_c1);
        t2 = std::make_shared<solid_color>(_c2);
    }

    Color AlternatingTexture::value(double u, double v, const Point3 &p) const {
        auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
        if (sines < 0)
            return t1->value(u, v, p);
        else
            return t2->value(u, v, p);
    }

WCRAY_NAMESPACE_END
