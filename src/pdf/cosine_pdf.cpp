#include "cosine_pdf.h"

WCRAY_NAMESPACE_BEGIN

    Vec3 random_uniform_direction() {
        auto r1 = random_number();
        auto r2 = random_number();
        auto z = sqrt(1 - r2);

        auto phi = 2 * PI * r1;
        auto x = cos(phi) * sqrt(r2);
        auto y = sin(phi) * sqrt(r2);

        return {x, y, z};
    }

    CosinePDF::CosinePDF(const Vec3 &w) {
        uvw.build_from_w(w);
    }

    [[nodiscard]] double CosinePDF::value(const Vec3 &direction) const {
        auto cosine = dot(normalize(direction), uvw.w());
        return std::max(0.0, cosine / PI);
    }

    [[nodiscard]] Vec3 CosinePDF::generate() const {
        return uvw.local(random_uniform_direction());
    }

WCRAY_NAMESPACE_END
