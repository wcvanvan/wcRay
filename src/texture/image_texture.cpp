#define STB_IMAGE_IMPLEMENTATION
#include "image_texture.h"
#include <iostream>

WCRAY_NAMESPACE_BEGIN
    ImageTexture::ImageTexture(const char *filename) {
        auto components_per_pixel = bytes_per_pixel;
        data = stbi_load(filename, &width, &height, &components_per_pixel, components_per_pixel);
        if (!data) {
            std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
            width = height = 0;
        }
        bytes_per_scanline = bytes_per_pixel * width;
    }

    Color ImageTexture::value(double u, double v, const Point3 &p) const {
        if (data == nullptr) {
            return {0, 1, 1};
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

WCRAY_NAMESPACE_END