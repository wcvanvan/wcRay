#ifndef SOFTWAREPATHTRACING_HITTABLE_PDF_H
#define SOFTWAREPATHTRACING_HITTABLE_PDF_H

#include "pdf.h"
#include "../geometries/hit.h"
#include "../core/vec.h"
#include <memory>

WCRAY_NAMESPACE_BEGIN

    using std::shared_ptr;

    class HittablePDF : public PDF {
    public:
        shared_ptr<Hittable> ptr;
        Point3 origin;

        HittablePDF(std::shared_ptr<Hittable> ptr_, const Point3 &origin_) : ptr(std::move(ptr_)), origin(origin_) {}

        [[nodiscard]] double value(const Vec3 &direction) const override;

        [[nodiscard]] Vec3 generate() const override;
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_HITTABLE_PDF_H
