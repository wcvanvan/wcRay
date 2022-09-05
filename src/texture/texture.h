#ifndef SOFTWAREPATHTRACING_TEXTURE_H
#define SOFTWAREPATHTRACING_TEXTURE_H

#include "../core/vec.h"

WCRAY_NAMESPACE_BEGIN

    class texture {
    public:
        [[nodiscard]] virtual Color value(double u, double v, const Point3 &p) const = 0;
    };

    class solid_color : public texture {
    private:
        Color color_value;
    public:
        explicit solid_color(const Color &c) : color_value(c) {}

        [[nodiscard]] Color value(double u, double v, const Point3 &p) const override {
            return color_value;
        }
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_TEXTURE_H
