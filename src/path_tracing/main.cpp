#include <iostream>
#include <fstream>
#include <thread>
#include <memory>
#include "path_tracing.hpp"

using std::make_shared;
using std::make_shared;
using std::shared_ptr;
using std::shared_ptr;

std::shared_ptr<hittable_list> cornell_smoke() {
    hittable_list objects;

    auto red = make_shared<metal>(color(.65, .05, .05), 0.7);
    auto white = make_shared<metal>(color(.73, .73, .73), 0.7);
    auto green = make_shared<metal>(color(.12, .45, .15), 0.7);
    auto light = make_shared<diffuse_light>(std::make_shared<solid_color>(color(7, 7, 7)));

//    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
//    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
//    objects.add(make_shared<xz_rect>(113, 443, 127, 432, 554, light));
////    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
//    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
//    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));
//
    shared_ptr<hittable> box1 = make_shared<box>(point3(0, 0, 0), point3(165, 330, 165), white);
//    box1 = make_shared<rotate_y>(box1, 15);
//    box1 = make_shared<translate>(box1, vec3(265,0,295));

    shared_ptr<hittable> box2 = make_shared<box>(point3(0, 0, 0), point3(165, 165, 165), white);
//    box2 = make_shared<rotate_y>(box2, -18);
//    box2 = make_shared<translate>(box2, vec3(130,0,65));

    objects.add(make_shared<volumn>(box1, 0.01,
                                    std::make_shared<isotropic>(std::make_shared<solid_color>(color(0, 0, 0)))));
    objects.add(make_shared<volumn>(box2, 0.01,
                                    std::make_shared<isotropic>(std::make_shared<solid_color>(color(1, 1, 1)))));

    return std::make_shared<hittable_list>(objects);
}

std::shared_ptr<hittable_list> lsd_box() {
    hittable_list objects;

    auto red = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<metal>(color(.73, .73, .73), 0);
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(std::make_shared<solid_color>(color(4, 4, 4)));

//    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 555, red));
    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
    objects.add(make_shared<xz_rect>(170, 400, 200, 380, 554, light));
//    objects.add(make_shared<xz_rect>(213, 343, 227, 332, 0, light));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, red));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, red));
    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, red));
    point3 center(270, 270, 270);
    objects.add(std::make_shared<sphere>(center, 100, green));
//
//    shared_ptr<hittable> box1 = make_shared<box>(point3(0, 0, 0), point3(165, 330, 165), white);
//    box1 = make_shared<rotate_y>(box1, 15);
//    box1 = make_shared<translate>(box1, vec3(265,0,295));
//    objects.add(box1);
//
//    shared_ptr<hittable> box2 = make_shared<box>(point3(0,0,0), point3(165,165,165), white);
//    box2 = make_shared<rotate_y>(box2, -18);
//    box2 = make_shared<translate>(box2, vec3(130,0,65));
//    objects.add(box2);
    return std::make_shared<hittable_list>(objects);
}

shared_ptr<hittable_list> cornell_box() {
    hittable_list objects;

    auto red = make_shared<metal>(color(.65, .05, .05), 0);
    auto white = make_shared<metal>(color(.73, .73, .73), 0.7);
    auto green = make_shared<metal>(color(.12, .45, .15), 0.7);
    auto green_metal = make_shared<metal>(color(.12, .45, .15), 0);
    auto light = make_shared<diffuse_light>(std::make_shared<solid_color>(color(5, 5, 5)));

    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
    point3 light_center(250, 50, 250);
//    objects.add(make_shared<sphere>(light_center, 50, light));
    objects.add(make_shared<xz_rect>(100, 450, 100, 450, 550, light));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));
    point3 center(250, 270, 270);
//    point3 point1(100,100,50), point2(200,100,50), point3(150, 200,50);
//    objects.add(std::make_shared<triangle>(point1, point2, point3, green_metal));
    objects.add(std::make_shared<sphere>(center, 100, green_metal));
