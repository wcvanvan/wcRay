#include "hittable_pdf.h"

WCRAY_NAMESPACE_BEGIN

    shared_ptr<Hittable> ptr;
    Point3 origin;

    [[nodiscard]] double HittablePDF::value(const Vec3 &direction) const {
        return ptr->pdf_value(origin, direction);
    }

    [[nodiscard]] Vec3 HittablePDF::generate() const {
        return ptr->random_direction(origin);
    }

WCRAY_NAMESPACE_END

