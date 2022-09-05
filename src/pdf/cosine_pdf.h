#ifndef SOFTWAREPATHTRACING_COSINE_PDF_H
#define SOFTWAREPATHTRACING_COSINE_PDF_H

#include "pdf.h"
#include "../core/onb.h"

WCRAY_NAMESPACE_BEGIN

    class CosinePDF : public PDF {
    public:
        ONB uvw;

        explicit CosinePDF(const Vec3 &w);

        [[nodiscard]] double value(const Vec3 &direction) const override;

        [[nodiscard]] Vec3 generate() const override;
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_COSINE_PDF_H
