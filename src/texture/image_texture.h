#ifndef SOFTWAREPATHTRACING_IMAGE_TEXTURE_H
#define SOFTWAREPATHTRACING_IMAGE_TEXTURE_H

#include "texture.h"
#include "../core/stb_image.h"

WCRAY_NAMESPACE_BEGIN

    class ImageTexture : public texture {
        const static int bytes_per_pixel = 3;
        int bytes_per_scanline{};
    public:
        int width{}, height{};
        unsigned char *data{};

        ImageTexture() = default;

        explicit ImageTexture(const char *filename);

        [[nodiscard]] Color value(double u, double v, const Point3 &p) const override;
    };

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_IMAGE_TEXTURE_H
