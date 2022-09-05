#include "sphere.h"

WCRAY_NAMESPACE_BEGIN

    Vec3 random_to_sphere(double radius, double distance_squared) {
        auto r1 = random_number();
        auto r2 = random_number();
        auto z = 1 + r2 * (sqrt(1 - radius * radius / distance_squared) - 1);

        auto phi = 2 * PI * r1;
        auto x = cos(phi) * sqrt(1 - z * z);
        auto y = sin(phi) * sqrt(1 - z * z);

        return {x, y, z};
    }


    Sphere::Sphere(const Point3 &p, double _radius, std::shared_ptr<Material> _material_ptr) : center(p),
                                                                                               radius(_radius),
                                                                                               material_ptr(std::move(
                                                                                                       _material_ptr)) {};


    bool Sphere::hit(const Ray &r, double t_min, double t_max, HitRecord &record) const {
        Vec3 oc = r.origin - center;
        double a = dot(r.direction, r.direction);
        double b = 2 * dot(r.direction, oc);
        double c = dot(oc, oc) - pow(radius, 2);
        double delta = pow(b, 2) - 4 * a * c;
        if (delta < 0) {
            return false;
        }
        double root = (-b - sqrt(delta)) / (2 * a);
        if (root < t_min || root > t_max) {
            root = (-b + sqrt(delta)) / (2 * a);
            if (root < t_min || root > t_max) {
                return false;
            }
        }
        record.t = root;
        record.hit_point = r.at(root);
        record.set_face_normal(r, normalize(record.hit_point - center));
        record.material_ptr = material_ptr;
        Sphere::get_sphere_uv(record.normal, record.u, record.v);
        return true;
    }

    std::shared_ptr<AABB> Sphere::bounding_box(double time0, double time1, bool &bounded) const {
        bounded = true;
        return std::make_shared<AABB>(
                AABB(center - Point3(radius, radius, radius), center + Point3(radius, radius, radius)));
    }

    void Sphere::get_sphere_uv(const Point3 &p, double &u, double &v) {
        double theta = acos(-p.y());
        double phi = atan2(-p.z(), p.x()) + PI;
        u = phi / (2 * PI);
        v = theta / PI;
    }

    double Sphere::pdf_value(const Point3 &origin, const Vec3 &direction) const {
        HitRecord rec;
        if (!this->hit(Ray(origin, direction), 0.001, infinity, rec))
            return 0;

        auto cos_theta_max = sqrt(1 - radius * radius / length_squared(center - origin));
        auto solid_angle = 2 * PI * (1 - cos_theta_max);

        return 1 / solid_angle;
    }

    Vec3 Sphere::random_direction(const Vec3 &origin) const {
        Vec3 direction = center - origin;
        auto distance_squared = length_squared(direction);
        ONB uvw;
        uvw.build_from_w(direction);
        return uvw.local(random_to_sphere(radius, distance_squared));
    }

WCRAY_NAMESPACE_END
