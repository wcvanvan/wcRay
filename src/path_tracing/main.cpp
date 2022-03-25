#include <iostream>
#include <fstream>
#include <thread>
#include <memory>
#include "path_tracing.hpp"

hittable_list &random_scene(Random &random) {
    auto *world = new hittable_list;

    auto ground_material = std::make_shared<lambertian>(color(0.5, 0.5, 0.5), random);
    auto ground = std::make_shared<sphere>(point3(0,-1000,0), 1000, ground_material);
    world->add(ground);

    for (int a = -3; a < 8; a++) {
        for (int b = -3; b < 11; b++) {
            auto choose_mat = random.random_number();
            point3 center(a + 0.9*random.random_number(), 0.2, b + 0.9*random.random_number());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random.random_color() * random.random_color();
                    sphere_material = std::make_shared<lambertian>(albedo, random);
                    auto s = std::make_shared<sphere>(center, 0.2, sphere_material);
                    world->add(s);
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random.random_color(0.5, 1);
                    auto fuzz = random.random_number(0, 0.5);
                    sphere_material = std::make_shared<metal>(albedo, fuzz, random);
                    auto s = std::make_shared<sphere>(center, 0.2, sphere_material);
                    world->add(s);
                } else {
                    // glass
                    sphere_material = std::make_shared<dielectric>(1.5, random);
                    auto s = std::make_shared<sphere>(center, 0.2, sphere_material);
                    world->add(s);
                }
            }
        }
    }

    auto material1 = std::make_shared<dielectric>(1.5, random);
    auto s1 = std::make_shared<sphere>(point3(0, 1, 0), 1.0, material1);
    world->add(s1);

    auto material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1), random);
    auto s2 = std::make_shared<sphere>(point3(-4, 1, 0), 1.0, material2);
    world->add(s2);

    auto material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0, random);
    auto s3 = std::make_shared<sphere>(point3(4, 1, 0), 1.0, material3);
    world->add(s3);

    return *world;
}

int main() {
    std::ofstream file(R"(D:\Projects\RayTracing\pic.ppm)");
    double ratio = 3.0 / 2.0;
    int img_width = 1000;
    int img_height = int(img_width / ratio);
    int samples_per_pixel = 100;
    int depth = 50;

    Random random;

    point3 lookfrom(13,2,3);
    point3 lookat(0,0,0);
    vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;
    camera cam(lookfrom, lookat, vup, 20, ratio, aperture, dist_to_focus, random);

    auto world = random_scene(random);

    file << "P3\n" << img_width << " " << img_height << "\n255\n";
    auto start_time = std::chrono::system_clock::now();
    for (int height = img_height - 1; height >= 0; --height) {
        std::cout << "\rScanlines remaining: " << height << '\n' << std::flush;
        for (int width = 0; width < img_width; ++width) {
            color pixel_color(0.0, 0.0, 0.0);
            for (int sample = 0; sample < samples_per_pixel; ++sample) {
                ray r = cam.get_ray(
                        ((double) height + random.random_number()) / (img_height - 1),
                        ((double) width + random.random_number()) / (img_width - 1));
                color r_color(ray_color(r, world, depth, random));
                pixel_color += r_color;
            }
            write_color(file, pixel_color, samples_per_pixel);
        }
    }
    auto end_time = std::chrono::system_clock::now();
    std::cerr << "\nDone.\n";
    std::cout << "time: " << double((end_time - start_time).count()) / pow(10, 9) << "s" << std::endl;
    delete &world;
}