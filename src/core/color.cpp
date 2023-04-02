#include "color.h"

WCRAY_NAMESPACE_BEGIN

    Color
    ray_color(Ray &ray, const HittableList &world, const std::shared_ptr<Hittable> &lights, Color &background,
              int depth) {
        if (depth <= 0) {
            return {0.0, 0.0, 0.0};
        }
        HitRecord hit_record;
        if (!world.hit(ray, 0.001, infinity, hit_record)) {
            return background;
        }
        ScatterRecord scatter_record;
        Color emitted = hit_record.material_ptr->emitted(ray, hit_record);
        if (!hit_record.material_ptr->scatter(ray, hit_record, scatter_record)) {
            return emitted;
        }
        if (scatter_record.is_specular) {
            return scatter_record.attenuation *
                   ray_color(scatter_record.specular_ray, world, lights, background, depth - 1);
        }
        Ray ray_scattered;
        double pdf_value{};
        MixturePDF mix_pdf(std::make_shared<HittablePDF>(lights, hit_record.hit_point), scatter_record.pdf_ptr);
        ray_scattered = {hit_record.hit_point, mix_pdf.generate(), ray.time};
        double NdotL = dot(normalize(hit_record.normal), normalize(ray_scattered.direction));
        pdf_value = mix_pdf.value(ray_scattered.direction);
        return emitted +
               scatter_record.BRDF * NdotL *
               ray_color(ray_scattered, world, lights, background, depth - 1) / pdf_value;
    }

    void write_color(std::ostream &out, Color **image, int samples_per_pixel, int image_height, int image_width) {
        for (int h = 0; h < image_height; ++h) {
            for (int w = 0; w < image_width; ++w) {
                int pos = h * image_height + w;
                double r = image[pos]->x() / samples_per_pixel;
                double g = image[pos]->y() / samples_per_pixel;
                double b = image[pos]->z() / samples_per_pixel;

                r = sqrt(r);
                g = sqrt(g);
                b = sqrt(b);

                // Write the translated [0,255] value of each color component.
                out << int(256 * clamp(r, 0.0, 0.999)) << ' '
                    << int(256 * clamp(g, 0.0, 0.999)) << ' '
                    << int(256 * clamp(b, 0.0, 0.999)) << '\n';
            }
        }
    }

WCRAY_NAMESPACE_END
