#ifndef SOFTWAREPATHTRACING_ROTATE_H
#define SOFTWAREPATHTRACING_ROTATE_H

#include "../core/vec.h"
#include "hit.h"
#include <memory>

WCRAY_NAMESPACE_BEGIN

    class rotate_y : public Hittable {
    public:
        std::shared_ptr<Hittable> object;
        double sin_theta;
        double cos_theta;

        rotate_y(std::shared_ptr<Hittable> _object, double angle);

        bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const override;

        std::shared_ptr<AABB> bounding_box(double time0, double time1, bool &bounded) const override;
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_ROTATE_H
