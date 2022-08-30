#ifndef SOFTWAREPATHTRACING_MIXTURE_PDF_HPP
#define SOFTWAREPATHTRACING_MIXTURE_PDF_HPP

#include <memory>
#include "pdf.hpp"
#include "core/utils.hpp"

class MixturePDF : public PDF {
public:
    shared_ptr<PDF> p[2];

    MixturePDF(std::shared_ptr<PDF> p0, std::shared_ptr<PDF> p1) {
        p[0] = std::move(p0);
        p[1] = std::move(p1);
    }

    [[nodiscard]] double value(const vec3 &direction) const override {
        return (p[0]->value(direction) + p[1]->value(direction)) * 0.5 ;
    }

    [[nodiscard]] virtual vec3 generate() const override {
        double random = random_number();
        if (random <= 0.5) {
            return p[0]->generate();
        } else {
            return p[1]->generate();
        }
    }
};

#endif //SOFTWAREPATHTRACING_MIXTURE_PDF_HPP
