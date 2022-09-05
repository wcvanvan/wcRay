#ifndef SOFTWAREPATHTRACING_MIXTURE_PDF_HPP
#define SOFTWAREPATHTRACING_MIXTURE_PDF_HPP

#include "mixture_pdf.h"

WCRAY_NAMESPACE_BEGIN

    [[nodiscard]] double MixturePDF::value(const Vec3 &direction) const {
        return (p[0]->value(direction) + p[1]->value(direction)) * 0.5 ;
    }

    [[nodiscard]] Vec3 MixturePDF::generate() const {
        double random = random_number();
        if (random <= 0.5) {
            return p[0]->generate();
        } else {
            return p[1]->generate();
        }
    }

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_MIXTURE_PDF_HPP
