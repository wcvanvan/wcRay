#ifndef RAYTRACING_COLOR_HPP
#define RAYTRACING_COLOR_HPP
#include "ray.hpp"
#include "geometries/hittable.hpp"
#include "utils.hpp"


color ray_color(ray &r, hittable &world, int depth, Random &random) {
    if (depth <= 0) {
        return {0, 0, 0};
    }
    hit_record record;
    if (world.hit(r, 0.001, infinity, record)) {
        ray scattered;
        color albedo;
        if (record.material_ptr->scatter(r, record, albedo, scattered)) {
            return albedo * ray_color(scattered, world, depth - 1, random);
        }
    } else {
        double y = r.direction.y();
        double u = (y + 1) / 2.;
        return color(color(1.0, 1.0, 1.0) * (1 - u) + color(0.5, 0.7, 1.0) * u);
    }
}

void write_color(std::ostream &out, color &pixel_color, int samples_per_pixel) {
    double r = pixel_color.x() / samples_per_pixel;
    double g = pixel_color.y() / samples_per_pixel;
    double b = pixel_color.z() / samples_per_pixel;

    r = sqrt(r);
    g = sqrt(g);
    b = sqrt(b);

    // Write the translated [0,255] value of each color component.
    out << int(256 * clamp(r, 0.0, 0.999)) << ' '
        << int(256 * clamp(g, 0.0, 0.999)) << ' '
        << int(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif //RAYTRACING_COLOR_HPP
