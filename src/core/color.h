#ifndef SOFTWAREPATHTRACING_COLOR_H
#define SOFTWAREPATHTRACING_COLOR_H

#include "vec.h"
#include "ray.h"
#include "../pdf/mixture_pdf.h"
#include "../pdf/hittable_pdf.h"
#include "../geometries/hit.h"
#include "../geometries/hittable_list.h"

WCRAY_NAMESPACE_BEGIN

    Color
    ray_color(Ray &ray, const HittableList &world, const std::shared_ptr<Hittable> &lights, Color &background,
              int depth);

    void write_color(std::ostream &out, Color &pixel_color, int samples_per_pixel);

WCRAY_NAMESPACE_END

#endif //SOFTWAREPATHTRACING_COLOR_H