//
//    shared_ptr<hittable> box1 = make_shared<box>(point3(0, 0, 0), point3(165, 330, 165), white);
//    box1 = make_shared<rotate_y>(box1, 15);
//    box1 = make_shared<translate>(box1, vec3(265,0,295));
//    objects.add(box1);
//
//    shared_ptr<hittable> box2 = make_shared<box>(point3(0,0,0), point3(165,165,165), white);
//    box2 = make_shared<rotate_y>(box2, -18);
//    box2 = make_shared<translate>(box2, vec3(130,0,65));
//    objects.add(box2);
    return std::make_shared<hittable_list>(objects);
}

[[maybe_unused]] shared_ptr<hittable_list> simple_light() {
    hittable_list objects;

    auto pertext = make_shared<noise_texture>(4);
    objects.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
    objects.add(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));

    auto difflight = make_shared<diffuse_light>(make_shared<solid_color>(color(4, 4, 4)));
    objects.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflight));
    objects.add(std::make_shared<sphere>(point3(0, 7, 0), 1, difflight));

    return make_shared<hittable_list>(objects);
}

shared_ptr<hittable_list> two_perlin_spheres() {
    hittable_list objects;

    auto pertext = make_shared<noise_texture>();
    objects.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(pertext)));
    objects.add(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));

    return make_shared<hittable_list>(objects);
}

shared_ptr<hittable_list> earth() {
    hittable_list objects;
    auto earth_texture = make_shared<image_texture>(R"(D:\Projects\RayTracing\src\resources\earthmap.jpg)");
    auto earth_surface = make_shared<lambertian>(earth_texture);
    auto globe = make_shared<sphere>(point3(0, 0, 0), 2, earth_surface);
    objects.add(globe);

    return make_shared<hittable_list>(objects);
}

shared_ptr<hittable_list> two_spheres() {
    hittable_list objects;

    auto checker = make_shared<alternating_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));

    objects.add(make_shared<sphere>(point3(0, -10, 0), 10, make_shared<lambertian>(checker)));
    objects.add(make_shared<sphere>(point3(0, 10, 0), 10, make_shared<lambertian>(checker)));

    return make_shared<hittable_list>(objects);
}

