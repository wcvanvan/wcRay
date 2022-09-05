#ifndef SOFTWAREPATHTRACING_NOISE_TEXTURE_H
#define SOFTWAREPATHTRACING_NOISE_TEXTURE_H

#include "texture.h"

WCRAY_NAMESPACE_BEGIN

    class Perlin {
    private:
        static int permutation[256];
        int *p;
    public:

        Perlin();

        ~Perlin();

        [[nodiscard]] double noise(const Point3 &point) const;


        [[nodiscard]] double turb(const Point3 &point, int depth = 7) const;
    };


    class NoiseTexture : public texture {
    private:
        Perlin *noise{};
        double scale = 1;
        int mode;
    public:
        explicit NoiseTexture(double _scale = 1.0, int _mode = 1);

        ~NoiseTexture();

        [[nodiscard]] Color value(double u, double v, const Point3 &p) const override;

        Color get_color(const Point3 &p) const;

    };

    double lerp(double t, double a, double b);

    double grad(int hash, double x, double y, double z);

    double fade(double t);

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_NOISE_TEXTURE_H
