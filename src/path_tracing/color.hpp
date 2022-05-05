#ifndef RAYTRACING_COLOR_HPP
#define RAYTRACING_COLOR_HPP

#include "ray.hpp"
#include "geometries/hit.hpp"
#include "utils.hpp"


color ray_color(ray &r, const hittable_list &world, color &background, int depth) {
    if (depth <= 0) {
        return {0, 0, 0};
    }
    hit_record record;
    if (world.hit(r, 0.001, infinity, record)) {
        color emit = record.material_ptr->emit(record.u, record.v, record.hit_point);
        ray scattered;
        color albedo;
        if (record.material_ptr->scatter(r, record, albedo, scattered)) {
            return emit + albedo * ray_color(scattered, world, background, depth - 1);
        } else {
            return emit;
        }
    } else {
        return background;
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
