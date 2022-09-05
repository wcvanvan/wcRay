#ifndef SOFTWAREPATHTRACING_BOX_H
#define SOFTWAREPATHTRACING_BOX_H

#include "hit.h"
#include "hittable_list.h"
#include "rectangle.h"
#include <memory>

using std::make_shared;

WCRAY_NAMESPACE_BEGIN

    class Box : public Hittable {
    private:
        HittableList sides;
        Point3 point0, point1;
        std::shared_ptr<Material> material_ptr;
    public:
        Box(const Point3 &_point0, const Point3 &_point1, std::shared_ptr<Material> mat);

        bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const override;

        std::shared_ptr<AABB> bounding_box(double time0, double time1, bool &bounded) const override;
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_BOX_H
