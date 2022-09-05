#ifndef SOFTWAREPATHTRACING_MIXTURE_PDF_H
#define SOFTWAREPATHTRACING_MIXTURE_PDF_H

#include "pdf.h"
#include <memory>

using std::shared_ptr;

WCRAY_NAMESPACE_BEGIN

    class MixturePDF : public PDF {
    public:
        shared_ptr<PDF> p[2];

        MixturePDF(std::shared_ptr<PDF> p0, std::shared_ptr<PDF> p1) {
            p[0] = std::move(p0);
            p[1] = std::move(p1);
        }

        [[nodiscard]] double value(const Vec3 &direction) const override;

        [[nodiscard]] Vec3 generate() const override;
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_MIXTURE_PDF_H
