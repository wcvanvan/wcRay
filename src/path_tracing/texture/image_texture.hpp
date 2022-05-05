#ifndef RAYTRACING_IMAGE_TEXTURE_HPP
#define RAYTRACING_IMAGE_TEXTURE_HPP

#include "texture.hpp"
#include "../rt_stb_image.hpp"
#include "../utils.hpp"

class image_texture : public texture {
    const static int bytes_per_pixel = 3;
    int bytes_per_scanline{};
public:
    int width{}, height{};
    unsigned char *data{};

    image_texture() = default;

    explicit image_texture(const char *filename) {
        auto components_per_pixel = bytes_per_pixel;
        data = stbi_load(filename, &width, &height, &components_per_pixel, components_per_pixel);
        if (!data) {
            std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
            width = height = 0;
        }
        bytes_per_scanline = bytes_per_pixel * width;
    }

    [[nodiscard]] color value(double u, double v, const point3 &p) const override;
};

color image_texture::value(double u, double v, const point3 &p) const {
    if (data == nullptr) {
        return {0,1,1};
    }
    u = clamp(u, 0.0, 1.0);
    v = 1.0 - clamp(v, 0.0, 1.0);
    auto i = int(u * (double) width);
    auto j = int(v * (double) height);
    if (i >= width) {
        i = width - 1;
    }
    if (j >= height) {
        j = height - 1;
    }
    unsigned char *pixel = data + bytes_per_pixel * i + bytes_per_scanline * j;
    double color_scale = 1.0 / 255.0;
    return {color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]};
}

#endif //RAYTRACING_IMAGE_TEXTURE_HPP
