#ifndef SOFTWAREPATHTRACING_COSINE_PDF_HPP
#define SOFTWAREPATHTRACING_COSINE_PDF_HPP

#include "pdf.hpp"
#include "core/onb.hpp"

vec3 random_uniform_direction() {
    auto r1 = random_number();
    auto r2 = random_number();
    auto z = sqrt(1 - r2);

    auto phi = 2 * PI * r1;
    auto x = cos(phi) * sqrt(r2);
    auto y = sin(phi) * sqrt(r2);

    return {x, y, z};
}

class CosinePDF : public PDF {
public:
    ONB uvw;

    explicit CosinePDF(const vec3 &w) {
        uvw.build_from_w(w);
    }

    [[nodiscard]] double value(const vec3 &direction) const override {
        auto cosine = direction.unit_vector().dot(uvw.w());
        return std::max(0.0, cosine / PI);
    }

    [[nodiscard]] vec3 generate() const override {
        return uvw.local(random_uniform_direction());
    }
};

#endif //SOFTWAREPATHTRACING_COSINE_PDF_HPP
