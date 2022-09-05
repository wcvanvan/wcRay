#ifndef SOFTWAREPATHTRACING_ALTERNATING_TEXTURE_H
#define SOFTWAREPATHTRACING_ALTERNATING_TEXTURE_H

#include "texture.h"
#include "../core/color.h"
#include <memory>

WCRAY_NAMESPACE_BEGIN

    class AlternatingTexture : public texture {
    public:
        std::shared_ptr<texture> t1, t2;

        [[nodiscard]] Color value(double u, double v, const Point3 &p) const override;

        AlternatingTexture(const Color &_c1, const Color &_c2);
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_ALTERNATING_TEXTURE_H
