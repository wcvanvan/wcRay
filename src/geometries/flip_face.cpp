#include "flip_face.h"

WCRAY_NAMESPACE_BEGIN

    FlipFace::FlipFace(shared_ptr<Hittable> p) {
        ptr = std::move(p);
    }

    bool FlipFace::hit(
            const Ray &r, double t_min, double t_max, HitRecord &rec) const {

        if (!ptr->hit(r, t_min, t_max, rec))
            return false;

        rec.exterior_hit = !rec.exterior_hit;
        return true;
    }

    std::shared_ptr<AABB> FlipFace::bounding_box(double time0, double time1, bool &bounded) const {
        return ptr->bounding_box(time0, time1, bounded);
    }


WCRAY_NAMESPACE_END
