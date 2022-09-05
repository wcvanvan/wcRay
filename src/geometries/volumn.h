#ifndef SOFTWAREPATHTRACING_VOLUMN_H
#define SOFTWAREPATHTRACING_VOLUMN_H

#include "../core/common.h"
#include "hit.h"
#include "../material/isotropic.h"

WCRAY_NAMESPACE_BEGIN

    class Volumn : public Hittable {
    public:
        std::shared_ptr<Hittable> boundary;
        double density;
        std::shared_ptr<Isotropic> iso;

        Volumn(std::shared_ptr<Hittable> obj, double _density, std::shared_ptr<Isotropic> isotropic_);

        bool hit(const Ray &r, double t_min, double t_max, HitRecord &record) const override;

        std::shared_ptr<AABB> bounding_box(double time0, double time1, bool &bounded) const override;
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_VOLUMN_H
