#include "box.h"

using std::make_shared;

WCRAY_NAMESPACE_BEGIN

    Box::Box(const Point3 &_point0, const Point3 &_point1, std::shared_ptr<Material> mat) {
        point0 = _point0;
        point1 = _point1;
        material_ptr = std::move(mat);

        sides.add(make_shared<XYRect>(point0.x(), point1.x(), point0.y(), point1.y(), point1.z(), material_ptr));
        sides.add(make_shared<XYRect>(point0.x(), point1.x(), point0.y(), point1.y(), point0.z(), material_ptr));

        sides.add(make_shared<XZRect>(point0.x(), point1.x(), point0.z(), point1.z(), point1.y(), material_ptr));
        sides.add(make_shared<XZRect>(point0.x(), point1.x(), point0.z(), point1.z(), point0.y(), material_ptr));

        sides.add(make_shared<YZRect>(point0.y(), point1.y(), point0.z(), point1.z(), point1.x(), material_ptr));
        sides.add(make_shared<YZRect>(point0.y(), point1.y(), point0.z(), point1.z(), point0.x(), material_ptr));
    }

    bool Box::hit(const Ray &r, double t_min, double t_max, HitRecord &record) const {
        return sides.hit(r, t_min, t_max, record);
    }

    std::shared_ptr<AABB> Box::bounding_box(double time0, double time1, bool &bounded) const {
        bounded = true;
        return std::make_shared<AABB>(point0, point1);
    }

WCRAY_NAMESPACE_END
