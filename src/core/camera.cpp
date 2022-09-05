#include "camera.h"

WCRAY_NAMESPACE_BEGIN

    Camera::Camera(const Point3 &look_from, const Point3 &look_to, const Vec3 &view_up, double fov_vertical,
                   double aspect_ratio, double aperture, double focus_dist, double time_start_,
                   double time_end_) : time_start(time_start_), time_end(time_end_) {
        const double radian = degrees_to_radians(fov_vertical);
        const double viewport_height = 2 * tan(radian / 2);
        const double viewport_width = viewport_height * aspect_ratio;
        origin = look_from;
        look_unit = normalize(look_to - look_from);
        horizontal_unit = normalize(cross(look_unit, view_up));
        vertical_unit = normalize(cross(horizontal_unit, look_unit));
        horizontal = focus_dist * viewport_width * horizontal_unit;
        vertical = focus_dist * viewport_height * vertical_unit;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 + focus_dist * look_unit;
        lens_radius = aperture / 2;
    }

    Ray Camera::get_ray(double vertical_coefficient, double horizontal_coefficient) {
        Vec3 offset = lens_radius * random_in_unit_disk();
        Point3 ray_start_point =
                origin + offset.x() * horizontal_unit + offset.y() * vertical_unit;
        return {ray_start_point, lower_left_corner + horizontal * horizontal_coefficient +
                                 vertical * vertical_coefficient - ray_start_point,
                random_number(time_start, time_end)};
    }

WCRAY_NAMESPACE_END
