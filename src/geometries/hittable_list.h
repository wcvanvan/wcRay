#ifndef SOFTWAREPATHTRACING_HITTABLE_LIST_H
#define SOFTWAREPATHTRACING_HITTABLE_LIST_H

#include "hit.h"
#include "aabb.h"
#include "../core/vec.h"
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

WCRAY_NAMESPACE_BEGIN

    class HittableList : public Hittable {
    public:

        HittableList() = default;


        vector<shared_ptr<Hittable>> hittable_objects;

        void add(const shared_ptr<Hittable> &hittable_object) { hittable_objects.push_back(hittable_object); }

        bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const override;

        std::shared_ptr<AABB> bounding_box(double time0, double time1, bool &bounded) const override;

        [[nodiscard]] double pdf_value(const Point3 &origin, const Vec3 &direction) const override;

        [[nodiscard]] Vec3 random_direction(const Vec3 &origin) const override;

    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_HITTABLE_LIST_H
