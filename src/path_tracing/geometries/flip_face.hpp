#include <utility>

#ifndef SOFTWAREPATHTRACING_FLIP_FACE_HPP
#define SOFTWAREPATHTRACING_FLIP_FACE_HPP

class FlipFace : public Hittable {
public:
    explicit FlipFace(shared_ptr<Hittable> p) : ptr(std::move(p)) {}

    bool hit(
            const Ray &r, double t_min, double t_max, HitRecord &rec) const override {

        if (!ptr->hit(r, t_min, t_max, rec))
            return false;

        rec.exterior_hit = !rec.exterior_hit;
        return true;
    }

    std::shared_ptr<aabb> bounding_box(double time0, double time1, bool &bounded) const override {
        return ptr->bounding_box(time0, time1, bounded);
    }

public:
    shared_ptr<Hittable> ptr;
};

#endif //SOFTWAREPATHTRACING_FLIP_FACE_HPP
