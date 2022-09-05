#include "path_tracing.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <memory>

using std::make_shared;
using std::shared_ptr;
using namespace wcRay;

std::shared_ptr<HittableList> final_scene() {
    HittableList objects;

    // Cornell box
    auto red = make_shared<Lambertian>(Color(.65, .05, .05));
    auto white = make_shared<Lambertian>(Color(.73, .73, .73));
    auto green = make_shared<Lambertian>(Color(.12, .45, .15));
    auto light = make_shared<DiffuseLight>(std::make_shared<solid_color>(Color(7, 7, 7)));
    auto noise1 = std::make_shared<Lambertian>(std::make_shared<NoiseTexture>(0.005, 1));

    objects.add(make_shared<YZRect>(0, 555, 0, 555, 555, green));
    objects.add(make_shared<YZRect>(0, 555, 0, 555, 0, red));
    objects.add(make_shared<FlipFace>(make_shared<XZRect>(200, 360, 220, 340, 554.99, light)));
    objects.add(make_shared<XZRect>(0, 555, 0, 555, 555, noise1));
    objects.add(make_shared<XZRect>(0, 555, 0, 555, 0, white));
    objects.add(make_shared<XYRect>(0, 555, 0, 555, 555, white));

    // smoke box
    shared_ptr<Hittable> box1 = make_shared<Box>(Point3(0, 0, 0), Point3(165, 330, 165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, Vec3(265, 0, 295));

    shared_ptr<Hittable> box2 = make_shared<Box>(Point3(0, 0, 0), Point3(165, 165, 165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, Vec3(130, 0, 65));

    objects.add(make_shared<Volumn>(box1, 0.01,
                                    std::make_shared<Isotropic>(std::make_shared<solid_color>(Color(1, 1, 1)))));
    objects.add(make_shared<Volumn>(box2, 0.01,
                                    std::make_shared<Isotropic>(std::make_shared<solid_color>(Color(0, 0, 0)))));

//    // Fill with spheres
    auto earth_texture = make_shared<ImageTexture>(R"(D:\Projects\SoftwarePathTracing\resources\earthmap.jpg)");
    auto earth_surface = make_shared<Lambertian>(earth_texture);
    auto globe = make_shared<sphere>(Point3(310, 400, 165), 50, earth_surface);
    objects.add(globe);

    auto white_metal = std::make_shared<Metal>(Color(.73, .73, .73), 0);
    objects.add(std::make_shared<sphere>(Point3(170, 250, 220), 50, white_metal));

    auto mov_sphere = make_shared<moving_sphere>(Point3(140, 450, 350), Point3(190, 450, 350), 50,
                                                 make_shared<Lambertian>(Color(0.4, 0.4, 0.5)), 0.0, 1.0);
    objects.add(mov_sphere);

    objects.add(make_shared<sphere>(Point3(490, 370, 350), 50, make_shared<Dielectric>(1.5)));

    return std::make_shared<HittableList>(objects);
}

shared_ptr<HittableList> cornell_box() {
    HittableList objects;
    auto red = make_shared<Lambertian>(Color(.65, .05, .05));
    auto white = make_shared<Lambertian>(Color(.73, .73, .73));
    auto green = make_shared<Lambertian>(Color(.12, .45, .15));
    auto light = make_shared<DiffuseLight>(std::make_shared<solid_color>(Color(5, 5, 5)));

    objects.add(make_shared<YZRect>(0, 555, 0, 555, 555, green));
    objects.add(make_shared<YZRect>(0, 555, 0, 555, 0, red));
    objects.add(make_shared<FlipFace>(make_shared<XZRect>(213, 343, 227, 332, 554, light)));
    objects.add(make_shared<XZRect>(0, 555, 0, 555, 0, white));
    objects.add(make_shared<XZRect>(0, 555, 0, 555, 555, white));
    objects.add(make_shared<XYRect>(0, 555, 0, 555, 555, white));

    shared_ptr<Hittable> box1 = make_shared<Box>(Point3(0, 0, 0), Point3(165, 330, 165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, Vec3(265, 0, 295));
    objects.add(box1);

    shared_ptr<Hittable> box2 = make_shared<Box>(Point3(0, 0, 0), Point3(165, 165, 165), white);

    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, Vec3(130, 0, 65));
    objects.add(box2);
    return std::make_shared<HittableList>(objects);
}

int main() {
    std::ofstream file(R"(D:\Projects\SoftwarePathTracing\pic.ppm)");
    int scene = 1;
    shared_ptr<HittableList> world;
    double aspect_ratio;
    int image_width;
    int samples_per_pixel;
    int image_height;
    int depth = 50;
    Color background;
    Point3 lookfrom;
    Point3 lookat;
    double aperture = 0.0;
    double vfov;
    // lights is the list of direct sampling objects
    shared_ptr<HittableList> lights(new HittableList);
    switch (scene) {
        case 1:
            world = cornell_box();
            aspect_ratio = 1.0;
            image_width = 100;
            samples_per_pixel = 200;
            background = Color(0, 0, 0);
            lookfrom = Point3(278, 278, -800);
            lookat = Point3(278, 278, 0);
            vfov = 40.0;
            lights->add(make_shared<XZRect>(200, 360, 220, 340, 554.99, nullptr));
            break;
        case 2:
            world = final_scene();
            aspect_ratio = 1.0;
            image_width = 600;
            samples_per_pixel = 3000;
            background = Color(0, 0, 0);
            lookfrom = Point3(278, 278, -800);
            lookat = Point3(278, 278, 0);
            vfov = 40.0;
            lights->add(make_shared<XZRect>(200, 360, 220, 340, 554.99, nullptr));
            lights->add(make_shared<sphere>(Point3(490, 370, 350), 50, nullptr));
            break;
        default:
            break;
    }
    Vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    image_height = static_cast<int>(image_width / aspect_ratio);
    Camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);
    auto bvh = make_shared<bvh_node>(world->hittable_objects, 0, world->hittable_objects.size(), 0, 1);
    auto *objects = new HittableList;
    objects->add(bvh);

    file << "P3\n" << image_width << " " << image_height << "\n255\n";
    auto start_time = std::chrono::system_clock::now();
    for (int height = image_height - 1; height >= 0; --height) {
        std::cout << "\rScanlines remaining: " << height << '\n' << std::flush;
        for (int width = 0; width < image_width; ++width) {
            Color pixel_color(0.0, 0.0, 0.0);
            for (int sample = 0; sample < samples_per_pixel; ++sample) {
                Ray r = cam.get_ray(
                        ((double) height + random_number()) / (image_height - 1),
                        ((double) width + random_number()) / (image_width - 1));
                Color r_color(ray_color(r, *objects, lights, background, depth));
                pixel_color += r_color;
            }
            write_color(file, pixel_color, samples_per_pixel);
        }
    }
    auto end_time = std::chrono::system_clock::now();
    std::cerr << "\nDone.\n";
    std::cout << "time: " << double((end_time - start_time).count()) / pow(10, 9) << "s" << std::endl;

}