shared_ptr<hittable_list> random_scene() {
    auto world = make_shared<hittable_list>();

    auto earth_texture = make_shared<image_texture>(R"(D:\Projects\RayTracing\src\resources\earthmap.jpg)");
    auto earth_surface = make_shared<lambertian>(earth_texture);
    auto globe = make_shared<sphere>(point3(0, -1000, 0), 1000, earth_surface);
    world->add(globe);

    for (int a = -5; a < 2; a++) {
        for (int b = -1; b < 3; b++) {
            auto choose_mat = random_number();
            point3 center(a + 0.9 * random_number(), 0.2, b + 0.9 * random_number());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random_color() * random_color();
                    sphere_material = make_shared<lambertian>(albedo);
//                    auto center2 = center + vec3(0.random_number(0, 0.5), 0);
                    auto s = make_shared<sphere>(center, 0.2, sphere_material);
                    world->add(s);
//                    auto mov_sphere = make_shared<moving_sphere>(
//                            center, center2, 0.2, sphere_material, 0.0, 1.0);
//                    world->add(mov_sphere);
                }
            } else if (choose_mat < 0.95) {
                // metal
                auto albedo = random_color(0.5, 1);
                auto fuzz = random_number(0, 0.5);
                auto sphere_material = make_shared<metal>(albedo, fuzz);
                auto s = make_shared<sphere>(center, 0.2, sphere_material);
                world->add(s);
            } else {
                // glass
                auto sphere_material = make_shared<dielectric>(1.5);
                auto s = make_shared<sphere>(center, 0.2, sphere_material);
                world->add(s);
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    auto s1 = make_shared<sphere>(point3(0, 1, 0), 1.0, material1);
    world->add(s1);

    auto alternating = make_shared<alternating_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
    auto material2 = make_shared<lambertian>(alternating);
    auto s2 = make_shared<sphere>(point3(-4, 1, 0), 1.0, material2);
    world->add(s2);

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    auto s3 = make_shared<sphere>(point3(4, 1, 0), 1.0, material3);
    world->add(s3);
    return world;
}

int main() {
    std::ofstream file(R"(D:\Projects\RayTracing\pic.ppm)");
    int scene = 4;
    shared_ptr<hittable_list> world;
    double aspect_ratio;
    int image_width;
    int samples_per_pixel;
    int image_height;
    int depth = 50;
    color background;
    point3 lookfrom;
    point3 lookat;
    double aperture = 0.0;
    double vfov;
    switch (scene) {
        case 1:
            world = random_scene();
            background = color(0.70, 0.80, 1.00);
            lookfrom = point3(13, 2, 3);
            lookat = point3(0, 0, 0);
            vfov = 20.0;
            aperture = 0.1;
            break;

        case 2:
            world = two_spheres();
            background = color(0.70, 0.80, 1.00);
            lookfrom = point3(13, 2, 3);
            lookat = point3(0, 0, 0);
            vfov = 20.0;
            break;

        case 3:
            world = two_perlin_spheres();
            background = color(0.70, 0.80, 1.00);
            lookfrom = point3(13, 2, 3);
            lookat = point3(0, 0, 0);
            vfov = 20.0;
            break;
        case 4:
            world = earth();
            background = color(0.70, 0.80, 1.00);
            image_width = 200;
            samples_per_pixel = 200;
            aspect_ratio = 1.0;
            lookfrom = point3(13, 2, 3);
            lookat = point3(0, 0, 0);
            vfov = 20.0;
            break;
        case 5:
            world = simple_light();
            samples_per_pixel = 200;
            aspect_ratio = 2.0;
            image_width = 400;
            background = color(0, 0, 0);
            lookfrom = point3(26, 3, 6);
            lookat = point3(0, 2, 0);
            vfov = 20.0;
            break;
        case 6:
            world = cornell_box();
            aspect_ratio = 1.0;
            image_width = 200;
            samples_per_pixel = 100;
            background = color(0, 0, 0);
            lookfrom = point3(278, 278, -800);
//            lookfrom = point3(600, 278, -600);
            lookat = point3(278, 278, 0);
            vfov = 40.0;
            break;
        case 7:
            world = cornell_smoke();
            aspect_ratio = 1.0;
            image_width = 100;
            samples_per_pixel = 200;
            lookfrom = point3(278, 278, -800);
            lookat = point3(278, 278, 0);
            vfov = 40.0;
            background = color(0.3, 0.5, 0.2);
            break;
        case 8:
            world = lsd_box();
            aspect_ratio = 1.0;
            image_width = 200;
            samples_per_pixel = 100;
            background = color(0.5, 0.3, 0.6);
//            background = color(0, 0, 0);
            lookfrom = point3(700, 278, -500);
            lookat = point3(400, 278, 0);
            vfov = 40.0;
            break;
        default:
            break;
    }
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    image_height = static_cast<int>(image_width / aspect_ratio);
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);
    auto bvh = make_shared<bvh_node>(world->hittable_objects, 0, world->hittable_objects.size(), 0, 1);
    auto *objects = new hittable_list;
    objects->add(bvh);

    file << "P3\n" << image_width << " " << image_height << "\n255\n";
    auto start_time = std::chrono::system_clock::now();
    for (int height = image_height - 1; height >= 0; --height) {
        std::cout << "\rScanlines remaining: " << height << '\n' << std::flush;
        for (int width = 0; width < image_width; ++width) {
            color pixel_color(0.0, 0.0, 0.0);
            for (int sample = 0; sample < samples_per_pixel; ++sample) {
                ray r = cam.get_ray(
                        ((double) height + random_number()) / (image_height - 1),
                        ((double) width + random_number()) / (image_width - 1));
                color r_color(ray_color(r, *objects, background, depth));
                pixel_color += r_color;
            }
            write_color(file, pixel_color, samples_per_pixel);
        }
    }
    auto end_time = std::chrono::system_clock::now();
    std::cerr << "\nDone.\n";
    std::cout << "time: " << double((end_time - start_time).count()) / pow(10, 9) << "s" << std::endl;

}