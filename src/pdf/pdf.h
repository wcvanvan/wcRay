#ifndef SOFTWAREPATHTRACING_PDF_H
#define SOFTWAREPATHTRACING_PDF_H

#include "../core/vec.h"

WCRAY_NAMESPACE_BEGIN

    class PDF {
    public:
        [[nodiscard]] virtual double value(const Vec3 &direction) const = 0;

        [[nodiscard]] virtual Vec3 generate() const = 0;
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_PDF_H
