#ifndef RAYTRACING_CAMERA_HPP
#define RAYTRACING_CAMERA_HPP

#include "vec3.hpp"
#include "ray.hpp"

class camera {
private:
    point3 origin;
    vec3 horizontal, vertical;
    point3 lower_left_corner;
    double lens_radius;
    vec3 horizontal_unit, vertical_unit, look_unit;
    double time_start, time_end;

public:
    camera(const point3 &look_from, const point3 &look_to, const vec3 &view_up, double fov_vertical,
           double aspect_ratio, double aperture, double focus_dist, double _time_start,
           double _time_end) : time_start(_time_start), time_end(_time_end) {
        const double radian = degrees_to_radians(fov_vertical);
        const double viewport_height = 2 * tan(radian / 2);
        const double viewport_width = viewport_height * aspect_ratio;
        origin = look_from;
        look_unit = (look_to - look_from).unit_vector();
        horizontal_unit = look_unit.cross(view_up).unit_vector();
        vertical_unit = horizontal_unit.cross(look_unit).unit_vector();
        horizontal = focus_dist * viewport_width * horizontal_unit;
        vertical = focus_dist * viewport_height * vertical_unit;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 + focus_dist * look_unit;
        lens_radius = aperture / 2;
    }

    ray get_ray(double vertical_coefficient, double horizontal_coefficient) {
        vec3 offset = lens_radius * random_in_unit_disk();
        point3 ray_start_point =
                origin + offset.x() * horizontal_unit + offset.y() * vertical_unit;
        return {ray_start_point, lower_left_corner + horizontal * horizontal_coefficient +
                                 vertical * vertical_coefficient - ray_start_point,
                random_number(time_start, time_end)};
    }
};

#endif //RAYTRACING_CAMERA_HPP
