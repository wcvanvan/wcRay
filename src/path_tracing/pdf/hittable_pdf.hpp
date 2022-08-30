#ifndef SOFTWAREPATHTRACING_HITTABLE_PDF_HPP
#define SOFTWAREPATHTRACING_HITTABLE_PDF_HPP

#include "pdf.hpp"
#include "geometries/hit.hpp"
#include "core/vec3.hpp"
#include <memory>
#include <utility>

using std::shared_ptr;

class HittablePDF : public PDF {
public:
    shared_ptr<Hittable> ptr;
    point3 origin;

    HittablePDF(std::shared_ptr<Hittable> ptr_, const point3& origin_) : ptr(std::move(ptr_)), origin(origin_) {}

    [[nodiscard]] double value(const vec3 &direction) const override {
        return ptr->pdf_value(origin, direction);
    }

    [[nodiscard]] vec3 generate() const override {
        return ptr->random_direction(origin);
    }
};

#endif //SOFTWAREPATHTRACING_HITTABLE_PDF_HPP
