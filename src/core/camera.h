#ifndef SOFTWAREPATHTRACING_CAMERA_H
#define SOFTWAREPATHTRACING_CAMERA_H

#include "vec.h"
#include "ray.h"

WCRAY_NAMESPACE_BEGIN

    class Camera {
    private:
        Point3 origin;
        Vec3 horizontal, vertical;
        Point3 lower_left_corner;
        double lens_radius;
        Vec3 horizontal_unit, vertical_unit, look_unit;
        double time_start, time_end;

    public:
        Camera(const Point3 &look_from, const Point3 &look_to, const Vec3 &view_up, double fov_vertical,
               double aspect_ratio, double aperture, double focus_dist, double time_start_,
               double time_end_);

        Ray get_ray(double vertical_coefficient, double horizontal_coefficient);
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_CAMERA_H